
#ifndef HPP_DROPSERVERCOMMAND
#define HPP_DROPSERVERCOMMAND

#include <sstream>

#include "IServerCommand.hpp"

class DropServerCommand : public IServerCommand
{
    SERVERCOMMAND_META

    public:
    static IServerCommand* factory(std::string const& str)
    {
        std::stringstream ss(str);
        std::string cmd;
        int player;
        int resource;

        ss.exceptions(std::ios_base::failbit);
        ss >> cmd;
        
        if (cmd != "pdr")
            return 0;

        ss >> player >> resource;
        if (!ss.eof())
            return 0;

        return new DropServerCommand(player, resource);
    }

    DropServerCommand(int player_arg, int resource_arg)
        : player(player_arg), resource(resource_arg)
    {
    }

    int const player;
    int const resource;
};

#endif

