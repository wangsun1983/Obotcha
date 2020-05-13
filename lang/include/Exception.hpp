#ifndef __OBOTCHA_EXCEPTION_HPP__
#define __OBOTCHA_EXCEPTION_HPP__

#include <exception>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"

namespace obotcha {

class Exception :public std::exception{
public:
    Exception(const char *);

    Exception(String);

    Exception(int);

    virtual String getErrInfo();   

    virtual int getErrCode();

    void printStack();

    Exception * operator->();

protected:
    String mErrInfo;

    int mErrCode;
};

}

#endif
