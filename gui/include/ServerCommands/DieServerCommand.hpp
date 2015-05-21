
#ifndef HPP_DIESERVERCOMMAND
#define HPP_DIESERVERCOMMAND

#include <sstream>

#include "IServerCommand.hpp"

class DieServerCommand : public IServerCommand
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
        
        if (cmd != "pdi")
            return 0;

        ss >> player;
        if (!ss.eof())
            return 0;

        return new DieServerCommand(player);
    }

    DieServerCommand(int player_arg)
        : player(player_arg)
    {
    }

    int const player;
};

#endif

