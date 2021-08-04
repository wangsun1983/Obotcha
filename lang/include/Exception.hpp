#ifndef __OBOTCHA_EXCEPTION_HPP__
#define __OBOTCHA_EXCEPTION_HPP__

#include <stdio.h>
#include <exception>

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

class Exception;

#define DECLARE_EXCEPTION(V) \
class V:public Exception

void _translateException(char *buff,const char *err);
void _translateException(char *buff,String err);

#if EXPORT_EXCEPTION_INFO
#define Trigger(V,info) \
    char buff[256] = {0};\
    sprintf(buff,"\n-------%s START-------- \n[File]:%s \n[Line]:%d\n",#V,__FILE__,__LINE__);\
    printf("%s \n",buff);\
    _translateException(buff,info);\
    throw V(buff);
#else 
#define Trigger(V,info) \
    char buff[256] = {0};\
    sprintf(buff,"\n-------%s START-------- \n[File]:%s \n[Line]:%d\n",#V,__FILE__,__LINE__);\
    _translateException(buff,info);\
    throw V(buff);
#endif

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
