/**
 * @file Executor.cpp
 * @brief An object that executes submitted Runnable tasks. This
 * interface provides a way of decoupling task submission from the
 * mechanics of how each task will be run, including details of thread
 * use, scheduling, etc.
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */

#include "Executor.hpp"
#include "ExecutorTask.hpp"
#include "Future.hpp"

namespace obotcha {

ThreadLocal<ExecutorTask> _Executor::gExecutorTasks = createThreadLocal<sp<_ExecutorTask>>();;

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

size_t _Executor::getMaxPendingTaskNum() const {
    return mMaxPendingTaskNum;
}

long _Executor::getDefaultThreadNum() const {
    return mDefaultThreadNum;
}

long _Executor::getMaxThreadNum() const {
    return mMaxThreadNum;
}

long _Executor::getMinThreadNum() const {
    return mMinThreadNum;
}

uint32_t _Executor::getMaxNoWorkingTime() const {
    return mMaxNoWorkingTime;
}

uint32_t _Executor::getMaxSubmitTaskWaitTime() const {
    return mMaxSubmitTaskWaitTime;
}

ExecutorTask _Executor::GetCurrentTask() {
    return gExecutorTasks->get();
}

void _Executor::SetCurrentTask(sp<_ExecutorTask> task) {
    gExecutorTasks->set(task);
}

void _Executor::RemoveCurrentTask() {
    gExecutorTasks->remove();
}

sp<_Future> _Executor::submitRunnable(Runnable r,long delay,st(Concurrent)::TaskPriority priority) {
    auto task = createExecutorTask(r,
                                  std::bind(&_Executor::onRemoveTask,
                                           this,
                                           std::placeholders::_1),
                                delay,priority);
    return this->submitTask(task);
}

} // namespace obotcha