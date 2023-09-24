#include "ExecutorTask.hpp"
#include "AutoLock.hpp"
#include "ExecutorResult.hpp"
#include "Synchronized.hpp"

namespace obotcha {

_ExecutorTask::_ExecutorTask(Runnable r,const std::function<void(sp<_ExecutorTask>)> & func):mRunnable(r),mRemoveFunction(func) {
    mResult = createExecutorResult();
}

_ExecutorTask::_ExecutorTask(Runnable r,
                            const std::function<void(sp<_ExecutorTask>)>& func,
                            long delay,
                            st(Concurrent)::TaskPriority priority):_ExecutorTask(r,func) {
    mDelay = delay;
    mPriority = priority;
}

_ExecutorTask::~_ExecutorTask() { 
    this->mRunnable = nullptr; 
}

int _ExecutorTask::wait(long interval) {
    AutoLock l(mMutex);
    if (mStatus == st(Concurrent)::Status::Complete 
      || mStatus == st(Concurrent)::Status::Interrupt) {
        return -1;
    }
    return mCompleteCond->wait(mMutex, interval);
}

void _ExecutorTask::cancel() {
    AutoLock l(mMutex);
    if (mStatus == st(Concurrent)::Status::Interrupt 
        || mStatus == st(Concurrent)::Status::Complete) {
        return;
    }
    
    if (mRunnable != nullptr) {
        bool ret = mRunnable->onInterrupt();
        if(!ret && mStatus == st(Concurrent)::Status::Running) {
            return;
        }
    }
    
    mStatus = st(Concurrent)::Status::Interrupt;

    if(mRemoveFunction != nullptr) {
        mRemoveFunction(AutoClone(this));
        mRemoveFunction = nullptr;
    }

    mCompleteCond->notify();
    mRunnable = nullptr;
}

st(Concurrent)::Status _ExecutorTask::getStatus() {
    AutoLock l(mMutex);
    return mStatus;
}

void _ExecutorTask::setPending() {
    AutoLock l(mMutex);
    mStatus = st(Concurrent)::Status::WaitingStart;
}

void _ExecutorTask::execute() {
    Runnable r = nullptr;

    Synchronized(mMutex) {
        if (mStatus == st(Concurrent)::Status::Complete 
            || mStatus == st(Concurrent)::Status::Interrupt) {
            return;
        }

        mStatus = st(Concurrent)::Status::Running;
        r = mRunnable;
    }

    st(Executor)::SetCurrentTask(AutoClone(this));
    
    if (r != nullptr) {
        r->run();
    }

    st(Executor)::RemoveCurrentTask();

    Synchronized(mMutex) {
        mStatus = st(Concurrent)::Status::Complete;
        mCompleteCond->notify();
    }
}

Runnable _ExecutorTask::getRunnable() { 
    return mRunnable; 
}

//Priority
void _ExecutorTask::setPriority(st(Concurrent)::TaskPriority prio) {
    mPriority = prio;
}

st(Concurrent)::TaskPriority _ExecutorTask::getPriority() const {
    return mPriority;
}

//Delay
void _ExecutorTask::setDelay(long delay) {
    mDelay = delay;
}

long _ExecutorTask::getDelay() const {
    return mDelay;
}

} // namespace obotcha
