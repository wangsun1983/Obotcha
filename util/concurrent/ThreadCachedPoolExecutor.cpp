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
#include "InitializeException.hpp"

namespace obotcha {

#define DEFAULT_CACHED_THREAD_WAIT_TIME 60*1000
#define DEFAULT_CACHED_THREAD_NUMS 4    

DEBUG_REFERENCE_REALIZATION(ThreadCachedPoolExecutorHandler)

_ThreadCachedPoolExecutorHandler::_ThreadCachedPoolExecutorHandler(BlockingQueue<FutureTask> pool,
                                                                   long timeout,
                                                                   _ThreadCachedPoolExecutor *h)
                                                                         :mPool(pool),
                                                                         state(idleState),
                                                                         mStop(false),
                                                                         isWaitIdle(false){
    mStateMutex = createMutex("ThreadCachedPoolExeHandlerMutex");

    waitStartMutex = createMutex("CachedPoolStartMutex");

    waitStartCond = createCondition();
    
    mWaitCond = createCondition();

    Runnable r;

    r.set_pointer(this);

    mExecutorMutex = createMutex("CachedPoolExecutorMutex");

    mExecutor = h;

    mThread = createThread(r);
    
    mThreadTimeout = timeout;

    mThread->start();

    {
        AutoMutex ll(waitStartMutex);
    
        isFirstBoot = true;
    
        waitStartCond->wait(waitStartMutex);
    }
    
    incDebugReferenctCount();
    //printf("increase count is %d \n",getDebugReferenceCount());
}

_ThreadCachedPoolExecutorHandler::~_ThreadCachedPoolExecutorHandler() {
    //printf("~_ThreadCachedPoolExecutorHandler \n");
    decDebugReferenctCount();
    //printf("decrease count is %d \n",getDebugReferenceCount());
}

void _ThreadCachedPoolExecutorHandler::stop() {
    mStop = true;
    mThread->quit();
}

void _ThreadCachedPoolExecutorHandler::run() {
    while(!mStop) {
        mCurrentTask = nullptr;
        //printf("_ThreadCachedPoolExecutorHandler start \n");
        {
            AutoMutex ll(mExecutorMutex);
            if(mExecutor != nullptr) {
                //printf("thread increase \n");
                mExecutor->increaseIdleThreadNum();

                if(isFirstBoot) {
                    waitStartCond->notify();
                    isFirstBoot = false;
                }
            }
            
        }
        //printf("mThreadTimeout is %d \n",mThreadTimeout);
        long start = st(System)::currentTimeMillis();

        mCurrentTask = mPool->deQueueFirst(mThreadTimeout);
        {
            AutoMutex ll(mExecutorMutex);
            if(mExecutor != nullptr) {
                //printf("thread increase \n");
                mExecutor->decreaseIdleThreadNum();
            }
        }
        //printf("dequeue cost is %d \n",st(System)::currentTimeMillis() - start);
        
        if(mCurrentTask == nullptr) {
            //printf("timeout trace1 \n");
            {
                AutoMutex ll(mExecutorMutex);
                if(mExecutor != nullptr) {
                    //printf("timeout trace2 \n");
                    if(!mExecutor->isOverMinSize() && !mStop){
                        //printf("timeout trace3 \n");
                        continue;
                    }
                }
                
            }
            //printf("timeout trace4 \n");
            mStop = true;
            //printf("timeout trace4_1 \n");
            goto end;
        }

        //printf("timeout trace4_2 \n");
        if(mCurrentTask->getStatus() == FUTURE_CANCEL) {
            continue;
        }
        //printf("timeout trace4_3 \n");
        {
            AutoMutex l(mStateMutex);
            state = busyState;
            if(mCurrentTask->getType() == FUTURE_TASK_SUBMIT) {
                mCurrentTask->onRunning();
            }
        }
        //printf("timeout trace4_4 \n");
        Runnable runnable = mCurrentTask->getRunnable();
        if(runnable != nullptr) {
            runnable->run();    
        }
        //printf("timeout trace4_5 \n");
     
        {
            AutoMutex l(mStateMutex);
            state = idleState;

            if(mCurrentTask->getType() == FUTURE_TASK_SUBMIT) {
                mCurrentTask->onComplete();
            }
        }
        //printf("timeout trace4_6 \n");
    }

end:
    //printf("timeout trace5 \n");
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, nullptr);
    {
        AutoMutex l(mStateMutex);
        state = terminateState;
        if(isWaitTerminate) {
            mWaitCond->notify();
            isWaitTerminate = false;
        }
    }

    //printf("timeout trace6 \n");
    AutoMutex ll(mExecutorMutex);
    if(mExecutor != nullptr) {
        ThreadCachedPoolExecutorHandler t;
        t.set_pointer(this);
        mExecutor->removeHandler(t);
    }
}

void _ThreadCachedPoolExecutorHandler::onExecutorDestroy() {
    AutoMutex ll(mExecutorMutex);
    mExecutor = nullptr;
}

void _ThreadCachedPoolExecutorHandler::onInterrupt() {
    
    if(mCurrentTask != nullptr) {
        Runnable r = mCurrentTask->getRunnable();
        if(r != nullptr) {
            r->onInterrupt();
        }
    }

    AutoMutex ll(mExecutorMutex);
    if(mExecutor != nullptr) {
        ThreadCachedPoolExecutorHandler t;
        t.set_pointer(this);
        mExecutor->removeHandler(t);
    }
   
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

DEBUG_REFERENCE_REALIZATION(ThreadCachedPoolExecutor)

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
    ////printf("cachethread shutdown start \n");
    AutoMutex l(mProtectMutex);

    if(mIsShutDown ||mIsTerminated) {
        return -AlreadyDestroy;
    }

    mIsShutDown = true;

    {
        AutoMutex ll(mHandlerMutex);

        int size = mHandlers->size();
        for(int i = 0;i < size;i++) {
            ThreadCachedPoolExecutorHandler handler = mHandlers->get(i);
            handler->stop();
        }
    }
    ////printf("cachethread shutdown trace1 \n");
    for(;;) {
        FutureTask task = mPool->deQueueLastNoBlock();
        if(task != nullptr) {
            task->cancel();
        } else {
            break;
        }
    }
    ////printf("cachethread shutdown trace2 \n");
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
            
            ThreadCachedPoolExecutorHandler handler;
            {
                AutoMutex ll(mHandlerMutex);
                if(mHandlers->size() == 0) {
                    break;
                }

                handler = mHandlers->get(0);
            }
             
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
                ThreadCachedPoolExecutorHandler handler;
                {
                    AutoMutex ll(mHandlerMutex);
                    if(mHandlers->size() == 0) {
                        break;
                    }

                    handler = mHandlers->get(0);
                }

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
    
    //printf("mIdleThreadNum size is %d,size is %d,max is %d \n",mIdleThreadNum->get(),mHandlers->size(),maxThreadNum);
    if(mIdleThreadNum->get() == 0 && mHandlers->size() < maxThreadNum) {
        ThreadCachedPoolExecutorHandler t = createThreadCachedPoolExecutorHandler(mPool,mThreadTimeout,this);
        mHandlers->add(t);
        //increaseIdleThreadNum();
    }

    FutureTask task = createFutureTask(FUTURE_TASK_SUBMIT,r);
    Future future = createFuture(task);
    mPool->enQueueLast(task);
    //decreaseIdleThreadNum();

    return future;   
}

void _ThreadCachedPoolExecutor::init(int queuesize,int minthreadnum,int maxthreadnum,long timeout) {
    if(queuesize == 0 || minthreadnum > maxthreadnum) {
        throw createInitializeException(createString("ThreadCachedPool"));
    }

    incDebugReferenctCount();

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

    mHandlerMutex = createMutex("CachedPoolHandlersMutex");
    mHandlers = createArrayList<ThreadCachedPoolExecutorHandler>();

    for(int i = 0;i < minThreadNum;i++) {
        ThreadCachedPoolExecutorHandler handler = createThreadCachedPoolExecutorHandler(mPool,mThreadTimeout,this);
        mHandlers->add(handler);
        //increaseIdleThreadNum();
    }

    mIsTerminated = false;

    mIsShutDown = false;
}

bool _ThreadCachedPoolExecutor::isOverMinSize() {
    return mHandlers->size() > minThreadNum;
}

void _ThreadCachedPoolExecutor::removeHandler(ThreadCachedPoolExecutorHandler h) {
    AutoMutex ll(mHandlerMutex);
    ////printf("h1 count is %d \n",h->getStrongCount());
    mHandlers->remove(h);
    ////printf("h2 count is %d \n",h->getStrongCount());
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
    //TODO
    shutdown();
    decDebugReferenctCount();
}

}
