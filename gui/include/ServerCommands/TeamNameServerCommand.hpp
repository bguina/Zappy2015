
#ifndef HPP_TEAMNAMESERVERCOMMAND
#define HPP_TEAMNAMESERVERCOMMAND

#include <sstream>

#include "IServerCommand.hpp"

class TeamNameServerCommand : public IServerCommand
{
    SERVERCOMMAND_META

    public:
    static IServerCommand* factory(std::string const& str)
    {
        std::stringstream ss(str);
        std::string cmd;

        ss.exceptions(std::ios_base::failbit);
        ss >> cmd;
        
        if (cmd != "tna")
            return 0;

        return new TeamNameServerCommand(str.substr(1 + ss.tellg()));
    }

    TeamNameServerCommand(std::string const& team_arg)
        : team(team_arg)
    {
    }

    std::string const team;
};

#endif

