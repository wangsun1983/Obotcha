#include "FilaCondition.hpp"
#include "FilaRoutineManager.hpp"

namespace obotcha {

_FilaCondition::_FilaCondition() { 
    mCond = co_cond_alloc(); 
}

void _FilaCondition::wait() {
    st(FilaRoutineManager)::getInstance()->addWaitCondition(AutoClone(this));
    co_cond_timedwait(mCond, -1); 
}

void _FilaCondition::wait(long mseconds) { 
    co_cond_timedwait(mCond, mseconds); 
}

void _FilaCondition::notify() {
    auto sets = st(FilaRoutineManager)::getInstance()->getWaitCroutine(AutoClone(this));
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
    
    //co_cond_signal(mCond); 
}

void _FilaCondition::notifyAll() {
    auto sets = st(FilaRoutineManager)::getInstance()->getWaitCroutine(AutoClone(this));
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
    //co_cond_broadcast(mCond); 
}

void _FilaCondition::doNotifyAll() {
    co_cond_broadcast(mCond);
}

void _FilaCondition::doNotify() {
    co_cond_signal(mCond);
}

_FilaCondition::~_FilaCondition() { 
    co_cond_free(mCond); 
}

} // namespace obotcha