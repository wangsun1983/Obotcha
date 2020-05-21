#include <stdio.h>
#include <vector>
#include <unistd.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Runnable.hpp"
#include "BlockingQueue.hpp"
#include "ConcurrentQueue.hpp"
#include "Thread.hpp"
#include "AutoLock.hpp"
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
#include "ExecutorDestructorException.hpp"
#include "Log.hpp"
#include "Error.hpp"

namespace obotcha {

#define TAG "ThreadCachedPool"

#define DEFAULT_CACHED_THREAD_WAIT_TIME 15*1000
#define DEFAULT_CACHED_MAX_THREAD_NUMS 4
#define DEFAULT_CACHED_QUEUE_NUMS 32    

_ThreadCachedPoolExecutorHandler::_ThreadCachedPoolExecutorHandler(BlockingQueue<FutureTask> pool,
                                                                   CacheThreadManager manager, 
                                                                   long timeout)
                                                                         :mPool(pool),
                                                                         mStop(false),
                                                                         mCacheManager(manager){
    
    mThreadTimeout = timeout;

    isNotifed = false;

    mTaskMutex = createMutex("CachedTaskMutex");

    mCurrentTask = nullptr;

    mStop = false;
}

_ThreadCachedPoolExecutorHandler::~_ThreadCachedPoolExecutorHandler() {
    mCurrentTask = nullptr;
    mCacheManager.remove_pointer();
}

void _ThreadCachedPoolExecutorHandler::stop() {
    mStop = true;
    quit();
}

void _ThreadCachedPoolExecutorHandler::run() {
    ThreadCachedPoolExecutorHandler h;
    h.set_pointer(this);

    while(!mStop) {
        {
            //step 1
            if(mCurrentTask == nullptr) {
                if(mCacheManager->idleNotify(h) != 0) {
                    goto end;
                }
                
                //step 2
                mCurrentTask = mPool->deQueueLast(mThreadTimeout);
                if(mCurrentTask == nullptr) {
                    goto end;
                }
                isNotifed = true;
            }
        }

        //step 3
        if(isNotifed) {
            if(mCacheManager->busyNotify(h) != 0) {  
                goto end;
            }
            
            //when add task between step2 & step3
            //mPool is 0 and idleHandlers >0,new task
            //will be add into list instead of createing
            //no thread.just try to create a thread~.
            if(mPool->size() > 0) {
                mCacheManager->setupOneIdleThread();
            }
        }
        
        
        if(mCurrentTask != nullptr) {
            if(mCurrentTask->getStatus() == st(Future)::Cancel) {
                {
                    AutoLock l(mTaskMutex);
                    mCurrentTask = nullptr;
                }
                goto steal;
            }

            if(mCurrentTask->getType() == FUTURE_TASK_SUBMIT) {
                mCurrentTask->onRunning();
            }

            Runnable r = mCurrentTask->getRunnable();
            if(r != nullptr) {
                r->run();
            }
            
            {
                AutoLock l(mTaskMutex);
                if(mCurrentTask->getType() == FUTURE_TASK_SUBMIT) {
                    mCurrentTask->onComplete();
                }

                {
                    AutoLock l(mTaskMutex);
                    mCurrentTask = nullptr;
                }
            }
        }

        //start stealing
steal:        
        {
            if(mPool->size() != 0) {
                {
                    AutoLock l(mTaskMutex);
                    mCurrentTask = mPool->deQueueLastNoBlock();
                }
                isNotifed = false;
            }
        }
    }

end:
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, nullptr);
    if(mCacheManager != nullptr) {
        mCacheManager->completeNotify(h);
        mCacheManager.remove_pointer();
    }
}

void _ThreadCachedPoolExecutorHandler::onInterrupt() {
    {
        AutoLock l(mTaskMutex);
        if(mCurrentTask != nullptr) {
            Runnable r = mCurrentTask->getRunnable();
            if(r != nullptr) {
                r->onInterrupt();
            }
            mCurrentTask = nullptr;
        }
    }

    ThreadCachedPoolExecutorHandler h;
    h.set_pointer(this);
    mCacheManager->completeNotify(h);
    mCacheManager.remove_pointer();
}

bool _ThreadCachedPoolExecutorHandler::shutdownTask(FutureTask task) {
    if(mCurrentTask != nullptr && mCurrentTask == task) {
        stop();
        return true;
    }

    return false;
}

//---------------ThreadCachedPoolExecutor ---------------------
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

    AutoLock l(mProtectMutex);

    if(mIsShutDown ||mIsTerminated) {
        return -AlreadyDestroy;
    }

    mIsShutDown = true;

    mCacheManager->release();
    
    if(mCacheManager->awaitTermination(500) != 0) {
        LOGE(TAG,"ThreadCachePoolExecutor release timeout");
    }

    mCacheManager->removeExecutor();
    
    return 0;
}

int _ThreadCachedPoolExecutor::execute(Runnable r) {
    
    if(submit(r) == nullptr) {
        return -InvalidStatus;
    }

    return 0;
}

bool _ThreadCachedPoolExecutor::isTerminated() {
    return mCacheManager->isTerminated();
}

void _ThreadCachedPoolExecutor::awaitTermination() {
    awaitTermination(0);
}

int _ThreadCachedPoolExecutor::awaitTermination(long millseconds) {
    if(!mIsShutDown) {
        return -InvalidStatus;
    }

    if(mIsTerminated) {
        return 0;
    }

    mIsTerminated = true;

    return mCacheManager->awaitTermination(millseconds);
}

int _ThreadCachedPoolExecutor::getThreadsNum() {
    return mCacheManager->getThreadSum();;
}

Future _ThreadCachedPoolExecutor::submit(Runnable r) {
    if(mIsShutDown ||mIsTerminated) {
        return nullptr;
    }

    AutoLock l(mProtectMutex);

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
        throw InitializeException(createString("ThreadCachedPool"));
    }

    mProtectMutex = createMutex("ThreadCachedMutex");
    mQueueSize = queuesize;
    maxThreadNum = maxthreadnum;
    minThreadNum = minthreadnum;
    mThreadTimeout = timeout;
    mIsTerminated = false;
    mIsShutDown = false;
    
    mHandlerMutex = createMutex("ThreadCachedHandlerMutex");

    ThreadCachedPoolExecutor t;
    t.set_pointer(this);
    mCacheManager = createCacheThreadManager(queuesize,minthreadnum,maxthreadnum,mThreadTimeout,t);
}

void _ThreadCachedPoolExecutor::onCancel(FutureTask task) {
    if(mIsShutDown ||mIsTerminated) {
        return;
    }

    AutoLock l(mProtectMutex);

    if(mIsShutDown ||mIsTerminated) {
        return;
    }

    if(mCacheManager != nullptr) {
        mCacheManager->cancelTask(task);
    }
}

_ThreadCachedPoolExecutor::~_ThreadCachedPoolExecutor() {
    if(!mIsShutDown) {
        //cannot throw exception in destructor
        LOGE(TAG,"ThreadCachedPoolExecutor destruct error");
    }
}


//------------------CacheThreadManager------------------
_CacheThreadManager::_CacheThreadManager(int queueSize,int minThreadNum,int maxThreadNum,int waitTimeout,ThreadCachedPoolExecutor executor) {

    mQueuesize = queueSize;

    mMinThreadNum = minThreadNum;

    mMaxThreadNum = maxThreadNum;

    mWaitTimeout = waitTimeout;

    mIsTerminated = false;

    if(mQueuesize == -1) {
        mFutureTasks = createBlockingQueue<FutureTask>();
    } else {
        mFutureTasks = createBlockingQueue<FutureTask>(queueSize);
    }

    mIdleHandlerMutex = createMutex("CacheIdleHandlerMutex");

    mRunningHandlerMutex = createMutex("CacheRunningHandlerMutex");

    mWaitTermMutex = createMutex("WaitTermMutex");

    mCompleteNotifyMutex = createMutex("CompleteNotifyMutex");

    mThreadNumMutex = createMutex("ThreadNumMutex");

    mThreadNum = 0;

    mWaitTermCond = createCondition();

    mIdleHandlers = createArrayList<ThreadCachedPoolExecutorHandler>();

    mRunningHandlers = createArrayList<ThreadCachedPoolExecutorHandler>();

    mCreatingHandlers = createArrayList<ThreadCachedPoolExecutorHandler>();

    mCreatingHandlerMutex = createMutex("creatingMutex");

    mReleaseMutex = createMutex("CacheThreadReleaseMutex");
    
    mIsRelease = false;

    mExecutor = executor;
}

_CacheThreadManager::_CacheThreadManager():_CacheThreadManager(-1,
                                                               0,
                                                               DEFAULT_CACHED_MAX_THREAD_NUMS,
                                                               DEFAULT_CACHED_THREAD_WAIT_TIME,
                                                               nullptr) {
    //TODO nothing
}

_CacheThreadManager::~_CacheThreadManager() {

}

void _CacheThreadManager::bindTask(FutureTask task) {
    //check wether
    {
        AutoLock ll(mReleaseMutex);
        if(mIsRelease) {
            return;
        }
    }
    
    {
        if(mIdleHandlers->size() != 0 && mFutureTasks->size() == 0) {
            mFutureTasks->enQueueLast(task);
            return;
        } 
    }

    setupOneIdleThread();
    mFutureTasks->enQueueLast(task);
}

int _CacheThreadManager::idleNotify(ThreadCachedPoolExecutorHandler handler) {
    {
        AutoLock ll(mReleaseMutex);
        if(mIsRelease) {
            return -InvalidStatus;
        }
    }

    {
        AutoLock ll(mCreatingHandlerMutex);
        mCreatingHandlers->remove(handler);
    }

    {
        AutoLock ll(mRunningHandlerMutex);
        mRunningHandlers->remove(handler);
    }

    {
        AutoLock ll(mIdleHandlerMutex);
        mIdleHandlers->add(handler);
    }

    return 0;
}

int _CacheThreadManager::busyNotify(ThreadCachedPoolExecutorHandler handler) {
    {
        AutoLock ll(mReleaseMutex);
        if(mIsRelease) {
            return -InvalidStatus;
        }
    }

    {
        AutoLock ll(mCreatingHandlerMutex);
        mCreatingHandlers->remove(handler);
    }

    {
        AutoLock ll(mIdleHandlerMutex);
        mIdleHandlers->remove(handler);
    }

    {
        AutoLock ll(mRunningHandlerMutex);      
        mRunningHandlers->add(handler);
    }

    return  0;
}

bool _CacheThreadManager::isTerminated() {
    return mIsTerminated;
}

int _CacheThreadManager::awaitTermination(long timeout) {
    {
        AutoLock ll(mReleaseMutex);
        if(mIsRelease && getThreadSum() == 0) {
            return 0;
        }
    }

    AutoLock ll(mWaitTermMutex);
    if(mIsTerminated) {
        return 0;
    }
    
    return mWaitTermCond->wait(mWaitTermMutex,timeout);
}

void _CacheThreadManager::completeNotify(ThreadCachedPoolExecutorHandler h) {
    {
        AutoLock ll(mCreatingHandlerMutex);
        if(mCreatingHandlers->remove(h) >= 0) {
            goto end;
        }
    }

    {
        AutoLock ll(mIdleHandlerMutex);
        if(mIdleHandlers->remove(h) >= 0) {
            goto end;
        }
    }

    {
        AutoLock ll(mRunningHandlerMutex);
        if(mRunningHandlers->remove(h) >= 0) {
            goto end;
        }
    }

    goto exit;

end:
    {
        AutoLock l(mThreadNumMutex);
        mThreadNum--;
    }

    if(getThreadSum() == 0) {
        if(mIsTerminated) {
            goto exit;
        }

        AutoLock ll(mCompleteNotifyMutex);
        if(mIsTerminated) {
            goto exit;
        }

        if(mIsRelease) {
            mIsTerminated = true;
            mWaitTermCond->notifyAll();
            if(mExecutor != nullptr) {
                mExecutor.remove_pointer();
            }
        }
    }

exit:
    return;
}

void _CacheThreadManager::release() {
    if(mIsRelease) {
        return;
    }

    {
        AutoLock ll(mReleaseMutex);
        if(mIsRelease) {
            return;
        }

        mIsRelease = true;
    }

    {
        AutoLock ll(mCreatingHandlerMutex);
        ListIterator<ThreadCachedPoolExecutorHandler> list = mCreatingHandlers->getIterator();
        while(list->hasValue()) {
            ThreadCachedPoolExecutorHandler h = list->getValue();
            h->stop();
            list->next();
        }
    }

    {
        AutoLock ll(mRunningHandlerMutex);
        ListIterator<ThreadCachedPoolExecutorHandler> list = mRunningHandlers->getIterator();
        while(list->hasValue()) {
            ThreadCachedPoolExecutorHandler h = list->getValue();
            h->stop();
            list->next();
        }
    }
    
    {
        AutoLock ll(mIdleHandlerMutex);
        ListIterator<ThreadCachedPoolExecutorHandler> list = mIdleHandlers->getIterator();
        while(list->hasValue()) {
            ThreadCachedPoolExecutorHandler h = list->getValue();
            h->stop();
            list->next();
        }
    }

    {
        while(true) {
            FutureTask removeTask = mFutureTasks->deQueueLastNoBlock();
            if(removeTask == nullptr) {
                break;
            }

            Runnable r = removeTask->getRunnable();
            if(r != nullptr) {
                r->onInterrupt();
            }
        }
    }
}

void _CacheThreadManager::removeExecutor() {
    if(mExecutor != nullptr) {
        mExecutor.remove_pointer();
    }
}

int _CacheThreadManager::getThreadSum() {
    AutoLock l(mThreadNumMutex);
    return mThreadNum;
}

void _CacheThreadManager::cancelTask(FutureTask task) {
    bool isCancelTask = false;

    if(mFutureTasks->remove(task)) {
        return;
    }

    {
        AutoLock ll(mRunningHandlerMutex);
        ListIterator<ThreadCachedPoolExecutorHandler> list = mRunningHandlers->getIterator();
        ThreadCachedPoolExecutorHandler h = nullptr;
        while(list->hasValue()) {
            h = list->getValue();
            if(h->shutdownTask(task)) {
                isCancelTask = true;
                break;
            }
            list->next();
        }
    }

    if(isCancelTask && mFutureTasks->size() != 0) {
        setupOneIdleThread();
    }
}

void _CacheThreadManager::setupOneIdleThread() {
    AutoLock l(mThreadNumMutex);
    int currentThreadNum = this->getThreadSum();
    if(currentThreadNum < mMaxThreadNum) {
        CacheThreadManager m;
        m.set_pointer(this);
        ThreadCachedPoolExecutorHandler handler = createThreadCachedPoolExecutorHandler(
                    mFutureTasks,
                    m,
                    mWaitTimeout);
        {
            AutoLock ll2(mCreatingHandlerMutex);
            mCreatingHandlers->add(handler);
        }

        handler->start();
        mThreadNum++;
    }
}


}
