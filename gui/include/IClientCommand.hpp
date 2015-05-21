
#ifndef HPP_ICLIENTCOMMAND
#define HPP_ICLIENTCOMMAND

#include <string>

class IClientCommand
{
    public:
    virtual std::string serialize() const = 0;
};

#endif

