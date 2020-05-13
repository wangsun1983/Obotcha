#ifndef __OBOTCHA_STACK_TRACE_HPP__
#define __OBOTCHA_STACK_TRACE_HPP__

#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(StackTrace) {
public:
    static void dumpStack(String);
};

}

#endif
