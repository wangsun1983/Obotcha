#include "Executor.hpp"
#include "ExecutorTask.hpp"
#include "Future.hpp"

namespace obotcha {

ThreadLocal<ExecutorTask> _Executor::ExecutorTasks = createThreadLocal<sp<_ExecutorTask>>();;

_Executor::_Executor() {
    mStatus = st(Concurrent)::Status::Idle;
}

bool _Executor::isExecuting() {
    return mStatus == st(Concurrent)::Status::Running;
}

bool _Executor::isShutDown() {
    return mStatus == st(Concurrent)::Status::ShutDown;
}

void _Executor::updateStatus(st(Concurrent)::Status s) {
    mStatus = s;
}

int _Executor::getMaxPendingTaskNum() const {
    return mMaxPendingTaskNum;
}

int _Executor::getDefaultThreadNum() const {
    return mDefaultThreadNum;
}

int _Executor::getMaxThreadNum() const {
    return mMaxThreadNum;
}

int _Executor::getMinThreadNum() const {
    return mMinThreadNum;
}

uint32_t _Executor::getMaxNoWorkingTime() const {
    return mMaxNoWorkingTime;
}

uint32_t _Executor::getMaxSubmitTaskWaitTime() const {
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

sp<_Future> _Executor::submitRunnable(Runnable r,int delay,st(Concurrent)::TaskPriority priority) {
    auto task = createExecutorTask(r,
                                  std::bind(&_Executor::onRemoveTask,
                                           this,
                                           std::placeholders::_1),
                                delay,priority);
    return this->submitTask(task);
}

} // namespace obotcha