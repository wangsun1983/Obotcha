#include "ExecutorTask.hpp"
#include "AutoLock.hpp"
#include "ExecutorResult.hpp"
#include "Synchronized.hpp"

namespace obotcha {

_ExecutorTask::_ExecutorTask(Runnable r) {
    this->mRunnable = r;
    mMutex = createMutex("ExecutorTaskMutex");
    mCompleteCond = createCondition();
    mStatus = Idle;
    mResult = createExecutorResult();
}

_ExecutorTask::_ExecutorTask(Runnable r,int delay,int priority):_ExecutorTask(r) {
    mDelay = delay;
    mPriority = priority;
}

_ExecutorTask::~_ExecutorTask() { 
    this->mRunnable = nullptr; 
}

int _ExecutorTask::wait(long interval) {
    AutoLock l(mMutex);
    if (mStatus == Complete || mStatus == Cancel) {
        return -1;
    }
    return mCompleteCond->wait(mMutex, interval);
}

void _ExecutorTask::cancel() {
    AutoLock l(mMutex);
    if (mStatus == Cancel || mStatus == Complete) {
        return;
    }
    
    if (mRunnable != nullptr) {
        bool ret = mRunnable->onInterrupt();
        if(!ret && mStatus == Running) {
            return;
        }
    }
    
    mStatus = Cancel;

    mCompleteCond->notify();
    mRunnable = nullptr;
}

int _ExecutorTask::getStatus() {
    AutoLock l(mMutex);
    return mStatus;
}

void _ExecutorTask::setPending() {
    AutoLock l(mMutex);
    mStatus = Pending;
}

void _ExecutorTask::execute() {
    Runnable r = nullptr;

    Synchronized(mMutex) {
        if (mStatus == Complete || mStatus == Cancel) {
            return;
        }

        mStatus = Running;
        r = mRunnable;
    }

    st(Executor)::setCurrentTask(AutoClone(this));
    
    if (r != nullptr) {
        r->run();
    }

    st(Executor)::removeCurrentTask();

    Synchronized(mMutex) {
        mStatus = Complete;
        mCompleteCond->notify();
    }
}

Runnable _ExecutorTask::getRunnable() { 
    return mRunnable; 
}

//Priority
void _ExecutorTask::setPriority(int prio) {
    this->mPriority = prio;
}

int _ExecutorTask::getPriority() {
    return mPriority;
}

//Delay
void _ExecutorTask::setDelay(int delay) {
    mDelay = delay;
}

int _ExecutorTask::getDelay() {
    return mDelay;
}

} // namespace obotcha
