#ifndef __EXECUTOR_HPP__
#define __EXECUTOR_HPP__

#include <pthread.h>
#include <map>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Runnable.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Executor) {

public:
    virtual void execute(Runnable command) = 0;
};

}
#endif