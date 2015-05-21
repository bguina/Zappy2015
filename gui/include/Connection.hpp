
#ifndef HPP_CONNECTION
#define HPP_CONNECTION

#include <cassert>
#include <string>
#include <queue>
#include <list>
#include <map>

#include <pthread.h>

#include "ErrnoException.hpp"
#include "IClientCommand.hpp"
#include "IServerCommand.hpp"
#include "ServerCommandHandler.hpp"

class IClientRequest;

class Connection
{
    private:
    // Okay, this could be a simple object and not a singleton but both
    // the GUI and the AI will require one and only one connection.
    Connection();
    ~Connection();

    public:
    static Connection& singleton();

    // Return true if connected, false otherwise
    bool is_connected() const;

    // Connect to the server
    // Throws ErrnoException on failure
    void connect(std::string const& host, int port);

    // Disconnect from the server
    // Has no effect if not connected
    void disconnect();

    // Register a server command handlers and return true
    // Return false if a handler is already registered for the given command id
    template<class T>
    void register_handler(IServerCommand::ID command_id, T& obj, void (T::*handler)(IServerCommand const&));

    // Unregister the handler associated with the given command id, if any
    void unregister_handler(IServerCommand::ID command);

    // Interpret the socket's output already readen until now
    // Asynchronous, cannot fail
    void process();

    // Send a string over the socket and return true
    // Return false if disconnected (or if the connection was lost)
    bool send(std::string const& raw);

    private:
    void _disconnect();
    int m_socket;
    
    static void* _read(void*);
    void _lock(bool lock);
    pthread_t m_thread;
    pthread_mutex_t m_thread_lock;

    std::string m_buffer;

    typedef std::map<IServerCommand::ID, IServerCommandHandler*> ServerCommandHandlerMapType;
    ServerCommandHandlerMapType m_handlers;
};

template<class T>
void Connection::register_handler(IServerCommand::ID command_id, T& obj, void (T::*handler)(IServerCommand const&))
{
    assert(m_handlers.insert(
        std::pair<
            ServerCommandHandlerMapType::key_type,
            ServerCommandHandlerMapType::mapped_type
        >(
            command_id,
            new ServerCommandHandler<T>(obj, handler)
        )
    ).second);
}

#endif

