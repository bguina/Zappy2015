
#ifndef HPP_UNKNOWNCOMMANDSERVERCOMMAND
#define HPP_UNKNOWNCOMMANDSERVERCOMMAND

#include "IServerCommand.hpp"

class UnknownCommandServerCommand : public IServerCommand
{
    SERVERCOMMAND_META

    public:
    static IServerCommand* factory(std::string const& str)
    {
        if (str != "suc")
            return 0;
        return new UnknownCommandServerCommand();
    }
};

#endif

