
#ifndef HPP_NEWEGGSERVERCOMMAND
#define HPP_NEWEGGSERVERCOMMAND

#include <sstream>

#include "IServerCommand.hpp"

class NewEggServerCommand : public IServerCommand
{
    SERVERCOMMAND_META

    public:
    static IServerCommand* factory(std::string const& str)
    {
        std::stringstream ss(str);
        std::string cmd;
        int egg;
        int player;
        int x;
        int y;

        ss.exceptions(std::ios_base::failbit);
        ss >> cmd;
        
        if (cmd != "enw")
            return 0;

        ss >> egg >> player >> x >> y;
        if (!ss.eof())
            return 0;

        return new NewEggServerCommand(egg, player, x, y);
    }

    NewEggServerCommand(int egg_arg, int player_arg, int x_arg, int y_arg)
        : egg(egg_arg), player(player_arg), x(x_arg), y(y_arg)
    {
    }

    int const egg;
    int const player;
    int const x;
    int const y;
};

#endif

