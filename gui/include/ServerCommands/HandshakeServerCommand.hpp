
#ifndef HPP_HANDSHAKESERVERCOMMAND
#define HPP_HANDSHAKESERVERCOMMAND

#include "IServerCommand.hpp"

class HandshakeServerCommand : public IServerCommand
{
    SERVERCOMMAND_META

    public:
    static IServerCommand* factory(std::string const& str)
    {
        if (str != "BIENVENUE")
            return 0;
        return new HandshakeServerCommand();
    }
};

#endif

