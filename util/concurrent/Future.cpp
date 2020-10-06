#include "Future.hpp"
#include "Error.hpp"

namespace obotcha {

_Future::_Future(FutureTask t) {
    mTask = t;
}

void _Future::wait() {
    mTask->wait();
}
    
void _Future::wait(long t) {
    mTask->wait(t);
}
    
int _Future::cancel() {
    mTask->cancel();
    return 0;
}

_Future::~_Future() {
    mTask = nullptr;
}

}
