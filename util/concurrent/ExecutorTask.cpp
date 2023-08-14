#include "ExecutorTask.hpp"
#include "AutoLock.hpp"
#include "ExecutorResult.hpp"
#include "Synchronized.hpp"

namespace obotcha {

_ExecutorTask::_ExecutorTask(Runnable r,const RemoveFunction func):mRunnable(r),mRemoveFunction(func) {
    mResult = createExecutorResult();
}

_ExecutorTask::_ExecutorTask(Runnable r,const RemoveFunction func,long delay,int priority):_ExecutorTask(r,func) {
    mDelay = delay;
    mPriority = priority;
}

_ExecutorTask::~_ExecutorTask() { 
    this->mRunnable = nullptr; 
}

int _ExecutorTask::wait(long interval) {
    AutoLock l(mMutex);
    if (mStatus == _ExecutorTask::Status::Complete 
      || mStatus == _ExecutorTask::Status::Cancel) {
        return -1;
    }
    return mCompleteCond->wait(mMutex, interval);
}

void _ExecutorTask::cancel() {
    AutoLock l(mMutex);
    if (mStatus == _ExecutorTask::Status::Cancel 
        || mStatus == _ExecutorTask::Status::Complete) {
        return;
    }
    
    if (mRunnable != nullptr) {
        bool ret = mRunnable->onInterrupt();
        if(!ret && mStatus == _ExecutorTask::Status::Running) {
            return;
        }
    }
    
    mStatus = _ExecutorTask::Status::Cancel;

    if(mRemoveFunction != nullptr) {
        mRemoveFunction(AutoClone(this));
        mRemoveFunction = nullptr;
    }

    mCompleteCond->notify();
    mRunnable = nullptr;
}

_ExecutorTask::Status _ExecutorTask::getStatus() {
    AutoLock l(mMutex);
    return mStatus;
}

void _ExecutorTask::setPending() {
    AutoLock l(mMutex);
    mStatus = _ExecutorTask::Status::Pending;
}

void _ExecutorTask::execute() {
    Runnable r = nullptr;

    Synchronized(mMutex) {
        if (mStatus == _ExecutorTask::Status::Complete 
            || mStatus == _ExecutorTask::Status::Cancel) {
            return;
        }

        mStatus = _ExecutorTask::Status::Running;
        r = mRunnable;
    }

    st(Executor)::setCurrentTask(AutoClone(this));
    
    if (r != nullptr) {
        r->run();
    }

    st(Executor)::removeCurrentTask();

    Synchronized(mMutex) {
        mStatus = _ExecutorTask::Status::Complete;
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

int _ExecutorTask::getPriority() const {
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
