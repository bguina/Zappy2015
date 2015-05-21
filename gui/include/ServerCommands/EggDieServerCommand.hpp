
#ifndef HPP_EGGDIESERVERCOMMAND
#define HPP_EGGDIESERVERCOMMAND

#include <sstream>

#include "IServerCommand.hpp"

class EggDieServerCommand : public IServerCommand
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
        
        if (cmd != "edi")
            return 0;

        ss >> egg;
        if (!ss.eof())
            return 0;

        return new EggDieServerCommand(egg);
    }

    EggDieServerCommand(int egg_arg)
        : egg(egg_arg)
    {
    }

    int const egg;
};

#endif

