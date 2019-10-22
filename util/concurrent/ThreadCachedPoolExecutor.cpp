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
#include "Log.hpp"

namespace obotcha {

#define DEFAULT_CACHED_THREAD_WAIT_TIME 15*1000
#define DEFAULT_CACHED_MAX_THREAD_NUMS 4
#define DEFAULT_CACHED_QUEUE_NUMS 32    

_ThreadCachedPoolExecutorHandler::_ThreadCachedPoolExecutorHandler(BlockingQueue<FutureTask> pool,
                                                                   Mutex taskMutex,
                                                                   CacheThreadManager manager, 
                                                                   long timeout)
                                                                         :mPool(pool),
                                                                         state(idleState),
                                                                         mStop(false),
                                                                         mTaskMutex(taskMutex),
                                                                         mCacheManager(manager){
    mWaitCond = createCondition();

    mTaskWaitMutex = createMutex();

    mTaskCondition = createCondition();
    
    mThreadTimeout = timeout;
}

_ThreadCachedPoolExecutorHandler::~_ThreadCachedPoolExecutorHandler() {
    mCurrentTask = nullptr;
    mCacheManager.set_pointer(nullptr);
}

void _ThreadCachedPoolExecutorHandler::stop() {
    mStop = true;
    quit();
}

void _ThreadCachedPoolExecutorHandler::doTask(FutureTask task) {
    mCurrentTask = task;
    mTaskCondition->notify();
}

void _ThreadCachedPoolExecutorHandler::run() {
    ThreadCachedPoolExecutorHandler h;
    h.set_pointer(this);

    while(!mStop) {
        //long start = st(System)::currentTimeMillis();

        //printf("cached pool current time is %ld,mThreadTimeout is %ld\n",st(System)::currentTimeMillis(),mThreadTimeout);

        {
            AutoMutex ll(mTaskWaitMutex);
            if(mCurrentTask == nullptr) {
                //printf("start wait \n");
                mCacheManager->idleNotify(h);

                int result = mTaskCondition->wait(mTaskWaitMutex,mThreadTimeout);
                if(result == NotifyByTimeout) {
                    goto end;
                }
            }
        }

        mCacheManager->busyNotify(h);
        
        if(mCurrentTask != nullptr) {
            if(mCurrentTask->getStatus() == FUTURE_CANCEL) {
                mCurrentTask = nullptr;
                continue;
            }

            Runnable r = mCurrentTask->getRunnable();
            if(r != nullptr) {
                r->run();
            }

            mCurrentTask = nullptr;
        }

        //start stealing
        {
            AutoMutex ll(mTaskMutex);
            if(mPool->size() != 0) {
                mCurrentTask = mPool->deQueueFirst();
            }
        }
    }
        

end:
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, nullptr);
    
    mCacheManager->completeNotify(h);
    mCacheManager.remove_pointer();
}

void _ThreadCachedPoolExecutorHandler::onInterrupt() {
    printf("ThreadCachedPoolExecutorHandler onInterrupt \n");
    if(mCurrentTask != nullptr) {
        Runnable r = mCurrentTask->getRunnable();
        if(r != nullptr) {
            r->onInterrupt();
        }

        mCurrentTask = nullptr;
    }

    state = terminateState;

    //printf("ThreadCachedPoolExecutorHandler onInterrupt2 \n");
    ThreadCachedPoolExecutorHandler h;
    h.set_pointer(this);
    mCacheManager->completeNotify(h);
    mCacheManager.remove_pointer();
}

bool _ThreadCachedPoolExecutorHandler::shutdownTask(FutureTask task) {
    printf("shutdown task \n");
    if(mCurrentTask != nullptr && mCurrentTask == task) {
        printf("shutdown task trace1 \n");
        stop();
        return true;
    }

    return false;
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
    init(-1,0,DEFAULT_CACHED_MAX_THREAD_NUMS,DEFAULT_CACHED_THREAD_WAIT_TIME);
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

    mCacheManager->release();
    
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
    return awaitTermination(0);
}

int _ThreadCachedPoolExecutor::awaitTermination(long millseconds) {
    if(!mIsShutDown) {
        return -InvalidStatus;
    }

    if(mIsTerminated) {
        return 0;
    }
    //printf("start1 awaittermination %ld \n",st(System)::currentTimeMillis());
    if(mCacheManager->awaitTermination(millseconds) == NotifyByTimeout) {
        return -WaitTimeout;
    }
    //printf("start2 awaittermination %ld \n",st(System)::currentTimeMillis());
 
    mIsTerminated = true;
    return 0;
}

int _ThreadCachedPoolExecutor::getThreadsNum() {
    int size = mCacheManager->getThreadSum();
}

Future _ThreadCachedPoolExecutor::submit(Runnable r) {
    if(mIsShutDown ||mIsTerminated) {
        return nullptr;
    }

    AutoMutex l(mProtectMutex);

    if(mIsShutDown ||mIsTerminated) {
        return nullptr;
    }

    FutureTaskStatusListener listener;
    listener.set_pointer(this);

    FutureTask task = createFutureTask(FUTURE_TASK_SUBMIT,r,listener);
    Future future = createFuture(task);
    
    mCacheManager->bindTask(task);

    return future;   
}

void _ThreadCachedPoolExecutor::init(int queuesize,int minthreadnum,int maxthreadnum,long timeout) {
    if(queuesize == 0 || minthreadnum > maxthreadnum) {
        throw createInitializeException(createString("ThreadCachedPool"));
    }

    mProtectMutex = createMutex("ThreadCachedMutex");
    mQueueSize = queuesize;
    maxThreadNum = maxthreadnum;
    minThreadNum = minthreadnum;
    mThreadTimeout = timeout;
    mIsTerminated = false;
    mIsShutDown = false;
    
    mHandlerMutex = createMutex("ThreadCachedHandlerMutex");

    mCacheManager = createCacheThreadManager(queuesize,minthreadnum,maxthreadnum,mThreadTimeout);
}

bool _ThreadCachedPoolExecutor::isOverMinSize() {
    return mHandlers->size() > minThreadNum;
}

void _ThreadCachedPoolExecutor::onCancel(FutureTask task) {
    if(mIsShutDown ||mIsTerminated) {
        return;
    }

    AutoMutex l(mProtectMutex);

    if(mIsShutDown ||mIsTerminated) {
        return;
    }

    if(mCacheManager != nullptr) {
        mCacheManager->cancelTask(task);
    }
}

_ThreadCachedPoolExecutor::~_ThreadCachedPoolExecutor() {
    printf("release thread pool \n");
    shutdown();
}


//------------------CacheThreadManager------------------
_CacheThreadManager::_CacheThreadManager(int queueSize,int minThreadNum,int maxThreadNum,int waitTimeout) {

    mQueuesize = queueSize;

    mMinThreadNum = minThreadNum;

    mMaxThreadNum = maxThreadNum;

    mWaitTimeout = waitTimeout;

    if(mQueuesize == -1) {
        mFutureTasks = createBlockingQueue<FutureTask>();
    } else {
        mFutureTasks = createBlockingQueue<FutureTask>(queueSize);
    }

    mIdleHandlerMutex = createMutex("CacheIdleHandlerMutex");

    mRunningHandlerMutex = createMutex("CacheRunningHandlerMutex");

    mFutureTaskMutex = createMutex("FutureTaskMutex");

    mWaitTermMutex = createMutex("WaitTermMutex");

    mWaitTermCond = createCondition();

    mIdleHandlers = createArrayList<ThreadCachedPoolExecutorHandler>();

    mRunningHandlers = createArrayList<ThreadCachedPoolExecutorHandler>();

    for(int count = 0;count <minThreadNum;count++) {
        CacheThreadManager m;
        m.set_pointer(this);
        ThreadCachedPoolExecutorHandler handler = createThreadCachedPoolExecutorHandler(
                    mFutureTasks,
                    mFutureTaskMutex,
                    m,
                    mWaitTimeout);
        handler->start();
        mIdleHandlers->add(handler); 
    }
}

_CacheThreadManager::_CacheThreadManager():_CacheThreadManager(-1,
                                                               0,
                                                               DEFAULT_CACHED_MAX_THREAD_NUMS,
                                                               DEFAULT_CACHED_THREAD_WAIT_TIME) {
    //TODO nothing
}

_CacheThreadManager::~_CacheThreadManager() {
    printf("cacheThread manager release \n");
}

void _CacheThreadManager::bindTask(FutureTask task) {
    //printf("bindTask trace1 \n");
    {
        AutoMutex ll(mIdleHandlerMutex);
        if(mIdleHandlers->size() != 0) {
            //printf("bindTask trace2 \n");
            ThreadCachedPoolExecutorHandler handler = mIdleHandlers->remove(0);
            handler->doTask(task);
            return;
        } 
    }

    {
        int currentThreadNum = this->getThreadSum();
        //printf("bindTask trace3 currentThreadNum is %d \n",currentThreadNum);
        if(currentThreadNum < mMaxThreadNum) {
            CacheThreadManager m;
            m.set_pointer(this);
            ThreadCachedPoolExecutorHandler handler = createThreadCachedPoolExecutorHandler(
                    mFutureTasks,
                    mFutureTaskMutex,
                    m,
                    mWaitTimeout);
            {
                AutoMutex ll(mRunningHandlerMutex);
                mRunningHandlers->add(handler);
            }
            printf("bindTask trace4 \n");
            handler->start();
            handler->doTask(task);
            return;
        }
    }

    mFutureTasks->enQueueLast(task);
}

void _CacheThreadManager::idleNotify(ThreadCachedPoolExecutorHandler handler) {
    {
        AutoMutex ll(mRunningHandlerMutex);
        mRunningHandlers->remove(handler);
    }

    {
        AutoMutex ll(mIdleHandlerMutex);
        mIdleHandlers->add(handler);
    }
}

void _CacheThreadManager::busyNotify(ThreadCachedPoolExecutorHandler handler) {
    {
        AutoMutex ll(mIdleHandlerMutex);
        mIdleHandlers->remove(handler);
    }

    {
        AutoMutex ll(mRunningHandlerMutex);
        mRunningHandlers->add(handler);
    }
}

int _CacheThreadManager::awaitTermination(long timeout) {
    {
        AutoMutex ll(mRunningHandlerMutex);
        if(mRunningHandlers->size() == 0) {
            return NotifyByThread;
        }
    }

    AutoMutex ll(mWaitTermMutex);
    if(timeout == 0) {
        mWaitTermCond->wait(mWaitTermMutex);
    } else {
        if(NotifyByTimeout == mWaitTermCond->wait(mWaitTermMutex,timeout)) {
            return NotifyByTimeout;
        }
    }

    return NotifyByThread;
}

void _CacheThreadManager::completeNotify(ThreadCachedPoolExecutorHandler h) {
    {
        AutoMutex ll(mIdleHandlerMutex);
        if(mIdleHandlers->remove(h) > 0) {
            return;
        }
    }

    {
        AutoMutex ll(mRunningHandlerMutex);
        mRunningHandlers->remove(h);
        if(mRunningHandlers->size() == 0) {
            mWaitTermCond->notifyAll();
        }
    }
}

void _CacheThreadManager::release() {
    printf("_cacheThreadmanager release \n");
    {
        AutoMutex ll(mRunningHandlerMutex);
        //mIdleHandlers->remove(handler);
        ListIterator<ThreadCachedPoolExecutorHandler> list = mRunningHandlers->getIterator();
        while(list->hasValue()) {
            ThreadCachedPoolExecutorHandler h = list->getValue();
            h->stop();
            list->next();
        }

        //mRunningHandlers->clear();
    }

    {
        AutoMutex ll(mIdleHandlerMutex);
        //mIdleHandlers->add(handler);
        ListIterator<ThreadCachedPoolExecutorHandler> list = mIdleHandlers->getIterator();
        while(list->hasValue()) {
            ThreadCachedPoolExecutorHandler h = list->getValue();
            h->stop();
            list->next();
        }

        //mIdleHandlers->clear();
    }

    mFutureTasks->clear();
}

int _CacheThreadManager::getThreadSum() {
    int sum = 0;
    {
        AutoMutex ll(mRunningHandlerMutex);
        sum += mRunningHandlers->size();
    }

    {
        AutoMutex ll(mIdleHandlerMutex);
        sum += mIdleHandlers->size();
    }

    return sum;
}

void _CacheThreadManager::cancelTask(FutureTask task) {
    printf("remove task trace1 \n");
    if(mFutureTasks->remove(task)) {
        printf("remove task trace2 \n");
        return;
    }

    {
        AutoMutex ll(mRunningHandlerMutex);
        //mIdleHandlers->remove(handler);
        ListIterator<ThreadCachedPoolExecutorHandler> list = mRunningHandlers->getIterator();
        ThreadCachedPoolExecutorHandler h = nullptr;
        while(list->hasValue()) {
            h = list->getValue();
            printf("remove task trace3 \n");
            if(h->shutdownTask(task)) {
                break;
            }
            list->next();
        }
    }
}


}
