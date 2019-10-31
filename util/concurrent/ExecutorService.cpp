#include <pthread.h>
#include <map>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Runnable.hpp"
#include "Executor.hpp"
#include "ArrayList.hpp"
#include "Future.hpp"
#include "Executor.hpp"
#include "Callable.hpp"
#include "ExecutorService.hpp"

namespace obotcha {

ExecutorServiceRecycle _ExecutorService::mRecyler;

Mutex _ExecutorService::mRecylerInitMutex = createMutex("ExecutorRecyleMutex");

bool _ExecutorService::isRecylerInited = false;

static void* recycleRun(void *th) {
    _ExecutorServiceRecycle *thread = static_cast<_ExecutorServiceRecycle *>(th);
    thread->run();
    return nullptr;
}

_ExecutorServiceRecycle::_ExecutorServiceRecycle() {
    mWaitingMutex = createMutex("ExecutorServiceRecyleMutex");
    mWaitServices = createArrayList<ExecutorService>();

    mReleaseMutex = createMutex("ExecutorServiceReleaseMutex");
    mReleaseCondition = createCondition();
    mReleaseServices = createArrayList<ExecutorService>();

    mTid = 0;
}

void _ExecutorServiceRecycle::addRecycleService(ExecutorService s) {
    AutoMutex ll(mWaitingMutex);
    printf("addRecycleService trace 1 \n");
    if(!s->isTerminated()) {
        printf("addRecycleService trace 2 \n");
        mWaitServices->add(s);
    }
}

void _ExecutorServiceRecycle::run() {
    while(1) {
        ExecutorService s = nullptr;
        {
            AutoMutex ll1(mReleaseMutex);
            printf("_ExecutorServiceRecycle run1 \n");
            if(mReleaseServices->size() == 0) {
                mReleaseCondition->wait(mReleaseMutex);
            }
            s = mReleaseServices->remove(0);
        }

        if(s == nullptr) {
            printf("_ExecutorServiceRecycle run1_3 \n");
            break;
        }

        AutoMutex ll2(mWaitingMutex);
        ListIterator<ExecutorService> iterator = mWaitServices->getIterator();
        int index = 0;
        printf("mWaitServices before remove size is %d \n",mWaitServices->size());
        while(iterator->hasValue()) {
            ExecutorService t = iterator->getValue();
            t->awaitTermination(10);
            if((t == s) || t->isTerminated()) {
                printf("ExecutorServiceRecycle run2 \n");
                iterator->remove();
                printf("mWaitServices after remove size is %d \n",mWaitServices->size());
                continue;
            }
            iterator->next();
        }
        
        printf("mRelease size is %d,service count is %d ,addr is %lx \n",mReleaseServices->size(),s->getStrongCount(),s.get_pointer());
    }
}

void _ExecutorServiceRecycle::start() {
    pthread_attr_init(&mAttr);
    pthread_create(&mTid, &mAttr, recycleRun, this);
}

void _ExecutorServiceRecycle::onTerminate(ExecutorService s) {
    printf("onTerminate trace 1 \n");
    AutoMutex ll2(mReleaseMutex);
    printf("onTerminate trace 2,count is %d \n",s->getStrongCount());
    mReleaseServices->add(s);
    mReleaseCondition->notify();
    printf("onTerminate trace 3,count is %d \n",s->getStrongCount());
}

bool _ExecutorServiceRecycle::isWaiting(_ExecutorService *s) {

    AutoMutex ll1(mWaitingMutex);
    ListIterator<ExecutorService> iterator = mWaitServices->getIterator();
    while(iterator->hasValue()) {
        ExecutorService ls = iterator->getValue();
        if(s == ls.get_pointer()) {
            return true;
        }
        iterator->next();
    }

    return false;
}

_ExecutorServiceRecycle::~_ExecutorServiceRecycle() {
    if(mTid != 0) {
        printf("~_ExecutorServiceRecycle trace1,addr is %lx \n",this);
        {
            AutoMutex ll(mReleaseMutex);
            printf("~_ExecutorServiceRecycle trace2 \n");
            //mReleaseServices->clear();
            ExecutorService t;
            t.set_pointer(nullptr);
            mReleaseServices->add(t);
            mReleaseCondition->notify();
            printf("~_ExecutorServiceRecycle trace2_1 \n");
        }
        printf("~_ExecutorServiceRecycle trace2 \n");
        //pthread_cancel(mTid);
        pthread_join(mTid,(void **) nullptr);
        printf("~_ExecutorServiceRecycle trace3 \n");
    }
}

//---------------ExecutorService
void _ExecutorService::finishWaitTerminate() {
    printf("finishWaitTerminate trace1 \n");
    if(mRecyler == nullptr) {
        return;
    }

    if(mRecyler->isWaiting(this)) {
        ExecutorService s;
        s.set_pointer(this);

        mRecyler->onTerminate(s);
    }
    
    printf("finishWaitTerminate trace2 \n");
}

void _ExecutorService::startWaitTerminate() {
    if(!isRecylerInited) {
        AutoMutex ll(mRecylerInitMutex);
        if(!isRecylerInited) {
            mRecyler = createExecutorServiceRecycle();
            mRecyler->start();
        }
    }
    printf("this1 count is %d this is %lx\n",this->getStrongCount(),this);
    ExecutorService s;
    s.set_pointer(this);
    mRecyler->addRecycleService(s);
    printf("this2 count is %d,count addr is %lx \n",this->getStrongCount(),this);
}

}
