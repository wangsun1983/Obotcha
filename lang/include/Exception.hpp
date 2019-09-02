#ifndef __EXCEPTION_HPP__
#define __EXCEPTION_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Exception) {
public:
    _Exception(const char *);

    _Exception(String);

    _Exception(int);

    virtual String getErrInfo();   

    virtual int getErrCode();

    void printStack();

protected:
    String mErrInfo;

    int mErrCode;
};

}

#endif
