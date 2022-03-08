#include "co_routine_inner.h"

#include "FilaCroutine.hpp"
#include "FilaCroutineManager.hpp"

#include <sys/types.h>

namespace obotcha {

_FilaCroutine::_FilaCroutine() {
    mDataMutex = createMutex();
    innerEvents = createArrayList<FilaCoutineInnerEvent>();
    mFilaments = createArrayList<Filament>();
}

void _FilaCroutine::start() { 
    st(Thread)::start(); 
}

void _FilaCroutine::postEvent(FilaCoutineInnerEvent event) {
    AutoLock l(mDataMutex);
    innerEvents->add(event);
}

void _FilaCroutine::submit(Filament f) {
    AutoLock l(mDataMutex);
    FilaCoutineInnerEvent event = createFilaCoutineInnerEvent();
    event->event = st(FilaCoutineInnerEvent)::NewTask;
    event->filament = f;
    innerEvents->add(event);
}

void _FilaCroutine::run() {
    co_init_curr_thread_env();
    co_enable_hook_sys();
    st(FilaCroutineManager)::getInstance()->addCroutine(AutoClone(this));
    co_eventloop(co_get_epoll_ct(), 0, 0,onIdle,this);
}

void _FilaCroutine::onInterrupt() {
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

void _FilaCroutine::onIdle(void * data) {
    _FilaCroutine *croutine =(_FilaCroutine *)data;
    AutoLock l(croutine->mDataMutex);
    if(croutine->innerEvents->size() != 0) {
        auto iterator = croutine->innerEvents->getIterator();
        while(iterator->hasValue()) {
            auto event = iterator->getValue();
            switch(event->event) {
                case st(FilaCoutineInnerEvent)::NewTask: {
                    Filament f = event->filament;
                    f->start();
                    croutine->mFilaments->add(f);
                    break;
                }
                
                case st(FilaCoutineInnerEvent)::Notify: {
                    //TODO
                    break;
                }

                case st(FilaCoutineInnerEvent)::NotifyAll: {
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
