#include "FilaCondition.hpp"
#include "FilaRoutineManager.hpp"

namespace obotcha {

_FilaCondition::_FilaCondition() { 
    mCond = co_cond_alloc();
    mOriCond = createCondition();
}

void _FilaCondition::wait(FilaMutex m) {
    wait(m,-1);
}

void _FilaCondition::wait(FilaMutex m,long mseconds) {
    auto coa = GetCurrThreadCo();
    if(coa == nullptr) {
        AutoLock l(m->mMutex);
        mOriCond->wait(m->mMutex);
    } else {
        st(FilaRoutineManager)::getInstance()->addWaitCondition(AutoClone(this));
        m->unlock();
        co_cond_timedwait(mCond, mseconds); 
        m->lock();
        st(FilaRoutineManager)::getInstance()->removeWaitCondition(AutoClone(this));
    }
}

void _FilaCondition::notify() {
    auto sets = st(FilaRoutineManager)::getInstance()->getWaitRoutine(AutoClone(this));
    if(sets != nullptr) {
        auto iterator = sets->getIterator();
        FilaRoutineInnerEvent event = createFilaRoutineInnerEvent();
        event->event = st(FilaRoutineInnerEvent)::Notify;
        event->cond = AutoClone(this);

        while(iterator->hasValue()) {
            FilaRoutine c = iterator->getValue();
            c->postEvent(event);
            break;
        }
    }

    mOriCond->notify();
}

void _FilaCondition::notifyAll() {
    auto sets = st(FilaRoutineManager)::getInstance()->getWaitRoutine(AutoClone(this));
    if(sets != nullptr) {
        auto iterator = sets->getIterator();
        FilaRoutineInnerEvent event = createFilaRoutineInnerEvent();
        event->event = st(FilaRoutineInnerEvent)::NotifyAll;
        event->cond = AutoClone(this);
        while(iterator->hasValue()) {
            int size = sets->size();
            auto c = iterator->getValue();
            
            c->postEvent(event);
            iterator->next();
        }
    }

    mOriCond->notifyAll();
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