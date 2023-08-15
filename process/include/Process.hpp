#ifndef __OBOTCHA_PROCESS_HPP__
#define __OBOTCHA_PROCESS_HPP__

#include "Object.hpp"
#include "Thread.hpp"

namespace obotcha {

DECLARE_CLASS(Process) {
public:
    _Process() = default;
    static st(Thread)::Priority GetThreadPriority();
    static void SetThreadPriority(st(Thread)::Priority);
    static int MyPid();
    static long MyTid();
};

}
#endif
