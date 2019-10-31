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
#include "AutoMutex.hpp"
#include "Error.hpp"
#include "System.hpp"
#include "StackTrace.hpp"
#include "ExecutorDestructorException.hpp"

namespace obotcha {


//============= PriorityPoolThread =================
_PriorityPoolThread::_PriorityPoolThread(ArrayList<PriorityTask> l,Mutex m,Condition c,_PriorityPoolExecutor *exe) {
    mTasks = l;

    mMutex = m;

    mStop = false;

    mState = idleState;

    mCondition = c;
    
    mWaitTermCondition = createCondition();

    mExecutor = exe;

    mStateMutex = createMutex(createString("PriorityStateMutex"));

    mExecutorMutex = createMutex(createString("PriorityPoolExecutorMutex"));
}

void _PriorityPoolThread::onExecutorDestroy() {
    AutoMutex ll(mExecutorMutex);
    mExecutor = nullptr;
}

void _PriorityPoolThread::run() {
    while(!mStop) {
        mCurrentTask = nullptr;
        while(1) {
            AutoMutex l(mMutex);
            if(mTasks->size() == 0) {
                mCondition->wait(mMutex);
                continue;
            }
            mCurrentTask = mTasks->remove(0);
            break;
        }

        if(mCurrentTask == nullptr) {
            break;
        }

        if(mCurrentTask->task->getStatus() == FUTURE_CANCEL) {
            continue;
        }
        {    
            AutoMutex l(mStateMutex);
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
            AutoMutex l(mStateMutex);
            mState = idleState;
            if(mCurrentTask->task->getType() == FUTURE_TASK_SUBMIT) {
                mCurrentTask->task->onComplete();
            }
        }
    }
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, nullptr);
    {
        AutoMutex l(mStateMutex);
        mState = terminateState;
        mWaitTermCondition->notify();
    }
    
    {
        AutoMutex ll(mExecutorMutex);
        if(mExecutor != nullptr) {
            mExecutor->onHandlerRelease();
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
        AutoMutex l(mStateMutex);
        mState = terminateState;
        mWaitTermCondition->notify();
    } 

    {
        AutoMutex ll(mExecutorMutex);
        if(mExecutor != nullptr) {
            mExecutor->onHandlerRelease();
        }
    }
}

void _PriorityPoolThread::waitTermination(long interval) {
    if(mState == terminateState) {
        return;
    }
    AutoMutex l(mStateMutex);
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

    mPriorityTasks = createArrayList<PriorityTask>();
    mThreads = createArrayList<PriorityPoolThread>();
    for(int i = 0;i < threadnum;i++) {

        PriorityPoolThread thread = createPriorityPoolThread(mPriorityTasks,mDataLock,mDataCond,this);
       
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
        AutoMutex l(mProtectMutex);

        if(isShutDown) {
            return 0;
        }

        isShutDown = true;

        int size = mThreads->size();
        for(int i = 0;i < size;i++) {
            mThreads->get(i)->stop();
        }
    }
    
    {
        AutoMutex ll(mDataLock);
        ListIterator<PriorityTask> iterator = mPriorityTasks->getIterator();
        while(iterator->hasValue()) {
            PriorityTask priTask = iterator->getValue();
            priTask->task->cancel();
            iterator->next();
        }
        mPriorityTasks->clear();
    }

    startWaitTerminate();
}

bool _PriorityPoolExecutor::isShutdown() {
    return isShutDown;
}

bool _PriorityPoolExecutor::isTerminated() {
    if(isTermination) {
        return true;
    }

    AutoMutex l(mProtectMutex);

    if(isTermination) {
        return true;
    }

    int size = mThreads->size();
    for(int i = 0;i < size;i++) {
        if(mThreads->get(i)->getStatus() != terminateState) {
            return false;
        }
    }

    isTermination = true;
    return true;
}

int _PriorityPoolExecutor::awaitTermination(long millseconds) {
    if(!isShutDown) {
        return -InvalidStatus;
    }
    if(isTermination) {
        return 0;
    }
    int size = mThreads->size();

    if(millseconds == 0) {
        for(int i = 0;i < size;i++) {
            mThreads->get(i)->waitTermination(0);
        }

        isTermination = true;
        return 0;
    } else {
        for(int i = 0;i < size;i++) {
            long current = st(System)::currentTimeMillis();
            if(millseconds > 0) {
                mThreads->get(i)->waitTermination(millseconds);
                
            } else {
                break;
            }
            millseconds -= (st(System)::currentTimeMillis() - current);
        }

        if(millseconds <= 0) {
            return -WaitTimeout;
        }
    }

    return 0;
}

Future _PriorityPoolExecutor::submit(Runnable task) {
    return submit(TaskPriorityMedium,task);
}

Future _PriorityPoolExecutor::submit(int level,Runnable task) {
    if(isShutDown || isTermination) {
        return nullptr;
    }
    
    AutoMutex l(mProtectMutex);
    
    if(isShutDown || isTermination) {
        return nullptr;
    }

    AutoMutex ll(mDataLock);
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

    FutureTask futureTask = createFutureTask(FUTURE_TASK_SUBMIT,task);
    mPriorityTasks->insert(index,createPriorityTask(level,futureTask));

    mDataCond->notify();

    return createFuture(futureTask);
}

int _PriorityPoolExecutor::getThreadsNum() {
    AutoMutex ll(mProtectMutex);
    return mThreads->size();
}

void _PriorityPoolExecutor::onHandlerRelease() {
    AutoMutex ll(mProtectMutex);
    mThreadNum--;

    if(mThreadNum == 0) {
        mThreads->clear();
    }

    finishWaitTerminate();
}

void _PriorityPoolExecutor::onCancel(FutureTask) {
    //TODO
    
}

_PriorityPoolExecutor::~_PriorityPoolExecutor() {
    int size = mThreads->size();

    for(int i = 0;i < size;i++) {
        mThreads->get(i)->onExecutorDestroy();
    }

    //shutdown();
    if(!isShutDown) {
        throw createExecutorDestructorException("Priority Thread Pool destruct error");
    }

}

//============== PriorityTask ================
_PriorityTask::_PriorityTask(int level ,FutureTask f) {
    priority = level;
    task = f;
}

}
