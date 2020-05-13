#ifndef __OBOTCHA_FORK_JOIN_TASK_HPP__
#define __OBOTCHA_FORK_JOIN_TASK_HPP__

#include <stdio.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

DECLARE_CLASS(ForkJoinTask,1) {

public:
   virtual T compute() = 0;

private:
    T result;
    
};

}
#endif