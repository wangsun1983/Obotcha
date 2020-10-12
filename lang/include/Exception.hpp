#ifndef __OBOTCHA_EXCEPTION_HPP__
#define __OBOTCHA_EXCEPTION_HPP__

#include <stdio.h>
#include <exception>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"

namespace obotcha {

class Exception;

#define DECLARE_EXCEPTION(V) \
class V;\
template<typename... Args>\
void throw##V(Args&&... args) { \
    printf("\n-------%s START-------- \n[File]:%s\n[Line]:%d \n",#V,__FILE__,__LINE__);\
    throw V(std::forward<Args>(args)...);\
}\
class V:public Exception


class Exception :public std::exception{
public:
    Exception(const char *);

    Exception(String);

    Exception(int);

    Exception(){}

    String getErrInfo();   

    void printStack();

protected:
    String mErrInfo;
};

}

#endif
