#include "co_routine_inner.h"

#include "FilaRoutine.hpp"
#include "FilaCondition.hpp"
#include "Synchronized.hpp"
#include "ForEveryOne.hpp"

#include <sys/types.h>

namespace obotcha {

//------- FilaRoutineInnerEvent -------
_FilaRoutineInnerEvent::_FilaRoutineInnerEvent(_FilaRoutineInnerEvent::Type e,
                                               Filament f,
                                               FilaCondition c):event(e),filament(f),cond(c) {
}

//------- FilaRoutine -------
void _FilaRoutine::postEvent(FilaRoutineInnerEvent event) {
    AutoLock l(mFilaMutex);
    innerEvents->add(event);
}

_FilaRoutine::~_FilaRoutine() {
    join();
    co_free_curr_thread_env();
}

void _FilaRoutine::onComplete() {
    //st(FilaRoutineManager)::getInstance()->removeRoutine();
}

void _FilaRoutine::run() {
    co_init_curr_thread_env();
    co_enable_hook_sys();
    co_eventloop(co_get_epoll_ct(), nullptr, nullptr,OnIdle,this);
}

// void _FilaRoutine::onInterrupt() {
//     {
//         printf("onInterrupt \n");
//         AutoLock l(mFilaMutex);
//         ForEveryOne(fila,mFilaments) {
//             fila->onInterrupt();
//         }
//     }

//     //TOOD
//     stCoEpoll_t *epoll = co_get_epoll_ct();
//     if (epoll != nullptr) {
//         FreeEpoll(epoll);
//     }
// }

void _FilaRoutine::stop() {
    auto event = createFilaRoutineInnerEvent(
                    st(FilaRoutineInnerEvent)::Type::Stop,
                    nullptr,
                    nullptr);
    postEvent(event);
}

int _FilaRoutine::OnIdle(void * data) {
    auto croutine =(_FilaRoutine *)data;
    AutoLock l(croutine->mFilaMutex);
    ForEveryOne(event,croutine->innerEvents) {
        switch(event->event) {
            case st(FilaRoutineInnerEvent)::Type::NewTask: {
                Filament f = event->filament;
                f->start();
                croutine->mFilaments->add(f);
                break;
            }
            
            case st(FilaRoutineInnerEvent)::Type::Notify: {
                FilaCondition cond = event->cond;
                cond->doNotify();
                break;
            }

            case st(FilaRoutineInnerEvent)::Type::NotifyAll: {
                FilaCondition cond = event->cond;
                cond->doNotifyAll();
                break;
            }

            case st(FilaRoutineInnerEvent)::Type::RemoveFilament: {
                croutine->removeFilament(event->filament);
            }
            break;

            case st(FilaRoutineInnerEvent)::Type::Stop: {
                ForEveryOne(fila,croutine->mFilaments) {
                    fila->onInterrupt();
                    fila->markAsReleased();
                }
                co_free_curr_thread_env();
                croutine->mFilaments->clear();
                return -1;
            }
        }
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
