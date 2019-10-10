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

_ThreadCachedPoolExecutorHandler::_ThreadCachedPoolExecutorHandler(BlockingQueue<FutureTask> pool,
                                                                   long timeout,
                                                                   _ThreadCachedPoolExecutor *h,
                                                                   Mutex m)
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

    mHandlerMutex = m;

    mExecutor = h;

    isFirstBoot = true;

    isWaitTerminate = false;

    mThread = createThread(r);
    
    mThreadTimeout = timeout;
    mThread->start();
    
    {
        AutoMutex ll(waitStartMutex);
        if(isFirstBoot) {
            waitStartCond->wait(waitStartMutex);
        }
    }
}

_ThreadCachedPoolExecutorHandler::~_ThreadCachedPoolExecutorHandler() {
    mCurrentTask = nullptr;
}

void _ThreadCachedPoolExecutorHandler::stop() {
    mStop = true;
    mThread->quit();
}

void _ThreadCachedPoolExecutorHandler::run() {
    while(!mStop) {
        mCurrentTask = nullptr;
        {
            AutoMutex ll(mExecutorMutex);
            if(mExecutor != nullptr) {
                mExecutor->increaseIdleThreadNum();
                
                {
                    AutoMutex ll(waitStartMutex);
                    if(isFirstBoot) {
                        waitStartCond->notify();
                        isFirstBoot = false;
                    }
                }
            }
        }
        long start = st(System)::currentTimeMillis();

        mCurrentTask = mPool->deQueueFirst(mThreadTimeout);
        {
            AutoMutex ll(mExecutorMutex);
            if(mExecutor != nullptr) {
                mExecutor->decreaseIdleThreadNum();
            }
        }
        
        if(mCurrentTask == nullptr) {
            {
                AutoMutex ll(mExecutorMutex);
                if(mExecutor != nullptr) {
                    if(!mExecutor->isOverMinSize() && !mStop){
                        continue;
                    }
                }
            }
            mStop = true;
            goto end;
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

end:
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, nullptr);
    {
        AutoMutex l(mStateMutex);
        state = terminateState;
        if(isWaitTerminate) {
            mWaitCond->notify();
            isWaitTerminate = false;
        }
    }

    {
        AutoMutex ll1(mHandlerMutex);
        AutoMutex ll2(mExecutorMutex);
        if(mExecutor != nullptr) {
            ThreadCachedPoolExecutorHandler t;
            t.set_pointer(this);
            mExecutor->removeHandler(t);
        }
    }

    mThread = nullptr;
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

        mCurrentTask = nullptr;
    }

    {
        AutoMutex ll1(mHandlerMutex);
        AutoMutex ll(mExecutorMutex);
        if(mExecutor != nullptr) {
            ThreadCachedPoolExecutorHandler t;
            t.set_pointer(this);
            mExecutor->removeHandler(t);
        }
    }
   
    AutoMutex l(mStateMutex);
    state = terminateState;
    if(isWaitTerminate) {
        mWaitCond->notify();
        isWaitTerminate = false;
    }

    mThread = nullptr;
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
    
    int i = 0;
    for(;;) {
        FutureTask task = mPool->deQueueLastNoBlock();
        if(task != nullptr) {
            i++;
            task->cancel();
        } else {
            break;
        }
    }
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
    
    if(mIdleThreadNum->get() == 0 && mHandlers->size() < maxThreadNum) {
        ThreadCachedPoolExecutorHandler t = createThreadCachedPoolExecutorHandler(mPool,
                                                                                  mThreadTimeout,
                                                                                  this,
                                                                                  mHandlerMutex);
        AutoMutex ll(mHandlerMutex);
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
        ThreadCachedPoolExecutorHandler handler = createThreadCachedPoolExecutorHandler(mPool,
                                                                                        mThreadTimeout,
                                                                                        this,
                                                                                        mHandlerMutex);
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
    {
        AutoMutex ll(mHandlerMutex);
        int size = mHandlers->size();
        for(int i = 0;i < size;i++) {
            mHandlers->get(i)->onExecutorDestroy();
        }
    }

    shutdown();
}

}
