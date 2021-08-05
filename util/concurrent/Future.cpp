/**
 * @file Future.cpp
 * @brief Future represents the result of an asynchronous computation
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */

#include "Future.hpp"
#include "Error.hpp"

namespace obotcha {

_Future::_Future(ExecutorTask t) {
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
}

}
