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

    mThread = createThread(this);
    
    mThreadTimeout = timeout;

    mThread->start();
    
    mPoolExecutor.set_pointer(h);
    tt = h;
    printf("mPoolExecutor count is %d \n",mPoolExecutor->getStrongCount());
}

void _ThreadCachedPoolExecutorHandler::stop() {
    mStop = true;
}

void _ThreadCachedPoolExecutorHandler::forceStop() {
    mStop = true;
    mThread->exit();
}

void _ThreadCachedPoolExecutorHandler::run() {
    while(!mStop) {
        printf("wangsl,executorhandler run1 \n");
        FutureTask task = mPool->deQueueFirst(mThreadTimeout);
        //no task,so we should remove this thread,and exit;
        mPoolExecutor->decreaseIdleThreadNum();
        if(task == nullptr) {
            printf("wangsl,ececutorhandler run1_1 \n");
            if(!mPoolExecutor->isOverMinSize() && !mStop){
                continue;
            }

            mStop = true;
            break;
        }


        printf("wangsl,ececutorhandler run2 \n");
        {
            AutoMutex l(mStateMutex);
            state = busyState;
            if(task->getType() == FUTURE_TASK_SUBMIT) {
                task->onRunning();
            }
        }
        
        Runnable runnable = task->getRunnable();
        if(runnable != nullptr) {
            runnable->run();    
        }
     
        {
            AutoMutex l(mStateMutex);
            state = idleState;

            if(task->getType() == FUTURE_TASK_SUBMIT) {
                task->onComplete();
            }
        }
        printf("wangsl,ececutorhandler run3 \n");
        mPoolExecutor->increaseIdleThreadNum();
        //decreaseIdleThreadNum();
    }
    printf("wangsl,ececutorhandler run4 \n");
    if(mPoolExecutor != nullptr) {
        ThreadCachedPoolExecutorHandler t;
        t.set_pointer(this);
        printf("wangsl,ececutorhandler run4_1 \n");
        mPoolExecutor->removeHandler(t);
        mPoolExecutor.remove_pointer();
        printf("wangsl,ececutorhandler run4_2 \n");
        mPoolExecutor = nullptr;
        printf("wangsl,ececutorhandler run4_3 \n");
    }
    printf("wangsl,ececutorhandler run5 \n");

    {
        AutoMutex l(mStateMutex);
        state = terminateState;
        if(isWaitTerminate) {
            mWaitCond->notify();
            isWaitTerminate = false;
        }
    }
    printf("wangsl,ececutorhandler run6 \n");
}

void _ThreadCachedPoolExecutorHandler::onInterrupt() {
    printf("_ThreadCachedPoolExecutorHandler onInterrupt 1 \n");
    if(mPoolExecutor != nullptr) {
        printf("_ThreadCachedPoolExecutorHandler onInterrupt 2,count is %d \n",mPoolExecutor->getStrongCount());
        ThreadCachedPoolExecutorHandler t;
        t.set_pointer(this);
        mPoolExecutor->removeHandler(t);
        mPoolExecutor.remove_pointer();
        printf("_ThreadCachedPoolExecutorHandler onInterrupt 2_1,count is %d \n",tt->getStrongCount());
        mPoolExecutor = nullptr;
        printf("_ThreadCachedPoolExecutorHandler onInterrupt 2_2,count is %d \n",tt->getStrongCount());
        mPoolExecutor->increaseIdleThreadNum();
    }
    printf("_ThreadCachedPoolExecutorHandler onInterrupt 3 \n");
    AutoMutex l(mStateMutex);
    state = terminateState;
    if(isWaitTerminate) {
        //printf("notify trace \n");
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
        printf("wait internal start is %d \n",interval);
        mWaitCond->wait(mStateMutex,interval);
        printf("wait internal end is %d \n",interval);
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
        return -ExecutorFailAlreadyDestroy;
    }

    mIsShutDown = true;
    int size = mHandlers->size();
    for(int i = 0;i < size;i++) {
        mHandlers->get(i)->stop();
    }

    int taskNum = mPool->size();
    for(;;) {
        FutureTask task = mPool->deQueueLastNoBlock();
        if(task != nullptr) {
            task->cancel();
        } else {
            break;
        }
    }

    mPool->clear();
    return 0;
}

int _ThreadCachedPoolExecutor::shutdownNow() {
    printf("shutdownNow 1 \n");
    if(mIsShutDown ||mIsTerminated) {
        return -ExecutorFailAlreadyDestroy;
    }
    printf("shutdownNow 2 \n");
    mIsShutDown = true;
    int size = mHandlers->size();
    for(int i = 0;i < size;i++) {
        mHandlers->get(i)->forceStop();
    }
    printf("shutdownNow 3 \n");
    //int taskNum = mPool->size();
    for(;;) {
        FutureTask task = mPool->deQueueLastNoBlock();
        if(task != nullptr) {
            task->cancel();
        } else {
            break;
        }
    }
    printf("shutdownNow 4 \n");
    //mPool->clear();

    mIsTerminated = true;

    return 0;
}

int _ThreadCachedPoolExecutor::execute(Runnable r) {
    if(mIsShutDown || mIsTerminated) {
        return -ExecutorFailAlreadyDestroy;
    }
 
    //FutureTask task = createFutureTask(FUTURE_TASK_NORMAL,runnable);

    //mPool->enQueueLast(task);
    submit(r);

    return 0;
}

bool _ThreadCachedPoolExecutor::isShutdown() {
    return mIsShutDown;
}

bool _ThreadCachedPoolExecutor::isTerminated() {
    return false;
}

int _ThreadCachedPoolExecutor::awaitTermination(long millseconds) {
    if(!mIsShutDown) {
        return -ExecutorFailIsRunning;
    }

    //int size = mHandlers->size();
    if(millseconds == 0) {
        for(;;) {
            ThreadCachedPoolExecutorHandler handler = mHandlers->deQueueLast();
            decreaseIdleThreadNum();
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
            if(millseconds >= 0) {
                ThreadCachedPoolExecutorHandler handler = mHandlers->deQueueLast();
                decreaseIdleThreadNum();
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
            return -ExecutorFailWaitTimeout;
        }
    }
    
    mIsTerminated = true;
    return 0;
}

Future _ThreadCachedPoolExecutor::submit(Runnable r) {
    printf("cachedthread submit 0 \n");
    AutoMutex l(mInputMutex);

    if(mIsShutDown ||mIsTerminated) {
        return nullptr;//ExecuteResult::failShutDown;
    }
    printf("cachedthread submit 1 \n");
    if(mIdleThreadNum->get() == 0 && mHandlers->size() < maxThreadNum) {
        printf("cachedthread submit 2 \n");
        ThreadCachedPoolExecutorHandler t = createThreadCachedPoolExecutorHandler(mPool,mThreadTimeout,this);
        mHandlers->enQueueLast(t);
        increaseIdleThreadNum();
    }

    printf("cachedthread submit 3 \n");
    FutureTask task = createFutureTask(FUTURE_TASK_SUBMIT,r);
    Future future = createFuture(task);
    mPool->enQueueLast(task); 
    printf("cachedthread submit 4 \n");
    return future;   
}

void _ThreadCachedPoolExecutor::init(int queuesize,int minthreadnum,int maxthreadnum,long timeout) {
    //printf("init queue size is %d ,min num is %d,max num is %d,timeout is %ld",queuesize,minthreadnum,maxthreadnum,timeout);
    mIdleThreadNum = createAtomicInteger(0);

    mInputMutex = createMutex("ThreadCachedMutex");

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
    printf("destroy _ThreadCachedPoolExecutor \n");
    shutdownNow();
}

}
