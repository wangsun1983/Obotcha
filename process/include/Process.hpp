#ifndef __OBOTCHA_PROCESS_HPP__
#define __OBOTCHA_PROCESS_HPP__

#include "Object.hpp"

namespace obotcha {

DECLARE_CLASS(Process) {
public:
    _Process();
    static int GetThreadPriority();
    static void SetThreadPriority(int);
    static int MyPid();
    static int MyTid();
};

}
#endif
