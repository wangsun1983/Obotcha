#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "Thread.hpp"
#include "AutoMutex.hpp"
#include "ThreadLocal.hpp"

namespace obotcha {

//------------KeepAliveThread---------------//
static void* recycle(void *th) {
    _KeepAliveThread *thread = static_cast<_KeepAliveThread *>(th);
    thread->run();
    return nullptr;
}

_KeepAliveThread::_KeepAliveThread() {
    //printf("_RecycleThread start \n");
    mutex = createMutex("RecyleThreadMutex");
    cond = createCondition();
    queue = createBlockingQueue<Uint64>();
    isRunning = false;
    mThreadLocal = createThreadLocal<sp<_Thread>>();
    //mDestroyMutex = createMutex("RecyleThreadMutex");
    mDestroyBarrier = 0;
}

void _KeepAliveThread::start() {
    //printf("RecyleThread start \n");
    AutoMutex l(mutex);
    //printf("RecyleThread start2 \n");
    if(!isRunning) {
        pthread_create(&mTid, &mAttr, recycle, this);
        isRunning = true;
    }
}

void _KeepAliveThread::run() {
    //printf("RecyleThread run \n");
    //mDestroyMutex->lock();
    if(mDestroyBarrier == 1) {
        //mDestroyMutex->unlock();
        return;
    }

    ThreadLocal<Thread> tLocal = mThreadLocal;
    BlockingQueue<Uint64> mQueue = queue;
    //mDestroyMutex->unlock();

    while(1) {
        Uint64 t = mQueue->deQueueFirst();
        //printf("remove thread \n");
        //t->decStrong(0);
        //TODO
        //printf("remove thread 1,t count is %d, t addr is %x \n",t->getStrongCount(),t.get_pointer());
        if(t == nullptr) {
            return;
        }

        //st(Thread)::removeThread(t);
        //printf("remove thread 2,t count is %d, t addr is %x \n",t->getStrongCount(),t.get_pointer());
      
        //printf("remove thread 2,t count is %d \n",t->getStrongCount());
        
        tLocal->remove(t->toValue());
        //can not print thread's infor,because thread may be released!!
    }
}

/*
void _KeepAliveThread::dropDirect(pthread_t t) {
    ThreadLocal<Thread> tLocal = mThreadLocal;
    tLocal->remove(t);
}
 */

void _KeepAliveThread::save(sp<_Thread> s) {
    mThreadLocal->set(s->mPthread,s);
}

sp<_Thread> _KeepAliveThread::getSavedThread() {
    return mThreadLocal->get();
}

void _KeepAliveThread::drop(pthread_t t){
    //printf("submit trace1,thread count is %d \n",t->getStrongCount());
    queue->enQueueLast(createUint64(t));
    //printf("submit trace2,thread count is %d \n",t->getStrongCount());
}

void _KeepAliveThread::dropDirect(pthread_t t) {
    mThreadLocal->remove(t);
}

_KeepAliveThread::~_KeepAliveThread() {
    //this->exit();
    //mDestroyMutex->lock();
    mDestroyBarrier = 1;
    //mDestroyMutex->unlock();

    pthread_cancel(mTid);

}

//------------Thread Stack function---------------//
void cleanup(void *th) {
    _Thread *thread = static_cast<_Thread *>(th);
    //if(thread->getName() != nullptr) {
    //printf("clean up,sataus is %d \n",thread->mStatus);
    //}
    
    if(thread->getRunnable() != nullptr) {
        thread->getRunnable()->onInterrupt();
    } else {
        thread->onInterrupt();
    }

    //switch(thread->mStatus) {
    //    case ThreadDestroy:
    //        _Thread::getKeepAliveThread()->dropDirect(thread->mPthread);
    //        return;
    //}

    thread->mStatus = ThreadComplete;
    //Thread recyleTh;
    //recyleTh.set_pointer(thread);
    _Thread::getKeepAliveThread()->drop(thread->mPthread);
}

//------------Thread---------------//
KeepAliveThread _Thread::mKeepAliveThread = createKeepAliveThread();
HashMap<int,int *> _Thread::mPriorityTable = createHashMap<int,int *>();
//ThreadLocal<Thread> _Thread::mLocalThreadLocal = createThreadLocal<Thread>();

void* _Thread::localRun(void *th) {
    _Thread *thread = static_cast<_Thread *>(th);
    //thread->mStatus = ThreadRunning;
    KeepAliveThread mKAThread = mKeepAliveThread; 
    sp<_Thread> localThread;
    localThread.set_pointer(thread);
    mKeepAliveThread->save(localThread);
    //wangsl
    thread->bootFlag->orAndGet(1);
    //wangsl

    pthread_cleanup_push(cleanup, th);

    switch(thread->mStatus) {
        case ThreadDestroy:
            localThread.set_pointer(nullptr);
        case ThreadComplete:
            return nullptr;

        default:
        //Do nothing
            break;
    }



    thread->initPolicyAndPriority();

    thread->setSchedPolicy(thread->mPolicy);
    thread->setPriority(thread->mPriority);
    {
        AutoMutex l(thread->mNameMutex);
        if(thread->mName != nullptr) {
            pthread_setname_np(thread->mPthread,thread->mName->toChars());
        }
    }
    
    thread->mStatus = ThreadRunning;
    if(thread->mRunnable != nullptr) {
        thread->mRunnable->run();
        thread->mRunnable = nullptr;
    } else {
        thread->run();
    }
    
    pthread_cleanup_pop(0);
    
    thread->mStatus = ThreadComplete;

    mKAThread->drop(localThread->mPthread);
    
    return nullptr;
}

_Thread::_Thread(Runnable run) {
    mKeepAliveThread->start();
	mRunnable = run;
    mStatus = ThreadNotStart;
    mNameMutex = createMutex("theradNameMutex");
    bootFlag = createAtomicInteger(0);
}

_Thread::_Thread(String name,Runnable run) {
    mName = name;
    mKeepAliveThread->start();
    mRunnable = run;
    mStatus = ThreadNotStart;

    mNameMutex = createMutex("theradNameMutex");
    bootFlag = createAtomicInteger(0);
}

_Thread::_Thread() {
    //Nothing
    mPolicy = ThreadSchedOTHER;
    mPriority = ThreadLowPriority;
    mStatus = ThreadNotStart;

    mNameMutex = createMutex("theradNameMutex");
    bootFlag = createAtomicInteger(0);
}

int _Thread::setName(String name) {
    AutoMutex l(mNameMutex);
    mName = name;

    switch(mStatus) {
        case ThreadIdle:
        case ThreadNotStart:
            return -ThreadFailReason::ThreadFailNotStart;

        case ThreadComplete:
            return -ThreadFailReason::ThreadFailAllreadyComplete;

        case ThreadDestroy:
            return -ThreadFailReason::ThreadFailAllreadyDestroy;
    }
    
    pthread_setname_np(mPthread,name->toChars());
    return 0;
}

String _Thread::getName() {
    AutoMutex l(mNameMutex);
    return mName;
}

_Thread::~_Thread(){
    if(mStatus == ThreadIdle) {
        mStatus = ThreadDestroy;
        join();
        return;
    } else if(mStatus == ThreadNotStart){
        //pthread_cancel(mPthread);
    }

    mStatus = ThreadDestroy;
}

Runnable _Thread::getRunnable() {
    return mRunnable;
}

void _Thread::run() {
    //child thread can overwrite it.
}																									

int _Thread::start() {
    //pthread_create(&mPthread, &mThreadAttr, localRun, this);
    //if we use sp or declare a thread on stack
    //eg.
    //{
    //   Thread t1 = new Thread(new Runnable(setThreadSchedPolicy) {xxxxxx});
    //   t1->start();
    //}
    //when we leave the life circle,the thread is still running
    //the release may cause the corruption.
    //we should incStrong.after the thread complete,
    //we force decStrong to release;
    //incStrong(0);
    //sp<_Thread> localThread;
    //localThread.set_pointer(this);
    switch(mStatus) {
        case ThreadRunning:
        case ThreadComplete:
            return -ThreadFailReason::ThreadFailAllreadyComplete;

        case ThreadDestroy:
            return -ThreadFailReason::ThreadFailAllreadyDestroy;
    }

    mStatus = ThreadIdle;

    pthread_attr_init(&mThreadAttr);
    pthread_create(&mPthread, &mThreadAttr, localRun, this);
    while(bootFlag->orAndGet(0) == 0) {
        //wait
    }
    return 0;
}

void _Thread::initPolicyAndPriority() {
    int policy = ThreadSchedOTHER;
    pthread_attr_getschedpolicy(&mThreadAttr,&policy);
    updateThreadPrioTable(policy);
}

void _Thread::join() {
	pthread_join(mPthread,(void **) nullptr);
}

void _Thread::join(long timeInterval) {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);

    long secs = timeInterval/1000;
    timeInterval = timeInterval%1000;

    long add = 0;
    timeInterval = timeInterval*1000*1000 + ts.tv_nsec;
    add = timeInterval / (1000*1000*1000);
    ts.tv_sec += (add + secs);
    ts.tv_nsec = timeInterval%(1000*1000*1000);

    pthread_timedjoin_np(mPthread,nullptr,&ts);
}

int _Thread::getStatus() {
    int pthread_kill_err = 0;
    return mStatus;
}


void _Thread::exit() {
    if(mStatus == ThreadComplete) {
        return;
    }
    
    if(mStatus == ThreadNotStart) {
        return;
    }

    if(mStatus == ThreadIdle) {
        mStatus == ThreadDestroy;
        while(1) {
            join(100);
            if(mStatus == ThreadRunning) {
                mStatus = ThreadComplete;
                pthread_cancel(mPthread);
                return;
            } else if(mStatus == ThreadComplete) {
                return;
            }
        }
        
        return;
    }

    mStatus = ThreadComplete;
    pthread_cancel(mPthread);
}

int _Thread::setPriority(ThreadPriority priority) {
    //printf("setPriority mPolicy is %d trace1 \n",mPolicy);
    switch(mStatus) {
        case ThreadIdle:
        case ThreadNotStart:
            return -ThreadFailReason::ThreadFailNotStart;

        case ThreadComplete:
            return -ThreadFailReason::ThreadFailAllreadyComplete;

        case ThreadDestroy:
            return -ThreadFailReason::ThreadFailAllreadyDestroy;
    }

    if(mPolicy == ThreadSchedPolicy::ThreadSchedOTHER) {
        return -ThreadFailReason::ThreadFailNoPrioritySupport;
    }
    //printf("setPriority trace2 \n");
    mPriority = priority;
    
    int schedPrio = mPriorityTable->get(mPolicy)[priority];
    //printf("setPriority is %d \n",schedPrio);
    struct sched_param param;
    pthread_attr_getschedparam(&mThreadAttr, &param);

    param.sched_priority = schedPrio;
    return pthread_attr_setschedparam(&mThreadAttr, &param);
}

int _Thread::getPriority() {
    struct sched_param param;
    if(mStatus != ThreadRunning) {
        return -ThreadFailNotStart;
    }

    int rs = pthread_attr_getschedparam(&mThreadAttr, &param);
    if(rs == 0) {
        return SchePrio2threadPrio(param.__sched_priority);
    }

    return -1;
}

int _Thread::setSchedPolicy(ThreadSchedPolicy policy) {
    
    switch(mStatus) {
        case ThreadIdle:
        case ThreadNotStart:
            return -ThreadFailReason::ThreadFailNotStart;

        case ThreadComplete:
            return -ThreadFailReason::ThreadFailAllreadyComplete;

        case ThreadDestroy:
            return -ThreadFailReason::ThreadFailAllreadyDestroy;
    }

    if(policy != ThreadSchedOTHER
        &&policy != ThreadSchedFIFO
        &&policy != ThreadSchedRR) {
        return -ThreadFailUnknowPolicy;
    }

    int rs = pthread_attr_setschedpolicy(&mThreadAttr, policy);
    if(rs != 0) {
        return -ThreadFailActionFail;
    }

    mPolicy = policy;
    updateThreadPrioTable(policy);
    if(rs == 0) {
        return 0;
    }

    return -ThreadFailActionFail;

}

int _Thread::getSchedPolicy() {
    if(mStatus != ThreadRunning) {
        return ThreadFailNotStart;
    }

    int policy = ThreadSchedOTHER;
    int rs = pthread_attr_getschedpolicy(&mThreadAttr, &policy);
    if(rs != 0) {
        return -ThreadFailActionFail;
    }
    return policy;
}

void _Thread::onInterrupt() {
    //need overwrite by child class
}


void _Thread::yield() {
    pthread_yield();
}

void _Thread::msleep(unsigned long t) {
    usleep(t*1000);
}

int _Thread::threadPrio2SchePrio(int threadprio) {
    return mPriorityTable->get(mPolicy)[threadprio];
}

int _Thread::SchePrio2threadPrio(int schedPrio) {
    int index = ThreadLowestPriority;
    int *table = mPriorityTable->get(mPolicy);

    for(;index < ThreadPriorityMax;index++) {
        if(table[index] >= schedPrio) {
            break;
        }
    }

    if(index == 0) {
        return ThreadLowestPriority;
    }

    return index--;
}

int _Thread::updateThreadPrioTable(int policy) {

    int *table = mPriorityTable->get(policy);
    if(table != nullptr) {
        return 0;
    }

    int maxPrio = sched_get_priority_max (policy);
    int minPrio = sched_get_priority_min (policy);
    
    table = new int[ThreadPriorityMax];
   
    int interval = (maxPrio - minPrio)/ThreadHighestPriority;
    for(int i = ThreadLowestPriority;i < ThreadPriorityMax-1;i++) {
        table[i] = (minPrio/10)*10;
        minPrio += interval;
    }

    table[ThreadHighestPriority] = maxPrio;
    mPriorityTable->put(policy,table);
    return 0;
}

void _Thread::setThreadPriority(ThreadPriority priority) {
    Thread thread = mKeepAliveThread->getSavedThread();
    if(thread != nullptr) {
        thread->setPriority(priority);
    }
}

int _Thread::getThreadPriority() {
    Thread thread = mKeepAliveThread->getSavedThread();
    if(thread != nullptr) {
        return thread->getPriority();
    }

    return -ThreadFailActionFail;
}

bool _Thread::setThreadSchedPolicy(ThreadSchedPolicy policy) {
    Thread thread = mKeepAliveThread->getSavedThread();
    return thread->setSchedPolicy(policy);
}

int _Thread::getThreadSchedPolicy() {
    Thread thread = mKeepAliveThread->getSavedThread();
    return thread->getSchedPolicy();
}

KeepAliveThread _Thread::getKeepAliveThread(){
    return mKeepAliveThread;
}

}