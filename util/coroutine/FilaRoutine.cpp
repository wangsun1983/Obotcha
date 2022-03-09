#include "co_routine_inner.h"

#include "FilaRoutine.hpp"
#include "FilaRoutineManager.hpp"

#include <sys/types.h>

namespace obotcha {

void filaSleep(long t) {
    poll(0,0,t);
}

_FilaRoutine::_FilaRoutine() {
    mDataMutex = createMutex();
    innerEvents = createArrayList<FilaRoutineInnerEvent>();
    mFilaments = createArrayList<Filament>();
}

void _FilaRoutine::start() { 
    st(Thread)::start(); 
}

void _FilaRoutine::postEvent(FilaRoutineInnerEvent event) {
    AutoLock l(mDataMutex);
    innerEvents->add(event);
}

void _FilaRoutine::run() {
    co_init_curr_thread_env();
    co_enable_hook_sys();
    st(FilaRoutineManager)::getInstance()->addCroutine(AutoClone(this));
    co_eventloop(co_get_epoll_ct(), 0, 0,onIdle,this);
}

void _FilaRoutine::onInterrupt() {
    {
        AutoLock l(mDataMutex);
        ListIterator<Filament> iterator = mFilaments->getIterator();
        while (iterator->hasValue()) {
            Filament fila = iterator->getValue();
            fila->onInterrupt();
        }
    }

    stCoEpoll_t *epoll = co_get_epoll_ct();
    if (epoll != nullptr) {
        FreeEpoll(epoll);
    }
}

void _FilaRoutine::onIdle(void * data) {
    _FilaRoutine *croutine =(_FilaRoutine *)data;
    AutoLock l(croutine->mDataMutex);
    if(croutine->innerEvents->size() != 0) {
        auto iterator = croutine->innerEvents->getIterator();
        while(iterator->hasValue()) {
            auto event = iterator->getValue();
            switch(event->event) {
                case st(FilaRoutineInnerEvent)::NewTask: {
                    Filament f = event->filament;
                    f->start(event->future);
                    croutine->mFilaments->add(f);
                    break;
                }
                
                case st(FilaRoutineInnerEvent)::Notify: {
                    //TODO
                    break;
                }

                case st(FilaRoutineInnerEvent)::NotifyAll: {
                    FilaCondition cond = event->cond;
                    cond->doNotifyAll();
                    break;
                }
            }
            
            iterator->next();
        }
        croutine->innerEvents->clear();
    }
}

} // namespace obotcha
