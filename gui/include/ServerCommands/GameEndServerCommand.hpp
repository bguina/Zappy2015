
#ifndef HPP_GAMEENDSERVERCOMMAND
#define HPP_GAMEENDSERVERCOMMAND

#include <sstream>

#include "IServerCommand.hpp"

class GameEndServerCommand : public IServerCommand
{
    SERVERCOMMAND_META

    public:
    static IServerCommand* factory(std::string const& str)
    {
        std::stringstream ss(str);
        std::string cmd;

        ss.exceptions(std::ios_base::failbit);
        ss >> cmd;
        
        if (cmd != "seg")
            return 0;

        return new GameEndServerCommand(str.substr(1 + ss.tellg()));
    }

    GameEndServerCommand(std::string const& team_arg)
        : team(team_arg)
    {
    }

    std::string const team;
};

#endif

