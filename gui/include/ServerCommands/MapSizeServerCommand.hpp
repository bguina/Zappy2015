
#ifndef HPP_MAPSIZESERVERCOMMAND
#define HPP_MAPSIZESERVERCOMMAND

#include <sstream>

#include "IServerCommand.hpp"

class MapSizeServerCommand : public IServerCommand
{
    SERVERCOMMAND_META

    public:
    static IServerCommand* factory(std::string const& str)
    {
        std::stringstream ss(str);
        std::string cmd;
        int x;
        int y;

        ss.exceptions(std::ios_base::failbit);
        ss >> cmd;
        
        if (cmd != "msz")
            return 0;

        ss >> x >> y;
        if (!ss.eof())
            return 0;

        return new MapSizeServerCommand(x, y);
    }

    MapSizeServerCommand(int x_arg, int y_arg)
        : x(x_arg), y(y_arg)
    {
    }

    int const x;
    int const y;
};

#endif

