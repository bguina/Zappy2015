
#ifndef HPP_SERVERCOMMANDHANDLER
#define HPP_SERVERCOMMANDHANDLER

#include "IServerCommandHandler.hpp"

template<class T>
class ServerCommandHandler : public IServerCommandHandler
{
    public:
    ServerCommandHandler(T& object, void (T::*handler)(IServerCommand const&))
        : m_object(object), m_handler(handler)
    {
    }

    virtual void operator()(IServerCommand const& command)
    {
        return (m_object.*m_handler)(command);
    }

    private:
    T& m_object;
    void (T::*m_handler)(IServerCommand const&);
};

#endif

