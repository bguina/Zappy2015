
#ifndef HPP_NEWPLAYERSERVERCOMMAND
#define HPP_NEWPLAYERSERVERCOMMAND

#include <sstream>

#include "IServerCommand.hpp"

class NewPlayerServerCommand : public IServerCommand
{
    SERVERCOMMAND_META

    public:
    static IServerCommand* factory(std::string const& str)
    {
        std::stringstream ss(str);
        std::string cmd;
        int player;
        int x;
        int y;
        int orientation;
        int level;
        std::string team;

        ss.exceptions(std::ios_base::failbit);
        ss >> cmd;
        
        if (cmd != "pnw")
            return 0;

        ss >> player >> x >> y >> orientation >> level;
        
        return new NewPlayerServerCommand(player, x, y, orientation, level, str.substr(1 + ss.tellg()));
    }

    NewPlayerServerCommand(int player_arg, int x_arg, int y_arg, int orientation_arg, int level_arg, std::string const& team_arg)
        : player(player_arg), x(x_arg), y(y_arg), orientation(orientation_arg), level(level_arg), team(team_arg)
    {
    }

    int const player;
    int const x;
    int const y;
    int orientation;
    int level;
    std::string const team;
};

#endif

