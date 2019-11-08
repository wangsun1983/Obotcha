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

static int id = 0;

#define DEFAULT_THREAD_NUM 4

namespace obotcha {

_ThreadPoolExecutorHandler::_ThreadPoolExecutorHandler(BlockingQueue<FutureTask> pool,sp<_ThreadPoolExecutor> exe):mPool(pool),
                                                                         state(idleState),
                                                                         mStop(false),
                                                                         isWaitTerminate(false),
                                                                         mExecutor(exe){
    mStateMutex = createMutex("ThreadPoolExeHandlerMutex");
    mWaitCond = createCondition();
    Runnable r;
    r.set_pointer(this);
    mThread = createThread(r);

    mExecutorMutex = createMutex("ThreadPoolExecutorMutex");

    state = idleState;
    mThread->start();
}

_ThreadPoolExecutorHandler::~_ThreadPoolExecutorHandler() {
    
}

void _ThreadPoolExecutorHandler::stop() {
    mStop = true;
    mThread->quit();
}

bool _ThreadPoolExecutorHandler::shutdownTask(FutureTask task) {
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

void _ThreadPoolExecutorHandler::onInterrupt() {
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

    ThreadPoolExecutorHandler h;
    h.set_pointer(this);
    mExecutor->onCompleteNotify(h);
    mExecutor.remove_pointer();
    mThread = nullptr;
}

void _ThreadPoolExecutorHandler::run() {
    while(!mStop) {
        mCurrentTask = nullptr;
        mCurrentTask = mPool->deQueueFirst();
        if(mCurrentTask == nullptr) {
            break;
        }
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

    ThreadPoolExecutorHandler h;
    h.set_pointer(this);
    mExecutor->onCompleteNotify(h);
    mExecutor.remove_pointer();
    mThread = nullptr;
}

void _ThreadPoolExecutorHandler::waitForTerminate() {
    AutoMutex l(mStateMutex);
    isWaitTerminate = true;
    if(state == busyState) {
        mWaitCond->wait(mStateMutex);
    }
}

void _ThreadPoolExecutorHandler::waitForTerminate(long interval) {
    AutoMutex l(mStateMutex);
    isWaitTerminate = true;
    if(state == busyState) {
        mWaitCond->wait(mStateMutex,interval);
    }
}

bool _ThreadPoolExecutorHandler::isTerminated() {
    return state == terminateState;
}

_ThreadPoolExecutor::_ThreadPoolExecutor(int queuesize,int threadnum) {
    init(queuesize,threadnum);
}

_ThreadPoolExecutor::_ThreadPoolExecutor() {
    init(-1,DEFAULT_THREAD_NUM);
}

void _ThreadPoolExecutor::init(int queuesize,int threadnum) {
    mProtectMutex = createMutex("ThreadPoolExecutor");
    mHandlersMutex = createMutex("ThreadPoolHandlers");
    mWaitMutex = createMutex("ThreadPoolWaitMutex");
    mWaitCondition = createCondition();

    if(queuesize != -1) {
        mPool = createBlockingQueue<FutureTask>(queuesize);    
    } else {
        mPool = createBlockingQueue<FutureTask>();
    }
    
    mHandlers = createArrayList<ThreadPoolExecutorHandler>();

    mThreadNum = threadnum;

    for(int i = 0; i < threadnum;i++) {
        ThreadPoolExecutorHandler h = createThreadPoolExecutorHandler(mPool,this);
        mHandlers->add(h);
    }

    mIsTerminated = false;

    mIsShutDown = false;
}

int _ThreadPoolExecutor::execute(Runnable runnable) {
    if(runnable == nullptr) {
        return -InvalidParam;
    }

    if(mIsShutDown ||mIsTerminated) {
        return -AlreadyDestroy;
    }

    AutoMutex l(mProtectMutex);

    if(mIsShutDown ||mIsTerminated) {
        return -AlreadyDestroy;
    }
    
    FutureTask task = createFutureTask(FUTURE_TASK_NORMAL,runnable);

    mPool->enQueueLast(task);
}

int _ThreadPoolExecutor::shutdown() {
    //printf"shutdown trace1\n");
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

    AutoMutex ll1(mHandlersMutex);
    ListIterator<ThreadPoolExecutorHandler> iterator = mHandlers->getIterator();
    while(iterator->hasValue()) {
        ThreadPoolExecutorHandler h = iterator->getValue();
        h->stop();
        iterator->next();
    }

    //printf"shutdown trace2\n");
    for(;;) {
        FutureTask task = mPool->deQueueLastNoBlock();
        if(task != nullptr) {
            task->cancel();
        } else {
            break;
        }
    }

    mPool->clear();

    //printf"shutdown trace3\n");    
    AutoMutex ll2(mProtectMutex);
    if(!mIsTerminated) {
        //printf"shutdown trace4,this is %lx,count is %d \n",this,this->getStrongCount());
#if 0        
        startWaitTerminate();
#endif 0        
        //printf"shutdown trace5,this is %lx,count is %d,count addr is %lx \n",this,this->getStrongCount(),this);
    }
    return 0;
}

Future _ThreadPoolExecutor::submit(Runnable r) {
    if(r == nullptr) {
        return nullptr;
    }

    if(mIsShutDown||mIsTerminated) {
        return nullptr;
    }

    AutoMutex l(mProtectMutex);

    if(mIsShutDown ||mIsTerminated) {
        return nullptr;
    }
    
    FutureTaskStatusListener listener;
    listener.set_pointer(this);

    FutureTask task = createFutureTask(FUTURE_TASK_SUBMIT,r,listener);
    mPool->enQueueLast(task);

    return createFuture(task);
}

bool _ThreadPoolExecutor::isShutdown() {
    return mIsShutDown;
}

bool _ThreadPoolExecutor::isTerminated() {
    return mIsTerminated;
}

int _ThreadPoolExecutor::awaitTermination(long millseconds) {
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

    if(NotifyByTimeout == mWaitCondition->wait(mWaitMutex,millseconds)) {
        return -WaitTimeout;
    }

    return 0;
}

void _ThreadPoolExecutor::onCompleteNotify(ThreadPoolExecutorHandler h) {
    //printf"_ThreadPoolExecutor onCompleteNotify!!!! \n");
    AutoMutex ll(mHandlersMutex);
    ListIterator<ThreadPoolExecutorHandler>iterator = mHandlers->getIterator();
    while(iterator->hasValue()) {
        ThreadPoolExecutorHandler t = iterator->getValue();
        if(t == h) {
            iterator->remove();
            break;
        }
        iterator->next();
    }

    if(mIsShutDown) {
        if(mHandlers->size() == 0) {
            
#if 0            
            finishWaitTerminate();
#endif           
            AutoMutex ll(mWaitMutex);
            mIsTerminated = true;
            mWaitCondition->notifyAll();
        }
    }
}

int _ThreadPoolExecutor::getThreadsNum() {
    AutoMutex ll(mProtectMutex);
    return mHandlers->size();
}

_ThreadPoolExecutor::~_ThreadPoolExecutor() {
    
    //printf"~_ThreadPoolExecutor trace4 \n");
    if(!mIsShutDown) {
        throw createExecutorDestructorException("ThreadPoolExecutor destruct error");
    }
    //printf"~_ThreadPoolExecutor trace5 \n");
}

void _ThreadPoolExecutor::onCancel(FutureTask t) {
    //printf"ThreadPoolExecutor onCancel start \n");
    if(mIsShutDown ||mIsTerminated) {
        return;
    }

    AutoMutex l(mProtectMutex);

    if(mIsShutDown ||mIsTerminated) {
        return;
    }
    
    //printf"before remove mPool size is %d \n",mPool->size());
    if(mPool->remove(t)) {
        //printf"after remove mPool size is %d \n",mPool->size());
    } else {
        //printf"ThreadPoolExecutor onCancel trace1 \n");
        ThreadPoolExecutorHandler h = nullptr;
        int size = mHandlers->size();
        for(int i = 0;i < size;i++) {
            h = mHandlers->get(i);
            //printf"ThreadPoolExecutor onCancel trace2 \n");
            if(h != nullptr) {
                if(h->shutdownTask(t)) {
                    //printf"ThreadPoolExecutor onCancel trace3,before size is %d \n",mHandlers->size());
                    mHandlers->remove(h);
                    //printf"ThreadPoolExecutor onCancel trace3,after size is %d \n",mHandlers->size());
                    break;
                }
            }
        }
    }

    

    //we should insert a new
    if(!mIsShutDown) {
        ThreadPoolExecutorHandler h = createThreadPoolExecutorHandler(mPool,this);
        mHandlers->add(h);
    }
}

}
