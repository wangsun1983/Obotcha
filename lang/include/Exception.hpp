#ifndef __OBOTCHA_EXCEPTION_HPP__
#define __OBOTCHA_EXCEPTION_HPP__

#include <stdio.h>
#include <exception>

namespace obotcha {

class Exception;

#define EXCEPTION_DEBUG 0

#define DECLARE_EXCEPTION(V) \
class V:public Exception

#if EXCEPTION_DEBUG
#define Trigger(V,...) {\
  printf("---Execption Detected!!!--- \n    Error info:");\
  printf(__VA_ARGS__);\
  printf("\n    [Exception]:%s, [File]:%s, [Line]:%d ---\n",#V,__FILE__,__LINE__); \
  printf("---Execption Dump Complete!!!--- \n");\
  throw V();\
}
#else
#define Trigger(V,...) {\
  throw V();\
}
#endif

#define Panic(Condition,V,...) { \
  if(Condition) { \
    Trigger(V,__VA_ARGS__);\
  }\
}

// #define NoException(x) try { \
//   x\
// } catch(...) {}

class Exception :public std::exception{
public:
    Exception() = default;

    void printStack() const;
};

}

#endif
