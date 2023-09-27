#include "FilaCondition.hpp"
#include "FilaRoutine.hpp"
#include "IllegalStateException.hpp"
#include "TimeWatcher.hpp"
#include "Log.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

FilaMutex _FilaCondition::mWaitMutex = createFilaMutex();
HashMap<FilaCondition,HashSet<WaitRoutine>>_FilaCondition::mWaitRoutines
    = createHashMap<FilaCondition,HashSet<WaitRoutine>>();

//-----WaitRoutine----
_WaitRoutine::_WaitRoutine(sp<_FilaRoutine>r):routine(r) {
}

//-----FilaCondition----
int _FilaCondition::wait(FilaMutex m,long int mseconds) {
    if(!m->isOwner()) {
        Trigger(IllegalStateException,
                "Wait without getting the ownership of mutex")
    }
    if(GetCurrThreadCo() == nullptr) {
        return mThreadCond->wait(m->mMutex,mseconds);
    } else {
        addWaitRoutine();
        m->unlock();
        TimeWatcher watch = createTimeWatcher();
        if(mseconds > 0) {
            watch->start();
        }
        co_cond_timedwait(mCond, mseconds); 
        if(mseconds > 0) {
            long interval = watch->stop();
            if(interval >= mseconds) {
                removeWaitRoutine();
                return -ETIMEDOUT;
            }
        }
        m->lock();
        removeWaitRoutine();
    }
    return 0;
}

int _FilaCondition::getWaitCounts() {
    AutoLock l(mWaitMutex);
    auto croutine = Cast<FilaRoutine>(st(Thread)::Current());
    auto waitSets = mWaitRoutines->get(AutoClone(this));
    int count = 0;
    if(waitSets != nullptr) {
        ForEveryOne(waitRoutine,waitSets) {
            count += waitRoutine->count;
        }
    }
    return count;
}

void _FilaCondition::addWaitRoutine() {
    AutoLock l(mWaitMutex);
    auto croutine = Cast<FilaRoutine>(st(Thread)::Current());
    if(croutine == nullptr) {
      LOG(ERROR)<<"addWaitCondition,croutine is null";
      return;
    }

    auto waitSets = mWaitRoutines->get(AutoClone(this));
    if(waitSets == nullptr) {
        waitSets = createHashSet<WaitRoutine>();
        mWaitRoutines->put(AutoClone(this),waitSets);
    }

    ForEveryOne(waitRoutine,waitSets) {
        if(waitRoutine->routine == croutine) {
            waitRoutine->count++;
            return;
        }
    }

    waitSets->add(createWaitRoutine(croutine));
}

void _FilaCondition::removeWaitRoutine() {
    auto croutine = Cast<FilaRoutine>(st(Thread)::Current());

    AutoLock l(mWaitMutex);
    auto waitSets = mWaitRoutines->get(AutoClone(this));
    ForEveryOne(waitRoutine,waitSets) {
        if(waitRoutine->routine == croutine) {
            waitRoutine->count--;
            if(waitRoutine->count == 0) {
                waitSets->remove(waitRoutine);
            }
            return;
        }
    }
}

void _FilaCondition::notify() {
    AutoLock l(mWaitMutex);
    auto sets = mWaitRoutines->get(AutoClone(this));
    if(sets != nullptr && sets->size() != 0) {
        auto event = createFilaRoutineInnerEvent(
            st(FilaRoutineInnerEvent)::Type::Notify,
            nullptr,
            AutoClone(this)
        );
        sets->get(0)->routine->postEvent(event);
    } else {
        mThreadCond->notify();
    }
}

void _FilaCondition::notifyAll() {
    AutoLock l(mWaitMutex);
    auto sets = mWaitRoutines->get(AutoClone(this));

    if(sets != nullptr) {
        auto iterator = sets->getIterator();
        auto event = createFilaRoutineInnerEvent(
            st(FilaRoutineInnerEvent)::Type::NotifyAll,
            nullptr,
            AutoClone(this)
        );

        while(iterator->hasValue()) {
            auto c = iterator->getValue();
            c->routine->postEvent(event);
            iterator->next();
        }
    }

    mThreadCond->notifyAll();
}

void _FilaCondition::doNotifyAll() {
    co_cond_broadcast(mCond);
}

void _FilaCondition::doNotify() {
    co_cond_signal(mCond);
}

_FilaCondition::~_FilaCondition() { 
    if(mCond != nullptr) {
        co_cond_free(mCond);
        mCond = nullptr;
    }
}

} // namespace obotcha