
#ifndef HPP_FORKSERVERCOMMAND
#define HPP_FORKSERVERCOMMAND

#include <sstream>

#include "IServerCommand.hpp"

class ForkServerCommand : public IServerCommand
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
        
        if (cmd != "pfk")
            return 0;

        ss >> player;
        if (!ss.eof())
            return 0;

        return new ForkServerCommand(player);
    }

    ForkServerCommand(int player_arg)
        : player(player_arg)
    {
    }

    int const player;
};

#endif

