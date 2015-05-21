
#ifndef HPP_INCANTATIONENDSERVERCOMMAND
#define HPP_INCANTATIONENDSERVERCOMMAND

#include <sstream>

#include "IServerCommand.hpp"

class IncantationEndServerCommand : public IServerCommand
{
    SERVERCOMMAND_META

    public:
    static IServerCommand* factory(std::string const& str)
    {
        std::stringstream ss(str);
        std::string cmd;
        int x;
        int y;
        int result;

        ss.exceptions(std::ios_base::failbit);
        ss >> cmd;
        
        if (cmd != "pie")
            return 0;

        ss >> x >> y >> result;
        if (!ss.eof())
            return 0;

        return new IncantationEndServerCommand(x, y, result);
    }

    IncantationEndServerCommand(int x_arg, int y_arg, int result_arg)
        : x(x_arg), y(y_arg), result(result_arg)
    {
    }

    int const x;
    int const y;
    int const result;
};

#endif

