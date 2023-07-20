#include "co_routine_inner.h"

#include "FilaRoutine.hpp"
#include "FilaCondition.hpp"
#include "Synchronized.hpp"
#include "ForEveryOne.hpp"

#include <sys/types.h>

namespace obotcha {

//------- FilaRoutineInnerEvent -------
_FilaRoutineInnerEvent::_FilaRoutineInnerEvent(int e,
                                               Filament f,
                                               FilaCondition c) {
    this->event = e;
    this->filament = f;
    this->cond = c;
}

//------- FilaRoutine -------
_FilaRoutine::_FilaRoutine() {
    mDataMutex = createMutex();
    innerEvents = createArrayList<FilaRoutineInnerEvent>();

    mFilaMutex = createFilaMutex();
    mFilaments = createArrayList<Filament>();
    //isStop = false;
}

void _FilaRoutine::start() { 
    st(Thread)::start(); 
}

void _FilaRoutine::postEvent(FilaRoutineInnerEvent event) {
    AutoLock l(mFilaMutex);
    innerEvents->add(event);
}

_FilaRoutine::~_FilaRoutine() {
    co_free_curr_thread_env();
    join();
}

void _FilaRoutine::onComplete() {
    //st(FilaRoutineManager)::getInstance()->removeRoutine();
}

void _FilaRoutine::run() {
    co_init_curr_thread_env();
    co_enable_hook_sys();
    co_eventloop(co_get_epoll_ct(), nullptr, nullptr,onIdle,this);
}

void _FilaRoutine::onInterrupt() {
    {
        AutoLock l(mFilaMutex);
        ForEveryOne(fila,mFilaments) {
            fila->onInterrupt();
        }
    }

    //TOOD
    stCoEpoll_t *epoll = co_get_epoll_ct();
    if (epoll != nullptr) {
        FreeEpoll(epoll);
    }
}

void _FilaRoutine::stop() {
    auto event = createFilaRoutineInnerEvent(
                    st(FilaRoutineInnerEvent)::Stop,
                    nullptr,
                    nullptr);
    postEvent(event);
}

int _FilaRoutine::onIdle(void * data) {
    _FilaRoutine *croutine =(_FilaRoutine *)data;
    AutoLock l(croutine->mFilaMutex);
    auto iterator = croutine->innerEvents->getIterator();
    while(iterator->hasValue()) {
        auto event = iterator->getValue();
        switch(event->event) {
            case st(FilaRoutineInnerEvent)::NewTask: {
                Filament f = event->filament;
                f->start();
                croutine->mFilaments->add(f);
                break;
            }
            
            case st(FilaRoutineInnerEvent)::Notify: {
                FilaCondition cond = event->cond;
                cond->doNotify();
                break;
            }

            case st(FilaRoutineInnerEvent)::NotifyAll: {
                FilaCondition cond = event->cond;
                cond->doNotifyAll();
                break;
            }

            case st(FilaRoutineInnerEvent)::RemoveFilament: {
                croutine->removeFilament(event->filament);
            }
            break;

            case st(FilaRoutineInnerEvent)::Stop: {
                ArrayListIterator<Filament> iterator = croutine->mFilaments->getIterator();
                while (iterator->hasValue()) {
                    Filament fila = iterator->getValue();
                    fila->markAsReleased();
                    iterator->next();
                }
                co_free_curr_thread_env();
                croutine->mFilaments->clear();
                return -1;
            }
        }
        iterator->next();
    }
    croutine->innerEvents->clear();
    return 0;
}

void _FilaRoutine::removeFilament(Filament f) {
    AutoLock l(mDataMutex);
    mFilaments->remove(f);
}

int _FilaRoutine::getFilamentSize() {
    AutoLock l(mDataMutex);
    return mFilaments->size();
}

} // namespace obotcha
