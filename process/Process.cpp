#include <syscall.h>

#include "Process.hpp"
#include "Thread.hpp"

namespace obotcha {

_Process::_Process() {
    //Nothing
}

int _Process::getThreadPriority() {
    Thread thread = st(Thread)::current();
    return (thread == nullptr)?-1:thread->getPriority();
}

void _Process::setThreadPriority(int priority) {
    Thread thread = st(Thread)::current();
    if (thread != nullptr) {
        thread->setPriority(priority);
    }
}

int _Process::myPid() {
    return getpid();
}

int _Process::myTid() {
    return syscall(SYS_gettid);
}

}
