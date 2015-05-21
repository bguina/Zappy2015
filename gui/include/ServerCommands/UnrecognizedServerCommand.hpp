
#ifndef HPP_UNRECOGNIZEDSERVERCOMMAND
#define HPP_UNRECOGNIZEDSERVERCOMMAND

#include "../IServerCommand.hpp"

class UnrecognizedServerCommand : public IServerCommand
{
    public:
    static IServerCommand::ID const id;
    
    UnrecognizedServerCommand(std::string const& str)
        : m_str(str)
    {
    }

    IServerCommand::ID get_id() const
    {
        return id;
    }

    std::string const& str() const
    {
        return m_str;
    }

    protected:
    std::string const m_str;
};

#endif

