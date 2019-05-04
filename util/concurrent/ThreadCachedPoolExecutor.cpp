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

_ThreadCachedPoolExecutorHandler::_ThreadCachedPoolExecutorHandler(BlockingQueue<FutureTask> pool,
                                                                   long timeout,
                                                                   _ThreadCachedPoolExecutor *h)
                                                                         :mPool(pool),
                                                                         state(idleState),
                                                                         mStop(false),
                                                                         isWaitIdle(false){
    mStateMutex = createMutex();
    mWaitCond = createCondition();

    mThread = createThread(this);
    
    mThreadTimeout = timeout;

    mThread->start();

    mPoolExecutor.set_pointer(h);
}

void _ThreadCachedPoolExecutorHandler::stop() {
    mStop = true;
}

void _ThreadCachedPoolExecutorHandler::forceStop() {
    mThread->exit();
    mStop = true;
}

void _ThreadCachedPoolExecutorHandler::run() {
    while(!mStop) {
        printf("wangsl,executorhandler run1 \n");
        FutureTask task = mPool->deQueueFirst(mThreadTimeout);
        //no task,so we should remove this thread,and exit;
        if(task == nullptr) {
            if(!mPoolExecutor->isOverMinSize()){
                continue;
            }

            mThread->exit();
            mStop = true;

            ThreadCachedPoolExecutorHandler t;
            t.set_pointer(this);
            mPoolExecutor->removeHandler(t);
            mPoolExecutor.remove_pointer();
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
    }

    {
        AutoMutex l(mStateMutex);
        if(isWaitTerminate) {
            mWaitCond->notify();
            isWaitTerminate = false;
        }
    }
}

void _ThreadCachedPoolExecutorHandler::onInterrupt() {
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
    if(state != terminateState) {
        mWaitCond->wait(mStateMutex);
    }
}

void _ThreadCachedPoolExecutorHandler::waitForTerminate(long interval) {
    AutoMutex l(mStateMutex);
    isWaitTerminate = true;
    if(state != terminateState) {
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

void _ThreadCachedPoolExecutor::shutdown(){
    mIsShutDown = true;
    int size = mHandlers->size();
    for(int i = 0;i < size;i++) {
        mHandlers->get(i)->stop();
    }

    mPool->clear();
}

void _ThreadCachedPoolExecutor::shutdownNow() {
    mIsShutDown = true;
    int size = mHandlers->size();
    for(int i = 0;i < size;i++) {
        mHandlers->get(i)->forceStop();
    }

    mPool->clear();

    mIsTerminated = true;
}

void _ThreadCachedPoolExecutor::execute(Runnable r) {
    if(mIsShutDown) {
        return;//ExecuteResult::failShutDown;
    }
    
    //FutureTask task = createFutureTask(FUTURE_TASK_NORMAL,runnable);

    //mPool->enQueueLast(task);
    submit(r);
}

bool _ThreadCachedPoolExecutor::isShutdown() {
    return mIsShutDown;
}

bool _ThreadCachedPoolExecutor::isTerminated() {
    return false;
}

bool _ThreadCachedPoolExecutor::awaitTermination(long millseconds) {
    if(!mIsShutDown) {
        return false;
    }

    if(mIsTerminated) {
        return true;
    }

    int size = mHandlers->size();
    if(millseconds == 0) {
        for(int i = 0;i < size;i++) {
            mHandlers->get(i)->waitForTerminate();
        }
        mIsTerminated = true;
        return true;
    } else {
        for(int i = 0;i < size;i++) {
            long current = st(System)::currentTimeMillis();
            if(millseconds >= 0) {
                mHandlers->get(i)->waitForTerminate(millseconds);
            } else {
                break;
            }
            millseconds -= (st(System)::currentTimeMillis() - current);
        }
    }

    return false;
}

Future _ThreadCachedPoolExecutor::submit(Runnable r) {
    if(mIsShutDown) {
        return nullptr;//ExecuteResult::failShutDown;
    }
    //printf("cachedthread submit 1 \n");
    if((mPool->size()!= 0 && mHandlers->size() < maxThreadNum)
      ||(mHandlers->size() == 0)) {
        //printf("cachedthread submit 2 \n");
        ThreadCachedPoolExecutorHandler t = createThreadCachedPoolExecutorHandler(mPool,mThreadTimeout,this);
        mHandlers->enQueueLast(t);
    } 

    //printf("cachedthread submit 3 \n");
    FutureTask task = createFutureTask(FUTURE_TASK_SUBMIT,r);
    Future future = createFuture(task);
    mPool->enQueueLast(task); 
    //printf("cachedthread submit 4 \n");
    return future;   
}

void _ThreadCachedPoolExecutor::init(int queuesize,int minthreadnum,int maxthreadnum,long timeout) {
    //printf("init queue size is %d ,min num is %d,max num is %d,timeout is %ld",queuesize,minthreadnum,maxthreadnum,timeout);
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

}
