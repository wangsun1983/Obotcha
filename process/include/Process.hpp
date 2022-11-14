#ifndef __OBOTCHA_PROCESS_HPP__
#define __OBOTCHA_PROCESS_HPP__

#include "Object.hpp"

namespace obotcha {

DECLARE_CLASS(Process) {
public:
    _Process();
    static int getThreadPriority();
    static void setThreadPriority(int);
    static int myPid();
    static int myTid();
};

}
#endif
