
#ifndef HPP_TIMESERVERCOMMAND
#define HPP_TIMESERVERCOMMAND

#include <sstream>

#include "IServerCommand.hpp"

class TimeServerCommand : public IServerCommand
{
    SERVERCOMMAND_META

    public:
    static IServerCommand* factory(std::string const& str)
    {
        std::stringstream ss(str);
        std::string cmd;
        int time;

        ss.exceptions(std::ios_base::failbit);
        ss >> cmd;
        
        if (cmd != "sgt")
            return 0;

        ss >> time;
        if (!ss.eof())
            return 0;

        return new TimeServerCommand(time);
    }

    TimeServerCommand(int time_arg)
        : time(time_arg)
    {
    }

    int const time;
};

#endif

