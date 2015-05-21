
#ifndef HPP_INCANTATIONCASTSERVERCOMMAND
#define HPP_INCANTATIONCASTSERVERCOMMAND

#include <sstream>
#include <vector>

#include "IServerCommand.hpp"

class IncantationCastServerCommand : public IServerCommand
{
    SERVERCOMMAND_META

    public:
    static IServerCommand* factory(std::string const& str)
    {
        std::stringstream ss(str);
        std::string cmd;
        int x;
        int y;
        int level;
        std::vector<int> players;

        ss.exceptions(std::ios_base::failbit);
        ss >> cmd;
        
        if (cmd != "pic")
            return 0;

        ss >> x >> y >> level;
        for (int i = 0; !ss.eof(); ++i)
        {
            players.push_back(0);
            ss >> players[i];
        }

        return new IncantationCastServerCommand(x, y, level, players);
    }

    IncantationCastServerCommand(int x_arg, int y_arg, int level_arg, std::vector<int> const& players_arg)
        : x(x_arg), y(y_arg), level(level_arg), players(players_arg)
    {
    }

  int const x;
    int const y;
    int const level;
    std::vector<int> const players;
};

#endif

