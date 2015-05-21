
#ifndef HPP_ISERVERRESPONSE
#define HPP_ISERVERRESPONSE

#include "IServerCommand.hpp"

class IClientRequest;
class Connection;

class IServerResponse : public IServerCommand
{
    public:
    virtual IClientRequest const* request() const = 0;

    protected:
    friend class Connection;
    virtual void _set_request(IClientRequest const* request) = 0;
};

#endif

