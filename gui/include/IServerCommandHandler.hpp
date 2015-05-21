
#ifndef HPP_ISERVERCOMMANDHANDLER
#define HPP_ISERVERCOMMANDHANDLER

class IServerCommand;

class IServerCommandHandler
{
    public:
    virtual void operator()(IServerCommand const& command) = 0;
};

#endif

