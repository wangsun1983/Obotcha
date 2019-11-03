#include <stdio.h>
#include <stdlib.h>

#include "ExecutorService.hpp"
#include "Thread.hpp"
#include "ThreadPoolExecutor.hpp"
#include "FutureTask.hpp"
#include "Future.hpp"
#include "System.hpp"
#include "Error.hpp"
#include "ExecutorDestructorException.hpp"
#include "PriorityPoolExecutor.hpp"

#define DEFAULT_THREAD_NUM 4

namespace obotcha {

//------------------PriorityTask-------------------
_PriorityTask::_PriorityTask(int l,FutureTask t) {
    priority = l;
    task = t;
}

//-------------------PriorityPoolHandler-------------------
_PriorityPoolHandler::_PriorityPoolHandler(ArrayList<PriorityTask> pool,Mutex m,Condition c,sp<_PriorityPoolExecutor> exe):mPool(pool),
                                                                         state(idleState),
                                                                         mStop(false),
                                                                         isWaitTerminate(false),
                                                                         mExecutor(exe){
    mStateMutex = createMutex("ThreadPoolExeHandlerMutex");
    mFutureMutex = m;
    mFutureCond = c;

    mWaitCond = createCondition();
    Runnable r;
    r.set_pointer(this);
    mThread = createThread(r);

    mExecutorMutex = createMutex("ThreadPoolExecutorMutex");

    state = idleState;
    mThread->start();
}

_PriorityPoolHandler::~_PriorityPoolHandler() {
    
}

void _PriorityPoolHandler::stop() {
    mStop = true;
    mThread->quit();
}

bool _PriorityPoolHandler::shutdownTask(FutureTask task) {
    if(mCurrentTask != nullptr && mCurrentTask == task) {
        AutoMutex l(mStateMutex);
        if(state == terminateState) {
            return false;
        }

        stop();
        return true;
    }

    return false;
}

void _PriorityPoolHandler::onInterrupt() {
    {
        AutoMutex l(mStateMutex);
        state = terminateState;
        if(isWaitTerminate) {
            mWaitCond->notify();
            isWaitTerminate = false;
        }
    }

    if(mCurrentTask != nullptr) {
        Runnable r = mCurrentTask->getRunnable();
        if(r != nullptr) {
            r->onInterrupt();
        }
        mCurrentTask = nullptr;
        r = nullptr;
    }

    PriorityPoolHandler h;
    h.set_pointer(this);
    mExecutor->onCompleteNotify(h);

    mExecutor.remove_pointer();
    
    mThread = nullptr;
}

void _PriorityPoolHandler::run() {
    while(!mStop) {
        mCurrentTask = nullptr;
        PriorityTask t = nullptr;
        {
            AutoMutex ll(mFutureMutex);
            if(mPool->size() == 0) {
                mFutureCond->wait(mFutureMutex);
                continue;
            }
            t = mPool->remove(0);
        }

        if(t == nullptr) {
            break;
        }

        mCurrentTask = t->task;
        if(mCurrentTask->getStatus() == FUTURE_CANCEL) {
            continue;
        }
        
        {
            AutoMutex l(mStateMutex);
            state = busyState;
            if(mCurrentTask->getType() == FUTURE_TASK_SUBMIT) {
                mCurrentTask->onRunning();
            }
        }
        Runnable runnable = mCurrentTask->getRunnable();
        if(runnable != nullptr) {
            runnable->run();    
        }

        {
            AutoMutex l(mStateMutex);
            state = idleState;

            if(mCurrentTask->getType() == FUTURE_TASK_SUBMIT) {
                mCurrentTask->onComplete();
            }
        }
    }

    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, nullptr);
    {
        AutoMutex l(mStateMutex);
        state = terminateState;

        if(isWaitTerminate) {
            mWaitCond->notify();
            isWaitTerminate = false;
        }
    }

    PriorityPoolHandler h;
    h.set_pointer(this);

    mExecutor->onCompleteNotify(h);
    
    mThread = nullptr;
}

//----------------PriorityPoolExecutor----------------
_PriorityPoolExecutor::_PriorityPoolExecutor(int threadnum) {
    init(threadnum);
}

_PriorityPoolExecutor::_PriorityPoolExecutor() {
    init(DEFAULT_THREAD_NUM);
}

void _PriorityPoolExecutor::init(int threadnum) {
    mProtectMutex = createMutex("PriorityPoolExecutor");
    mHandlersMutex = createMutex("PriorityPoolHandlers");
    mFutureTaskMutex = createMutex("PriorityThreadPoolFuture");
    mFutureCond = createCondition();

    mWaitMutex = createMutex("WaitMutex");
    mWaitCond = createCondition();

    mPool = createArrayList<PriorityTask>();
    
    mHandlers = createArrayList<PriorityPoolHandler>();

    mThreadNum = threadnum;
    
    PriorityPoolExecutor executor;
    executor.set_pointer(this);

    for(int i = 0; i < threadnum;i++) {
        PriorityPoolHandler h = createPriorityPoolHandler(mPool,mFutureTaskMutex,mFutureCond,executor);
        mHandlers->add(h);
    }

    mIsTerminated = false;

    mIsShutDown = false;
}

int _PriorityPoolExecutor::execute(Runnable runnable) {
    if(runnable == nullptr) {
        return -InvalidParam;
    }

    if(submit(runnable) != nullptr) {
        return 0;
    }

    return -InvalidStatus;
}

int _PriorityPoolExecutor::shutdown() {

    printf("shutdown trace1\n");
    if(mIsShutDown ||mIsTerminated) {
        return -AlreadyDestroy;
    }

    {
        AutoMutex l(mProtectMutex);

        if(mIsShutDown ||mIsTerminated) {
            return -AlreadyDestroy;
        }

        mIsShutDown = true;
    }

    printf("shutdown trace1_1\n");
    {
        AutoMutex ll2(mProtectMutex);
        if(!mIsTerminated) {
            printf("shutdown trace4,this is %lx,count is %d \n",this,this->getStrongCount());
            startWaitTerminate();
            printf("shutdown trace5,this is %lx,count is %d,count addr is %lx \n",this,this->getStrongCount(),this);
        }
    }
    
    {
        AutoMutex ll1(mHandlersMutex);
        ListIterator<PriorityPoolHandler> iterator = mHandlers->getIterator();
        while(iterator->hasValue()) {
            PriorityPoolHandler h = iterator->getValue();
            h->stop();
            iterator->next();
        }
    }

    printf("shutdown trace2\n");
    {
        AutoMutex ll2(mFutureTaskMutex);
        ListIterator<PriorityTask> iterator = mPool->getIterator();
        while(iterator->hasValue()) {
            PriorityTask t = iterator->getValue();
            if(t != nullptr) {
                t->task->cancel();
            }
            iterator->next();
        }

        mPool->clear();
    }

    printf("shutdown trace3\n");    
    
    return 0;
}

Future _PriorityPoolExecutor::submit(Runnable task) {
    return submit(TaskPriorityMedium,task);
}

Future _PriorityPoolExecutor::submit(int level,Runnable task) {
    if(mIsShutDown || mIsTerminated) {
        return nullptr;
    }
    
    AutoMutex l(mProtectMutex);
    
    if(mIsTerminated || mIsTerminated) {
        return nullptr;
    }

    AutoMutex ll(mFutureTaskMutex);
    int start = 0;
    int end = mPool->size() - 1;
    int index = 0;
    while(start <= end) {
        index = (start+end)/2;
        PriorityTask m = mPool->get(index);
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
    mPool->insert(index,createPriorityTask(level,futureTask));
    mFutureCond->notify();

    return createFuture(futureTask);
}

bool _PriorityPoolExecutor::isShutdown() {
    return mIsShutDown;
}

bool _PriorityPoolExecutor::isTerminated() {
    return mIsTerminated;
}

int _PriorityPoolExecutor::awaitTermination(long millseconds) {
    if(!mIsShutDown) {
        return -InvalidStatus;
    }

    if(mIsTerminated) {
        return 0;
    }

    AutoMutex ll(mWaitMutex);

    if(mIsTerminated) {
        return 0;
    }

    printf("satart awaitTermination trace1\n");
    if(mWaitCond->wait(mWaitMutex,millseconds) == NotifyByThread) {
        return 0;
    }
    printf("satart awaitTermination trace2\n");

    return  -1;
}

void _PriorityPoolExecutor::onCompleteNotify(PriorityPoolHandler h) {
    printf("_ThreadPoolExecutor onCompleteNotify!!!! \n");
    {
        AutoMutex ll(mHandlersMutex);
        ListIterator<PriorityPoolHandler>iterator = mHandlers->getIterator();
        while(iterator->hasValue()) {
            PriorityPoolHandler t = iterator->getValue();
            if(t == h) {
                iterator->remove();
                break;
            }
            iterator->next();
        }
    }

    if(mIsShutDown) {
        if(mHandlers->size() == 0) {
            {
                AutoMutex ll2(mWaitMutex);
                mIsTerminated = true;
                mWaitCond->notifyAll();
            }
            finishWaitTerminate();
        }
    }
}

int _PriorityPoolExecutor::getThreadsNum() {
    AutoMutex ll(mProtectMutex);
    return mHandlers->size();
}

_PriorityPoolExecutor::~_PriorityPoolExecutor() {
    
    printf("~_ThreadPoolExecutor trace4 \n");
    if(!mIsShutDown) {
        throw createExecutorDestructorException("ThreadPoolExecutor destruct error");
    }
    printf("~_ThreadPoolExecutor trace5 \n");
}

void _PriorityPoolExecutor::onCancel(FutureTask t) {
    printf("ThreadPoolExecutor onCancel start \n");
    if(mIsShutDown ||mIsTerminated) {
        return;
    }

    AutoMutex l(mProtectMutex);

    if(mIsShutDown ||mIsTerminated) {
        return;
    }
    
    {
        AutoMutex ll(mFutureTaskMutex);
        ListIterator<PriorityTask> iterator = mPool->getIterator();
        while(iterator->hasValue()) {
            PriorityTask p = iterator->getValue();
            if(p != nullptr && p->task == t) {
                iterator->remove();
                goto end;
            }
        }
    }

    printf("ThreadPoolExecutor onCancel trace1 \n");
    {
        AutoMutex ll2(mHandlersMutex);
        ListIterator<PriorityPoolHandler> iterator = mHandlers->getIterator();
        while(iterator->hasValue()) {
            PriorityPoolHandler h = iterator->getValue();
            if(h->shutdownTask(t)) {
                iterator->remove();
                continue;
            }

            iterator->next();
        }
    }

end:
    //we should insert a new
    if(!mIsShutDown) {
        PriorityPoolExecutor executor;
        executor.set_pointer(this);

        PriorityPoolHandler h = createPriorityPoolHandler(mPool,mFutureTaskMutex,mFutureCond,executor);
        mHandlers->add(h);
    }
}

}
