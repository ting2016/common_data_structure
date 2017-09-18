#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <exception>
#include <string>
namespace bloomberg_interview{
    class Exception : public std::exception{
    protected:
        std::string _what;
    public:
        Exception(std::string _what) : _what(_what){}
        const char* what() const noexcept {return _what.c_str();}
        ~Exception() throw(){}
    };
}

#endif // EXCEPTION_H
