
#ifndef HPP_LEVELSERVERCOMMAND
#define HPP_LEVELSERVERCOMMAND

#include <sstream>

#include "IServerCommand.hpp"

class LevelServerCommand : public IServerCommand
{
    SERVERCOMMAND_META

    public:
    static IServerCommand* factory(std::string const& str)
    {
        std::stringstream ss(str);
        std::string cmd;
        int player;
        int level;

        ss.exceptions(std::ios_base::failbit);
        ss >> cmd;
        
        if (cmd != "plv")
            return 0;

        ss >> player >> level;
        if (!ss.eof())
            return 0;

        return new LevelServerCommand(player, level);
    }

    LevelServerCommand(int player_arg, int level_arg)
        : player(player_arg), level(level_arg)
    {
    }

    int const player;
    int const level;
};

#endif

