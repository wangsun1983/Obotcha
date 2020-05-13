#include <stdio.h>
#include <pthread.h>
#include <map>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Runnable.hpp"
#include "Executor.hpp"
#include "ArrayList.hpp"
#include "Future.hpp"
#include "Executor.hpp"
#include "Callable.hpp"
#include "ConcurrentQueue.hpp"
#include "ExecutorService.hpp"
#include "PriorityPoolExecutor.hpp"
#include "AutoLock.hpp"
#include "Error.hpp"
#include "System.hpp"
#include "StackTrace.hpp"
#include "ExecutorDestructorException.hpp"
#include "Log.hpp"

namespace obotcha {

#define TAG "PriorityPool"

//============= PriorityPoolThread =================
_PriorityPoolThread::_PriorityPoolThread(ArrayList<PriorityTask> l,Mutex m,Condition c,sp<_PriorityPoolExecutor> exe) {
    mTasks = l;

    mMutex = m;

    mStop = false;

    mState = idleState;

    mCondition = c;
    
    mWaitTermCondition = createCondition();

    mExecutor = exe;

    mStateMutex = createMutex("PriorityStateMutex");

    mExecutorMutex = createMutex("PriorityPoolExecutorMutex");
}

void _PriorityPoolThread::run() {
    while(!mStop) {
        mCurrentTask = nullptr;
        while(1) {
            AutoLock l(mMutex);
            if(mTasks->size() == 0) {
                mCondition->wait(mMutex);
                continue;
            }
            mCurrentTask = mTasks->removeAt(0);
            break;
        }

        if(mCurrentTask == nullptr) {
            break;
        }

        if(mCurrentTask->task->getStatus() == FUTURE_CANCEL) {
            continue;
        }
        {    
            AutoLock l(mStateMutex);
            mState = busyState;
            if(mCurrentTask->task->getType() == FUTURE_TASK_SUBMIT) {
                mCurrentTask->task->onRunning();
            }
        }
        Runnable runnable = mCurrentTask->task->getRunnable();
        if(runnable != nullptr) {
            runnable->run();    
        }
        {
            AutoLock l(mStateMutex);
            mState = idleState;
            if(mCurrentTask->task->getType() == FUTURE_TASK_SUBMIT) {
                mCurrentTask->task->onComplete();
            }
        }
    }
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, nullptr);
    {
        AutoLock l(mStateMutex);
        mState = terminateState;
        mWaitTermCondition->notify();
    }
    
    {
        AutoLock ll(mExecutorMutex);
        if(mExecutor != nullptr) {
            PriorityPoolThread thread;
            thread.set_pointer(this);
            mExecutor->onCompleteNotify(thread);
            mExecutor.remove_pointer();
        }
    }
}

void _PriorityPoolThread::onInterrupt() {
    if(mCurrentTask != nullptr) {
        Runnable r = mCurrentTask->task->getRunnable();
        if(r != nullptr) {
            r->onInterrupt();
        }
        mCurrentTask = nullptr;
        r = nullptr;
    }

    {
        AutoLock l(mStateMutex);
        mState = terminateState;
        mWaitTermCondition->notify();
    } 

    {
        AutoLock ll(mExecutorMutex);
        if(mExecutor != nullptr) {
            PriorityPoolThread thread;
            thread.set_pointer(this);
            mExecutor->onCompleteNotify(thread);
            mExecutor.remove_pointer();
        }
    }
}

void _PriorityPoolThread::waitTermination(long interval) {
    if(mState == terminateState) {
        return;
    }
    AutoLock l(mStateMutex);
    if(mState == terminateState) {
        return;
    }

    if(interval == 0) {
        mWaitTermCondition->wait(mStateMutex);
    } else {
        mWaitTermCondition->wait(mStateMutex,interval);
    }
    //this->join();
}

bool _PriorityPoolThread::foceStopTask(FutureTask t) {
    if(mCurrentTask != nullptr && mCurrentTask->task == t) {
        stop();
        return true;
    }

    return false;
}

_PriorityPoolThread::~_PriorityPoolThread() {
}

void _PriorityPoolThread::stop() {
    mStop = true;
    this->quit();
}

//============= PriorityPoolExecutor ================
_PriorityPoolExecutor::_PriorityPoolExecutor():_PriorityPoolExecutor{
                                      st(System)::availableProcessors()} {
    //do nothing
}

_PriorityPoolExecutor::_PriorityPoolExecutor(int threadnum) {
    mProtectMutex = createMutex("PriorityMutex");
    mDataLock = createMutex("PriorityData");
    mDataCond = createCondition();
    mWaitMutex = createMutex("PriorityWaitMutex");
    mWaitCondition = createCondition();

    mPriorityTasks = createArrayList<PriorityTask>();

    mThreadMutex = createMutex("PriorityThread Mutex");
    mThreads = createArrayList<PriorityPoolThread>();

    PriorityPoolExecutor exe;
    exe.set_pointer(this);

    mThreadNum = threadnum;
    for(int i = 0;i < threadnum;i++) {
        PriorityPoolThread thread = createPriorityPoolThread(mPriorityTasks,mDataLock,mDataCond,exe);
        thread->start();
        mThreads->add(thread);
    }
    
    isShutDown = false;
    isTermination = false;

}

int _PriorityPoolExecutor::execute(Runnable r) {
    return execute(TaskPriorityMedium,r);
}

int _PriorityPoolExecutor::execute(int level,Runnable r) {
    if(submit(level,r) == nullptr) {
        return -InvalidStatus;
    }

    return 0;
}

int _PriorityPoolExecutor::shutdown() {
    if(isShutDown) {
        return 0;
    }

    {
        AutoLock l(mProtectMutex);

        if(isShutDown) {
            return 0;
        }

        isShutDown = true;

        AutoLock ll(mThreadMutex);
        ListIterator<PriorityPoolThread> iterator = mThreads->getIterator();
        while(iterator->hasValue()) {
            PriorityPoolThread thread = iterator->getValue();
            thread->stop();
            iterator->next();
        }
    }
    
    {
        AutoLock ll(mDataLock);
        ListIterator<PriorityTask> iterator = mPriorityTasks->getIterator();
        while(iterator->hasValue()) {
            PriorityTask priTask = iterator->getValue();
            priTask->task->cancel();
            iterator->next();
        }
        mPriorityTasks->clear();
    }

    //startWaitTerminate();
}

bool _PriorityPoolExecutor::isTerminated() {
    return isTermination;
}

void _PriorityPoolExecutor::awaitTermination() {
    awaitTermination(0);
}

int _PriorityPoolExecutor::awaitTermination(long millseconds) {
    if(!isShutDown) {
        return -InvalidStatus;
    }

    if(isTermination) {
        return 0;
    }
    
    AutoLock ll(mWaitMutex);
    if(isTermination) {
        return 0;
    }

    return mWaitCondition->wait(mWaitMutex,millseconds);
}

Future _PriorityPoolExecutor::submit(Runnable task) {
    return submit(TaskPriorityMedium,task);
}

Future _PriorityPoolExecutor::submit(int level,Runnable task) {
    if(isShutDown || isTermination) {
        return nullptr;
    }
    
    AutoLock l(mProtectMutex);
    
    if(isShutDown || isTermination) {
        return nullptr;
    }

    AutoLock ll(mDataLock);
    int start = 0;
    int end = mPriorityTasks->size() - 1;
    int index = 0;
    while(start <= end) {
        index = (start+end)/2;
        PriorityTask m = mPriorityTasks->get(index);
        if(level > m->priority) {
            end = index - 1;
        } else if(level < m->priority) {
            start = index + 1;
        } else if(m->priority == level) {
            break;
        }
    }

    FutureTaskStatusListener listener;
    listener.set_pointer(this);

    FutureTask futureTask = createFutureTask(FUTURE_TASK_SUBMIT,task,listener);
    mPriorityTasks->insert(index,createPriorityTask(level,futureTask));

    mDataCond->notify();

    return createFuture(futureTask);
}

int _PriorityPoolExecutor::getThreadsNum() {
    AutoLock ll(mProtectMutex);
    return mThreads->size();
}

void _PriorityPoolExecutor::onCompleteNotify(PriorityPoolThread t){
    AutoLock ll(mThreadMutex);
    ListIterator<PriorityPoolThread> iterator = mThreads->getIterator();
    while(iterator->hasValue()) {
        PriorityPoolThread thread = iterator->getValue();
        if(thread == t) {
            iterator->remove();
            break;
        }
        iterator->next();
    }

    if(mThreads->size() == 0) {
        mThreads->clear();
        AutoLock ll(mWaitMutex);
        isTermination = true;
        mWaitCondition->notifyAll();
    }
}

void _PriorityPoolExecutor::onCancel(FutureTask task) {
    if(isShutDown ||isTermination) {
        return;
    }

    AutoLock l(mProtectMutex);

    if(isTermination ||isTermination) {
        return;
    }

    {
        AutoLock ll(mDataLock);
        ListIterator<PriorityTask> iterator = mPriorityTasks->getIterator();
        while(iterator->hasValue()) {
            PriorityTask t = iterator->getValue();
            if(t->task == task) {
                iterator->remove();
                return;
            }
            iterator->next();
        }
    }
    
    {
        bool isNeedCreate = false;
        AutoLock ll(mThreadMutex);
        ListIterator<PriorityPoolThread> iterator = mThreads->getIterator();
        while(iterator->hasValue()) {
            PriorityPoolThread thread = iterator->getValue();
            
            if(thread->foceStopTask(task)) {
                isNeedCreate = true;
                iterator->remove();
                break;
            }

            iterator->next();
        }
        
        if(isNeedCreate) {
            PriorityPoolExecutor exe;
            exe.set_pointer(this);

            PriorityPoolThread thread = createPriorityPoolThread(mPriorityTasks,mDataLock,mDataCond,exe);
            thread->start();
            mThreads->add(thread);
        }
    }

}

_PriorityPoolExecutor::~_PriorityPoolExecutor() {
    
    if(!isShutDown) {
        //cannot throw exception in destructor
        //throw ExecutorDestructorException("Priority Thread Pool destruct error");
        LOGE(TAG,"Priority Thread Pool destruct error");
    }

}

//============== PriorityTask ================
_PriorityTask::_PriorityTask(int level ,FutureTask f) {
    priority = level;
    task = f;
}

}
