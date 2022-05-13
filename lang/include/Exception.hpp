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

#define Trigger(V,...) {\
  printf("---[Exception]:%s, [File]:%s, [Line]:%d ---\n",#V,__FILE__,__LINE__); \
  printf(__VA_ARGS__);\
  throw V();\
}

class Exception :public std::exception{
public:
    Exception();

    void printStack();
};

}

#endif
