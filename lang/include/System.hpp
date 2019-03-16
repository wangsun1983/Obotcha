#ifndef __SYSTEM_HPP__
#define __SYSTEM_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(System) {

public:
    static long int currentTimeMillis();
    static void exit(int);
    static int availableProcessors();
    static int onlineProcessors();
};

}
#endif