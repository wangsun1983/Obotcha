#include "FilaCondition.hpp"
#include "FilaRoutine.hpp"
#include "IllegalStateException.hpp"
#include "TimeWatcher.hpp"
#include "Log.hpp"

namespace obotcha {

FilaMutex _FilaCondition::mWaitMutex = createFilaMutex();
HashMap<FilaCondition,HashSet<FilaRoutine>>_FilaCondition::mWaitConditions
    = createHashMap<FilaCondition,HashSet<FilaRoutine>>();

_FilaCondition::_FilaCondition() { 
    mCond = co_cond_alloc();
    mThreadCond = createCondition();
}

int _FilaCondition::wait(FilaMutex m,long mseconds) {
    if(!m->isOwner()) {
        Trigger(IllegalStateException,
                "Wait without getting the ownership of mutex");
    }
    auto coa = GetCurrThreadCo();
    if(coa == nullptr) {
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
                return -ETIMEDOUT;
            }
        }
        m->lock();
        removeWaitRoutine();
    }
    return 0;
}

void _FilaCondition::addWaitRoutine() {
    AutoLock l(mWaitMutex);
    auto croutine = Cast<FilaRoutine>(st(Thread)::current());
    if(croutine == nullptr) {
      LOG(ERROR)<<"addWaitCondition,croutine is null";
      return;
    }

    auto waitSets = mWaitConditions->get(AutoClone(this));
    if(waitSets == nullptr) {
      waitSets = createHashSet<FilaRoutine>();
      mWaitConditions->put(AutoClone(this),waitSets);
    }
    waitSets->add(croutine);
}

void _FilaCondition::removeWaitRoutine() {
    auto croutine = Cast<FilaRoutine>(st(Thread)::current());

    AutoLock l(mWaitMutex);
    auto waitSets = mWaitConditions->get(AutoClone(this));
    waitSets->remove(croutine);
}

void _FilaCondition::notify() {
    AutoLock l(mWaitMutex);
    auto sets = mWaitConditions->get(AutoClone(this));
    if(sets != nullptr && sets->size() != 0) {
        auto event = createFilaRoutineInnerEvent(
            st(FilaRoutineInnerEvent)::Notify,
            nullptr,
            AutoClone(this)
        );
        sets->get(0)->postEvent(event);
    } else {
        mThreadCond->notify();
    }
}

void _FilaCondition::notifyAll() {
    AutoLock l(mWaitMutex);
    auto sets = mWaitConditions->get(AutoClone(this));

    if(sets != nullptr) {
        auto iterator = sets->getIterator();
        auto event = createFilaRoutineInnerEvent(
            st(FilaRoutineInnerEvent)::NotifyAll,
            nullptr,
            AutoClone(this)
        );

        while(iterator->hasValue()) {
            auto c = iterator->getValue();
            c->postEvent(event);
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