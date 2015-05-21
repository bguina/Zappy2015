
#ifndef HPP_ISERVERCOMMAND
#define HPP_ISERVERCOMMAND

#include <string>

class IServerCommand
{
    public:
    typedef int ID;
    typedef IServerCommand* (*Factory)(std::string const&);

    virtual ID get_id() const = 0;
};

#define SERVERCOMMAND_META\
    public:\
    static IServerCommand::ID const id;\
    virtual IServerCommand::ID get_id() const { return id; }\
    private:

#endif

