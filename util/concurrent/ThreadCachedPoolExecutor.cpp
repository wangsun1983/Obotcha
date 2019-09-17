#include <vector>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "ConcurrentQueue.hpp"
#include "Thread.hpp"
#include "AutoMutex.hpp"
#include "Condition.hpp"
#include "Thread.hpp"
#include "Future.hpp"
#include "ExecutorService.hpp"
#include "FutureTask.hpp"
#include "Future.hpp"
#include "ThreadCachedPoolExecutor.hpp"
#include "Integer.hpp"
#include "System.hpp"
#include "Error.hpp"

namespace obotcha {

#define DEFAULT_CACHED_THREAD_WAIT_TIME 60*1000
#define DEFAULT_CACHED_THREAD_NUMS 32    

_ThreadCachedPoolExecutor *tt;

_ThreadCachedPoolExecutorHandler::_ThreadCachedPoolExecutorHandler(BlockingQueue<FutureTask> pool,
                                                                   long timeout,
                                                                   _ThreadCachedPoolExecutor *h)
                                                                         :mPool(pool),
                                                                         state(idleState),
                                                                         mStop(false),
                                                                         isWaitIdle(false){
    mStateMutex = createMutex("ThreadCachedPoolExeHandlerMutex");

    mWaitCond = createCondition();

    Runnable r;

    r.set_pointer(this);

    mThread = createThread(r);
    
    mThreadTimeout = timeout;

    mThread->start();
    
    mPoolExecutor.set_pointer(h);
}

void _ThreadCachedPoolExecutorHandler::stop() {
    mStop = true;
    mThread->quit();
}

void _ThreadCachedPoolExecutorHandler::run() {
    while(!mStop) {
        mCurrentTask = nullptr;

        mPoolExecutor->increaseIdleThreadNum();
        mCurrentTask = mPool->deQueueFirst(mThreadTimeout);
        mPoolExecutor->decreaseIdleThreadNum();
        if(mCurrentTask == nullptr) {
            if(!mPoolExecutor->isOverMinSize() && !mStop){
                continue;
            }

            mStop = true;
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
    
    ThreadCachedPoolExecutorHandler t;
    t.set_pointer(this);
    mPoolExecutor->removeHandler(t);
    mPoolExecutor.remove_pointer();
}

void _ThreadCachedPoolExecutorHandler::onInterrupt() {
    
    if(mCurrentTask != nullptr) {
        Runnable r = mCurrentTask->getRunnable();
        if(r != nullptr) {
            r->onInterrupt();
        }
    }
    ThreadCachedPoolExecutorHandler t;
    t.set_pointer(this);
    mPoolExecutor->removeHandler(t);
    mPoolExecutor.remove_pointer();
   
    AutoMutex l(mStateMutex);
    state = terminateState;
    if(isWaitTerminate) {
        mWaitCond->notify();
        isWaitTerminate = false;
    }
}

void _ThreadCachedPoolExecutorHandler::waitForTerminate() {
    AutoMutex l(mStateMutex);
    isWaitTerminate = true;
    if(state == busyState) {
        mWaitCond->wait(mStateMutex);
    }
}

void _ThreadCachedPoolExecutorHandler::waitForTerminate(long interval) {
    AutoMutex l(mStateMutex);
    isWaitTerminate = true;
    if(state == busyState) {
        mWaitCond->wait(mStateMutex,interval);
    }
}

bool _ThreadCachedPoolExecutorHandler::isTerminated() {
    return state == terminateState;
}

_ThreadCachedPoolExecutor::_ThreadCachedPoolExecutor(int queuesize,int minthreadnum,int maxthreadnum,long timeout) {
    init(queuesize,minthreadnum,maxthreadnum,timeout);
}

_ThreadCachedPoolExecutor::_ThreadCachedPoolExecutor(int maxthreadnum,long timeout) {
    init(-1,0,maxthreadnum,timeout);
}

_ThreadCachedPoolExecutor::_ThreadCachedPoolExecutor() {
    init(-1,0,DEFAULT_CACHED_THREAD_NUMS,DEFAULT_CACHED_THREAD_WAIT_TIME);
}

int _ThreadCachedPoolExecutor::shutdown(){
    if(mIsShutDown ||mIsTerminated) {
        return -AlreadyDestroy;
    }
    //printf("cachethread shutdown start \n");
    AutoMutex l(mProtectMutex);

    if(mIsShutDown ||mIsTerminated) {
        return -AlreadyDestroy;
    }

    mIsShutDown = true;
    int size = mHandlers->size();
    for(int i = 0;i < size;i++) {
        mHandlers->get(i)->stop();
    }
    //printf("cachethread shutdown trace1 \n");
    for(;;) {
        FutureTask task = mPool->deQueueLastNoBlock();
        if(task != nullptr) {
            task->cancel();
        } else {
            break;
        }
    }
    //printf("cachethread shutdown trace2 \n");
    return 0;
}

int _ThreadCachedPoolExecutor::execute(Runnable r) {
    
    if(submit(r) == nullptr) {
        return -InvalidStatus;
    }

    return 0;
}

bool _ThreadCachedPoolExecutor::isShutdown() {
    return mIsShutDown;
}

bool _ThreadCachedPoolExecutor::isTerminated() {
    return false;
}

int _ThreadCachedPoolExecutor::awaitTermination() {
    awaitTermination(0);
}

int _ThreadCachedPoolExecutor::awaitTermination(long millseconds) {
    if(!mIsShutDown) {
        return -InvalidStatus;
    }

    if(mIsTerminated) {
        return 0;
    }

    if(millseconds == 0) {
        for(;;) {
            ThreadCachedPoolExecutorHandler handler = mHandlers->deQueueLast();
            //decreaseIdleThreadNum();
            if(handler != nullptr) {
                handler->waitForTerminate();
            } else {
                break;
            }
        }
        mIsTerminated = true;
        return 0;
    } else {
        for(;;) {
            long current = st(System)::currentTimeMillis();
            if(millseconds > 0) {
                ThreadCachedPoolExecutorHandler handler = mHandlers->deQueueLast();
                //decreaseIdleThreadNum();
                if(handler != nullptr) {
                    handler->waitForTerminate(millseconds);
                } else {
                    break;
                }
            } else {
                break;
            }
            millseconds -= (st(System)::currentTimeMillis() - current);
        }

        if(millseconds <= 0) {
            return -WaitTimeout;
        }
    }
    
    mIsTerminated = true;
    return 0;
}

Future _ThreadCachedPoolExecutor::submit(Runnable r) {
    if(mIsShutDown ||mIsTerminated) {
        return nullptr;
    }

    AutoMutex l(mProtectMutex);

    if(mIsShutDown ||mIsTerminated) {
        return nullptr;
    }
    ////printf("mHandler size is %d \n",mHandlers->size());
    if(mIdleThreadNum->get() == 0 && mHandlers->size() < maxThreadNum) {
        ThreadCachedPoolExecutorHandler t = createThreadCachedPoolExecutorHandler(mPool,mThreadTimeout,this);
        mHandlers->enQueueLast(t);
        //increaseIdleThreadNum();
    }

    FutureTask task = createFutureTask(FUTURE_TASK_SUBMIT,r);
    Future future = createFuture(task);
    mPool->enQueueLast(task); 

    return future;   
}

void _ThreadCachedPoolExecutor::init(int queuesize,int minthreadnum,int maxthreadnum,long timeout) {
    mIdleThreadNum = createAtomicInteger(0);
    mProtectMutex = createMutex("ThreadCachedMutex");
    mQueueSize = queuesize;

    if(mQueueSize != -1) {
        mPool = createBlockingQueue<FutureTask>(mQueueSize);    
    } else {
        mPool = createBlockingQueue<FutureTask>();
    }
    
    maxThreadNum = maxthreadnum;
    minThreadNum = minthreadnum;
    mThreadTimeout = timeout;

    mHandlers = createConcurrentQueue<ThreadCachedPoolExecutorHandler>();

    for(int i = 0;i < minThreadNum;i++) {
        ThreadCachedPoolExecutorHandler handler = createThreadCachedPoolExecutorHandler(mPool,mThreadTimeout,this);
        mHandlers->enQueueLast(handler);
        increaseIdleThreadNum();
    }

    mIsTerminated = false;

    mIsShutDown = false;
}

bool _ThreadCachedPoolExecutor::isOverMinSize() {
    return mHandlers->size() > minThreadNum;
}

void _ThreadCachedPoolExecutor::removeHandler(ThreadCachedPoolExecutorHandler h) {
    mHandlers->remove(h);
}

int _ThreadCachedPoolExecutor::getThreadsNum() {
    return mHandlers->size();
}

void _ThreadCachedPoolExecutor::increaseIdleThreadNum() {
    mIdleThreadNum->incrementAndGet();
}

void _ThreadCachedPoolExecutor::decreaseIdleThreadNum() {
    mIdleThreadNum->decrementAndGet();
}

_ThreadCachedPoolExecutor::~_ThreadCachedPoolExecutor() {
    shutdown();
}

}
