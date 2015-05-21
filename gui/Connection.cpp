
#include <cerrno>
#include <cstring>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>

#include "IServerCommandHandler.hpp"
#include "ServerCommandFactoryManager.hpp"
#include "ServerCommands/UnrecognizedServerCommand.hpp"
#include "Connection.hpp"

Connection::Connection()
    : m_socket(-1)
{
    errno = 0;
    if (pthread_create(&m_thread, 0, &_read, 0) != 0 ||
        pthread_mutex_init(&m_thread_lock, 0) != 0)
        throw ErrnoException("thread creation failure", errno);
}

Connection::~Connection()
{
    pthread_kill(m_thread, SIGINT);
    pthread_join(m_thread, 0);
    
    for (ServerCommandHandlerMapType::iterator it = m_handlers.begin(); it != m_handlers.end(); ++it)
        unregister_handler(it->first);
}

Connection& Connection::singleton()
{
    static Connection instance;

    return instance;
}

bool Connection::is_connected() const
{
    return m_socket >= 0;
}

void Connection::connect(std::string const& host, int port)
{
    struct sockaddr_in serv_addr;
    struct hostent *server;

    try
    {
        errno = 0;
        server = ::gethostbyname(host.c_str());
        if (!server)
            throw ErrnoException("no such host", errno);
        
        _lock(true);
        m_socket = ::socket(AF_INET, SOCK_STREAM, 0);
        if (m_socket < 0)
            throw ErrnoException("socket open error", errno);
       
        std::memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        std::memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);
        serv_addr.sin_port = ::htons(port);
    
        if (::connect(m_socket, reinterpret_cast<struct sockaddr*>(&serv_addr), sizeof(serv_addr)) < 0)
            throw ErrnoException("connect error", errno);
    
        _lock(false);
    }
    catch (ErrnoException& e)
    {
        _disconnect();
        _lock(false);
        throw;
    }
}

void Connection::disconnect()
{
    _lock(true);
    _disconnect();
    _lock(false);
}

void Connection::unregister_handler(IServerCommand::ID command)
{
    ServerCommandHandlerMapType::iterator it(m_handlers.find(command));

    if (it != m_handlers.end())
    {
        delete it->second;
        m_handlers.erase(it);
    }
}

void Connection::process()
{
    _lock(true);
    
    if (is_connected())
    {
        int start(0);
        int end;

        if (m_buffer.size() > 4096)
        {
            // maybe we should start to worry
        }
        
        // split into commands and execute them
        while ((end = m_buffer.find('\n', start)) != std::string::npos)
        {
            std::string str(m_buffer, start, end - start);
            IServerCommand* command(ServerCommandFactoryManager::singleton().make(str));

            if (!command)
                command = new UnrecognizedServerCommand(str);
            
            _lock(false);
            (*m_handlers[command->get_id()])(*command);
            _lock(true);
            delete command;

            start = end + 1;
        }

        if (start)
            m_buffer.assign(m_buffer.substr(start));
    }
    _lock(false);
}

bool Connection::send(std::string const& raw)
{
    bool ret(false);
    
    _lock(true);

    if (is_connected())
    {
        int raw_sz(raw.size());
        char const* praw(raw.c_str());

        // make sure one and only one '\n' is in the string and terminates it
        assert(raw_sz);
        assert(raw.find('\n') == static_cast<unsigned int>(raw_sz - 1));

        // write on the socket
        while (raw_sz > 0)
        {
            int nsent;
            
            errno = 0;
            nsent = write(m_socket, praw, raw_sz);
            if (nsent <= 0)
            {
                if (errno == EINTR)
                    continue; // signal interruption

                _disconnect();
                ret = false;
                break;
            }

            raw_sz -= nsent;
            praw += nsent;
        }

        ret = true;
    }
    _lock(false);

    return ret;
}

void Connection::_disconnect()
{
    // the lock must be active
    if (is_connected())
    {
        close(m_socket);
        m_socket = -1;
    }
}

void Connection::_lock(bool lock)
{
    if (lock)
        pthread_mutex_lock(&m_thread_lock);
    else
        pthread_mutex_unlock(&m_thread_lock);
}

void* Connection::_read(void*)
{
    Connection& co(Connection::singleton());

    while (1)
    {
        char buf[2048];
        int nread;

        while (co.m_socket == -1)
            usleep(5 * 1000); // wait 5ms

        errno = 0;
        nread = ::read(co.m_socket, buf, sizeof(buf));
        
        if (nread <= 0)
        {
            co.disconnect();
            if (errno == SIGINT)
                break;
        }
        else
        {
            co._lock(true);
            co.m_buffer.append(buf, nread);
            co._lock(false);
        }
    }

    pthread_exit(0);
}

