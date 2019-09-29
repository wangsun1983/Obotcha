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
        //printf("priority thread start \n");
        while(1) {
            //printf("priority thread start0,pthread is %x \n",mPthread);
            AutoMutex l(mMutex);
            //printf("priority thread start1 \n");
            if(mTasks->size() == 0) {
                mCondition->wait(mMutex);
                //printf("priority thread start2 \n");
                continue;
            }
            //printf("priority thread start3 \n");
            mCurrentTask = mTasks->remove(0);
            //printf("priority thread start4 \n");
            break;
        }

        //printf("priority thread start5 \n");

        if(mCurrentTask == nullptr) {
            break;
        }

        if(mCurrentTask->task->getStatus() == FUTURE_CANCEL) {
            continue;
        }
        //printf("priority thread trae2 \n");
        {    
            AutoMutex l(mStateMutex);
            mState = busyState;
            if(mCurrentTask->task->getType() == FUTURE_TASK_SUBMIT) {
                mCurrentTask->task->onRunning();
            }
        }
        //printf("priority thread trae3 \n");
        Runnable runnable = mCurrentTask->task->getRunnable();
        if(runnable != nullptr) {
            runnable->run();    
        }
        //printf("priority thread trae4 \n");
        {
            AutoMutex l(mStateMutex);
            mState = idleState;
            //printf("priority thread trae5 \n");
            if(mCurrentTask->task->getType() == FUTURE_TASK_SUBMIT) {
                mCurrentTask->task->onComplete();
            }
        }
    }
    //printf("priority thread trae6 \n");
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, nullptr);
    {
        //printf("priority thread trae7 \n");
        AutoMutex l(mStateMutex);
        //printf("priority thread trae8 \n");
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
    //st(StackTrace)::dumpStack(createString("oninterrupt"));
    if(mCurrentTask != nullptr) {
        Runnable r = mCurrentTask->task->getRunnable();
        if(r != nullptr) {
            r->onInterrupt();
        }
        mCurrentTask = nullptr;
        r = nullptr;
    }

    //printf("priority onInterrupt,this is %lx \n",this);
    {
        AutoMutex l(mStateMutex);
        //printf("priority onInterrupt2 \n");
        mState = terminateState;
        mWaitTermCondition->notify();
    }
    //printf("priority onInterrupt4 \n");  

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
    //printf("thread waitTermination start \n");
    AutoMutex l(mStateMutex);
    //printf("thread waitTermination start2 \n");
    if(mState == terminateState) {
        return;
    }

    if(interval == 0) {
        //printf("thread waitTermination start3 \n");
        mWaitTermCondition->wait(mStateMutex);
        //printf("thread waitTermination start4 \n");
    } else {
        //printf("thread waitTermination start5,mPhtread is %x \n",mPthread);
        mWaitTermCondition->wait(mStateMutex,interval);
        //printf("thread waitTermination start6 \n");
    }

    //this->join();
}

_PriorityPoolThread::~_PriorityPoolThread() {
    //printf("_PriorityPoolThread~~~~ \n");
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
    //printf("priority pool threanum is %d \n",st(System)::availableProcessors());
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
            //printf("cancel task is %x \n",priTask->task->getRunnable().get_pointer());
            priTask->task->cancel();
            iterator->next();
        }
        mPriorityTasks->clear();
    }

    
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
    //printf("awaitTermination trace111111 \n");
    if(!isShutDown) {
        return -InvalidStatus;
    }
    //printf("awaitTermination trace2 \n");
    if(isTermination) {
        return 0;
    }
    //printf("awaitTermination trace3 \n");
    int size = mThreads->size();

    if(millseconds == 0) {
        for(int i = 0;i < size;i++) {
            //printf("awaitTermination trace4 \n");
            mThreads->get(i)->waitTermination(0);
            //printf("awaitTermination trace5\n");
        }

        isTermination = true;
        return 0;
    } else {
        for(int i = 0;i < size;i++) {
            long current = st(System)::currentTimeMillis();
            if(millseconds > 0) {
                //printf("wait Termination millseconds is %ld trac1 \n",millseconds);
                mThreads->get(i)->waitTermination(millseconds);
                //printf("wait Termination2 millseconds is %ld trac1 \n",millseconds);
               
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

    //printf("onHandler Release mThreadNum is %d \n",mThreadNum);
    if(mThreadNum == 0) {
        mThreads->clear();
    }
}

_PriorityPoolExecutor::~_PriorityPoolExecutor() {
    //printf("~_PriorityPoolExecutor \n");
    int size = mThreads->size();

    for(int i = 0;i < size;i++) {
        mThreads->get(i)->onExecutorDestroy();
    }

    shutdown();

}

//============== PriorityTask ================
_PriorityTask::_PriorityTask(int level ,FutureTask f) {
    priority = level;
    task = f;
}

}
