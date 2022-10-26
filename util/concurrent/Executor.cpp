#include "Executor.hpp"
#include "AutoLock.hpp"
#include "ExecutorTask.hpp"
#include "Future.hpp"

namespace obotcha {

ThreadLocal<ExecutorTask> _Executor::ExecutorTasks = createThreadLocal<sp<_ExecutorTask>>();;

_Executor::_Executor() {
    mStatus = createAtomicInteger(Idle);
    mMaxPendingTaskNum = 0;
    mDefaultThreadNum = 0;
    mMaxThreadNum = 0;
    mMinThreadNum = 0;
    mMaxNoWorkingTime = 0;
    mMaxSubmitTaskWaitTime = 0;
}

bool _Executor::isExecuting() {
    return mStatus->get() == Executing;
}

bool _Executor::isShutDown() {
    return mStatus->get() == ShutDown;
}

void _Executor::updateStatus(int s) {
    mStatus->set(s);
}

int _Executor::getMaxPendingTaskNum() {
    return mMaxPendingTaskNum;
}

int _Executor::getDefaultThreadNum() {
    return mDefaultThreadNum;
}

int _Executor::getMaxThreadNum() {
    return mMaxThreadNum;
}

int _Executor::getMinThreadNum() {
    return mMinThreadNum;
}

uint32_t _Executor::getMaxNoWorkingTime() {
    return mMaxNoWorkingTime;
}

uint32_t _Executor::getMaxSubmitTaskWaitTime() {
    return mMaxSubmitTaskWaitTime;
}

ExecutorTask _Executor::getCurrentTask() {
    return ExecutorTasks->get();
}

void _Executor::setCurrentTask(sp<_ExecutorTask> task) {
    ExecutorTasks->set(task);
}

void _Executor::removeCurrentTask() {
    ExecutorTasks->remove();
}

} // namespace obotcha