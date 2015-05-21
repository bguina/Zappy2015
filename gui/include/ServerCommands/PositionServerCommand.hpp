
#ifndef HPP_POSITIONSERVERCOMMAND
#define HPP_POSITIONSERVERCOMMAND

#include <sstream>

#include "IServerCommand.hpp"

class PositionServerCommand : public IServerCommand
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

        ss.exceptions(std::ios_base::failbit);
        ss >> cmd;
        
        if (cmd != "ppo")
            return 0;

        ss >> player >> x >> y >> orientation;
        if (!ss.eof())
            return 0;

        return new PositionServerCommand(player, x, y, orientation);
    }

    PositionServerCommand(int player_arg, int x_arg, int y_arg, int orientation_arg)
        : player(player_arg), x(x_arg), y(y_arg), orientation(orientation_arg)
    {
    }

    int const player;
    int const x;
    int const y;
    int const orientation;
};

#endif

