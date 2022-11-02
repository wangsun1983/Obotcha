#include "FilaCondition.hpp"
#include "FilaRoutine.hpp"
#include "Log.hpp"
#include "IllegalStateException.hpp"

namespace obotcha {

FilaMutex _FilaCondition::mWaitMutex = createFilaMutex();
HashMap<FilaCondition,HashSet<FilaRoutine>>_FilaCondition::mWaitConditions
    = createHashMap<FilaCondition,HashSet<FilaRoutine>>();

_FilaCondition::_FilaCondition() { 
    mCond = co_cond_alloc();
    mThreadCond = createCondition();
}

void _FilaCondition::wait(FilaMutex m) {
    wait(m,-1);
}

void _FilaCondition::wait(FilaMutex m,long mseconds) {
    if(!m->isOwner()) {
        Trigger(IllegalStateException,
                "Wait without getting the ownership of mutex");
    }

    auto coa = GetCurrThreadCo();
    if(coa == nullptr) {
        mThreadCond->wait(m->mMutex);
    } else {
        addWaitRoutine();
        m->unlock();
        co_cond_timedwait(mCond, mseconds); 
        m->lock();
        removeWaitRoutine();
    }
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
    //auto sets = st(FilaRoutineManager)::getInstance()->getWaitRoutine(AutoClone(this));
    AutoLock l(mWaitMutex);
    auto sets = mWaitConditions->get(AutoClone(this));
    if(sets != nullptr && sets->size() != 0) {
        FilaRoutineInnerEvent event = createFilaRoutineInnerEvent();
        event->event = st(FilaRoutineInnerEvent)::Notify;
        event->cond = AutoClone(this);
        sets->get(0)->postEvent(event);
    }

    mThreadCond->notify();
}

void _FilaCondition::notifyAll() {
    AutoLock l(mWaitMutex);
    auto sets = mWaitConditions->get(AutoClone(this));

    if(sets != nullptr) {
        auto iterator = sets->getIterator();
        FilaRoutineInnerEvent event = createFilaRoutineInnerEvent();
        event->event = st(FilaRoutineInnerEvent)::NotifyAll;
        event->cond = AutoClone(this);
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