#include "Future.hpp"

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
    
void _Future::cancel() {
    mTask->cancel();
}

}
