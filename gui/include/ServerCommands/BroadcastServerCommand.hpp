
#ifndef HPP_BROADCASTSERVERCOMMAND
#define HPP_BROADCASTSERVERCOMMAND

#include <sstream>

#include "IServerCommand.hpp"

class BroadcastServerCommand : public IServerCommand
{
    SERVERCOMMAND_META

    public:
    static IServerCommand* factory(std::string const& str)
    {
        std::stringstream ss(str);
        std::string cmd;
        int player;

        ss.exceptions(std::ios_base::failbit);
        ss >> cmd;
        
        if (cmd != "pbc")
            return 0;
        ss >> player;

        return new BroadcastServerCommand(player, str.substr(1 + ss.tellg()));
    }

    BroadcastServerCommand(int player_arg, std::string const& message_arg)
        : player(player_arg), message(message_arg)
    {
    }

  int const player;
  std::string const message;
};

#endif

