#include <syscall.h>

#include "Process.hpp"
#include "Thread.hpp"

namespace obotcha {

st(Thread)::Priority _Process::GetThreadPriority() {
    Thread thread = st(Thread)::current();
    return (thread == nullptr)?st(Thread)::Priority::Error:
                               thread->getPriority();
}

void _Process::SetThreadPriority(st(Thread)::Priority priority) {
    Thread thread = st(Thread)::current();
    if (thread != nullptr) {
        thread->setPriority(priority);
    }
}

int _Process::MyPid() {
    return getpid();
}

long _Process::MyTid() {
    return syscall(SYS_gettid);
}

}
