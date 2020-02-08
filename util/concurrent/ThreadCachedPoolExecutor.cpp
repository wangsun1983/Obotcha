#include <stdio.h>
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
#include "ExecutorDestructorException.hpp"
#include "Log.hpp"

namespace obotcha {

#define TAG "ThreadCachedPool"

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

    isNotifed = false;
}

_ThreadCachedPoolExecutorHandler::~_ThreadCachedPoolExecutorHandler() {
    mCurrentTask = nullptr;
    mCacheManager.remove_pointer();
}

void _ThreadCachedPoolExecutorHandler::stop() {
    mStop = true;
    quit();
}

void _ThreadCachedPoolExecutorHandler::doTask(FutureTask task) {
    mCurrentTask = task;
    isNotifed = true;
    mTaskCondition->notify();
}

void _ThreadCachedPoolExecutorHandler::run() {
    ThreadCachedPoolExecutorHandler h;
    h.set_pointer(this);

    while(!mStop) {
        //long start = st(System)::currentTimeMillis();

        {
            AutoMutex ll(mTaskWaitMutex);
            if(mCurrentTask == nullptr) {
                
                if(mCacheManager->idleNotify(h) != CachedNotifySuccess) {
                    goto end;
                }

                int result = mTaskCondition->wait(mTaskWaitMutex,mThreadTimeout);
                if(result == NotifyByTimeout) {
                    goto end;
                }
                isNotifed = true;
            }
        }

        if(isNotifed) {
            if(mCacheManager->busyNotify(h)) {                
                goto end;
            }
        }
        
        
        if(mCurrentTask != nullptr) {
            if(mCurrentTask->getStatus() == FUTURE_CANCEL) {
                mCurrentTask = nullptr;
                continue;
            }

            Runnable r = mCurrentTask->getRunnable();
            if(r != nullptr) {
                r->run();
            }

            mCurrentTask->onComplete();
            mCurrentTask = nullptr;

        }

        //start stealing
        {
            AutoMutex ll(mTaskMutex);
            if(mPool->size() != 0) {
                mCurrentTask = mPool->deQueueFirst();
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
    if(mCurrentTask != nullptr) {
        Runnable r = mCurrentTask->getRunnable();
        if(r != nullptr) {
            r->onInterrupt();
        }

        mCurrentTask = nullptr;
    }

    state = terminateState;

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

bool _ThreadCachedPoolExecutorHandler::isTerminated() {
    return state == terminateState;
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

    AutoMutex l(mProtectMutex);

    if(mIsShutDown ||mIsTerminated) {
        return -AlreadyDestroy;
    }

    mIsShutDown = true;

    mCacheManager->release();
    if(mCacheManager->getThreadSum() != 0) {
        //mCacheManager.remove_pointer();
        //TODO
    } else {
        mCacheManager->removeExecutor();
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
    return mCacheManager->isTerminated();
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

    if(mCacheManager->awaitTermination(millseconds) == NotifyByTimeout) {
        return -WaitTimeout;
    }
    
    mIsTerminated = true;
    return 0;
}

int _ThreadCachedPoolExecutor::getThreadsNum() {
    int size = mCacheManager->getThreadSum();
    return size;
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
    //shutdown();
    if(!mIsShutDown) {
        //cannot throw exception in destructor
        //throw ExecutorDestructorException("ThreadCachedPoolExecutor destruct error");
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

    mFutureTaskMutex = createMutex("FutureTaskMutex");

    mWaitTermMutex = createMutex("WaitTermMutex");

    mCompleteNotifyMutex = createMutex("CompleteNotifyMutex");

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
        AutoMutex ll(mReleaseMutex);
        if(mIsRelease) {
            return;
        }
    }
    
    {
        AutoMutex ll(mIdleHandlerMutex);
        if(mIdleHandlers->size() != 0) {
            ThreadCachedPoolExecutorHandler handler = mIdleHandlers->removeAt(0);
            handler->doTask(task);
            return;
        } 
    }

    {
        int currentThreadNum = this->getThreadSum();
        AutoMutex ll(mRunningHandlerMutex);
        
        if(currentThreadNum < mMaxThreadNum) {
            CacheThreadManager m;
            m.set_pointer(this);
            ThreadCachedPoolExecutorHandler handler = createThreadCachedPoolExecutorHandler(
                    mFutureTasks,
                    mFutureTaskMutex,
                    m,
                    mWaitTimeout);
            {
                AutoMutex ll2(mCreatingHandlerMutex);
                mCreatingHandlers->add(handler);
            }

            handler->doTask(task);
            handler->start();

            return;
        }
    }
    
    mFutureTasks->enQueueLast(task);
}

int _CacheThreadManager::idleNotify(ThreadCachedPoolExecutorHandler handler) {

    {
        AutoMutex ll(mReleaseMutex);
        if(mIsRelease) {
            return CachedNotifyFailAlreadyRelease;
        }
    }

    {
        AutoMutex ll(mCreatingHandlerMutex);
        mCreatingHandlers->remove(handler);
    }

    {
        AutoMutex ll(mRunningHandlerMutex);
        mRunningHandlers->remove(handler);
    }

    {
        AutoMutex ll(mIdleHandlerMutex);
        mIdleHandlers->add(handler);
    }

    return 0;
}

int _CacheThreadManager::busyNotify(ThreadCachedPoolExecutorHandler handler) {
    {
        AutoMutex ll(mReleaseMutex);
        if(mIsRelease) {
            return CachedNotifyFailAlreadyRelease;
        }
    }

    {
        AutoMutex ll(mCreatingHandlerMutex);
        mCreatingHandlers->remove(handler);
    }

    {
        AutoMutex ll(mIdleHandlerMutex);
        mIdleHandlers->remove(handler);
    }

    {
        AutoMutex ll(mRunningHandlerMutex);
        mRunningHandlers->add(handler);
    }
}

bool _CacheThreadManager::isTerminated() {
    return mIsTerminated;
}

int _CacheThreadManager::awaitTermination(long timeout) {
    {
        AutoMutex ll(mReleaseMutex);
        if(mIsRelease && getThreadSum() == 0) {
            return NotifyByThread;
        }
    }

    AutoMutex ll(mWaitTermMutex);
    if(mIsTerminated) {
        return NotifyByThread;
    }
    
    if(NotifyByTimeout == mWaitTermCond->wait(mWaitTermMutex,timeout)) {
        return NotifyByTimeout;
    }
    
    return NotifyByThread;
}

void _CacheThreadManager::completeNotify(ThreadCachedPoolExecutorHandler h) {
    
    int removeCreatingResult = -1;
    int removeIdleResult = -1;
    int removeRunningResult = -1;
    {
        AutoMutex ll(mCreatingHandlerMutex);
        removeCreatingResult = mCreatingHandlers->remove(h);
        if(removeCreatingResult >= 0) {
            goto end;
        }
    }

    {
        AutoMutex ll(mIdleHandlerMutex);
        removeIdleResult = mIdleHandlers->remove(h);
        if(removeIdleResult >= 0) {
            goto end;
        }
    }

    {
        AutoMutex ll(mRunningHandlerMutex);

        removeRunningResult = mRunningHandlers->remove(h);
        if(removeRunningResult >= 0) {
            //{
            //    AutoMutex ll(mWaitTermMutex);
            //    mIsTerminated->set(true);
            //    mWaitTermCond->notifyAll();
            //}

            //mExecutor->finishWaitTerminate();
            //mExecutor.remove_pointer();
            goto end;
        }
    }

    goto exit;

end:
    if(getThreadSum() == 0) {
        if(mIsTerminated) {
            goto exit;
        }

        AutoMutex ll(mCompleteNotifyMutex);
        if(mIsTerminated) {
            goto exit;
        }

        if(mIsRelease) {
            mIsTerminated = true;
            mWaitTermCond->notifyAll();
            if(mExecutor != nullptr) {
                //mExecutor->finishWaitTerminate();
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
        AutoMutex ll(mReleaseMutex);
        if(mIsRelease) {
            return;
        }

        mIsRelease = true;
    }

    //mFutureTasks->clear();

    {
        AutoMutex ll(mCreatingHandlerMutex);
        ListIterator<ThreadCachedPoolExecutorHandler> list = mCreatingHandlers->getIterator();
        while(list->hasValue()) {
            ThreadCachedPoolExecutorHandler h = list->getValue();
            h->stop();
            list->next();
        }
    }

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
    {
        AutoMutex ll(mFutureTaskMutex);
        while(mFutureTasks->size() != 0) {
            FutureTask removeTask = mFutureTasks->deQueueLast();
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
    int sum = 0;
    {
        AutoMutex ll0(mCreatingHandlerMutex);
        AutoMutex ll1(mIdleHandlerMutex);
        AutoMutex ll2(mRunningHandlerMutex);
        sum += mCreatingHandlers->size(); 
        sum += mRunningHandlers->size();
        sum += mIdleHandlers->size();
    }

    return sum;
}

void _CacheThreadManager::cancelTask(FutureTask task) {
    if(mFutureTasks->remove(task)) {
        return;
    }

    {
        AutoMutex ll(mRunningHandlerMutex);
        //mIdleHandlers->remove(handler);
        ListIterator<ThreadCachedPoolExecutorHandler> list = mRunningHandlers->getIterator();
        ThreadCachedPoolExecutorHandler h = nullptr;
        while(list->hasValue()) {
            h = list->getValue();
            if(h->shutdownTask(task)) {
                break;
            }
            list->next();
        }
    }
}

}
