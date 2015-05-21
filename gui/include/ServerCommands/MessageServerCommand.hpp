
#ifndef HPP_MESSAGESERVERCOMMAND
#define HPP_MESSAGESERVERCOMMAND

#include <sstream>

#include "IServerCommand.hpp"

class MessageServerCommand : public IServerCommand
{
    SERVERCOMMAND_META

    public:
    static IServerCommand* factory(std::string const& str)
    {
        std::stringstream ss(str);
        std::string cmd;

        ss.exceptions(std::ios_base::failbit);
        ss >> cmd;
        
        if (cmd != "smg")
            return 0;

        return new MessageServerCommand(str.substr(1 + ss.tellg()));
    }

    MessageServerCommand(std::string const& message_arg)
        : message(message_arg)
    {
    }

    std::string const message;
};

#endif

