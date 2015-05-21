
#ifndef HPP_EGGBORNSERVERCOMMAND
#define HPP_EGGBORNSERVERCOMMAND

#include <sstream>

#include "IServerCommand.hpp"

class EggBornServerCommand : public IServerCommand
{
    SERVERCOMMAND_META

    public:
    static IServerCommand* factory(std::string const& str)
    {
        std::stringstream ss(str);
        std::string cmd;
        int egg;

        ss.exceptions(std::ios_base::failbit);
        ss >> cmd;
        
        if (cmd != "ebo")
            return 0;

        ss >> egg;
        if (!ss.eof())
            return 0;

        return new EggBornServerCommand(egg);
    }

    EggBornServerCommand(int egg_arg)
        : egg(egg_arg)
    {
    }

    int const egg;
};

#endif

