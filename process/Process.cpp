#include <syscall.h>

#include "Process.hpp"
#include "Thread.hpp"

namespace obotcha {

_Process::_Process() {
    //Nothing
}

int _Process::GetThreadPriority() {
    Thread thread = st(Thread)::current();
    return (thread == nullptr)?-1:thread->getPriority();
}

void _Process::SetThreadPriority(int priority) {
    Thread thread = st(Thread)::current();
    if (thread != nullptr) {
        thread->setPriority(priority);
    }
}

int _Process::MyPid() {
    return getpid();
}

int _Process::MyTid() {
    return syscall(SYS_gettid);
}

}
