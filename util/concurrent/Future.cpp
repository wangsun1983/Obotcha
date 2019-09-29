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
    int result = 0;
    if(mTask->getStatus() != FUTURE_WAITING) {
        result = -InvalidStatus;
    }

    mTask->cancel();
    return result;
}

_Future::~_Future() {
    mTask = nullptr;
}

}
