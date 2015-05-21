
#ifndef HPP_INVENTORYSERVERCOMMAND
#define HPP_INVENTORYSERVERCOMMAND

#include <sstream>
#include <vector>

#include "Game.hpp"
#include "IServerCommand.hpp"

class InventoryServerCommand : public IServerCommand
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
        std::vector<int> resources;

        ss.exceptions(std::ios_base::failbit);
        ss >> cmd;
        
        if (cmd != "pin")
            return 0;

        ss >> player >> x >> y;
        resources.resize(TOTAL_RESOURCES);
        for (int i = 0; i < TOTAL_RESOURCES; ++i)
            ss >> resources[i];
        if (!ss.eof())
            return 0;

        return new InventoryServerCommand(player, x, y, resources);
    }

    InventoryServerCommand(int player_arg, int x_arg, int y_arg, std::vector<int> const& resources_arg)
        : player(player_arg), x(x_arg), y(y_arg), resources(resources_arg)
    {
    }

    int const player;
    int const x;
    int const y;
    std::vector<int> const resources;
};

#endif

