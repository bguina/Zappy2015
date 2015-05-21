
#ifndef HPP_ERRNOEXCEPTION
#define HPP_ERRNOEXCEPTION

#include <stdexcept>
#include <cstring>

class ErrnoException : public std::runtime_error
{
    public:
    ErrnoException(std::string const& what_arg, int errcode)
        : std::runtime_error(what_arg), m_errcode(errcode)
    {
    }

    int errcode() const
    {
        return m_errcode;
    }

    protected:
    int m_errcode;
};

#endif

