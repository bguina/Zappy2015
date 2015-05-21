
#ifndef HPP_BADPARAMETERSERVERCOMMAND
#define HPP_BADPARAMETERSERVERCOMMAND

#include "IServerCommand.hpp"

class BadParameterServerCommand : public IServerCommand
{
    SERVERCOMMAND_META

    public:
    static IServerCommand* factory(std::string const& str)
    {
        if (str != "sbp")
            return 0;
        return new BadParameterServerCommand();
    }
};

#endif

