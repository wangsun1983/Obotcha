#ifndef __OBOTCHA_EXECUTOR_HPP__
#define __OBOTCHA_EXECUTOR_HPP__

#include <pthread.h>
#include <map>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Runnable.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Executor) {

public:
    virtual int execute(Runnable command) = 0;
};

}
#endif