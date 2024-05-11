#include "co_routine_inner.h"

#include "FilaRoutine.hpp"
#include "FilaCondition.hpp"
#include "Synchronized.hpp"
#include "ForEveryOne.hpp"
#include "Fila.hpp"
#include "Inspect.hpp"
#include "FilaExecutorResult.hpp"
#include "System.hpp"
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
    innerEvents->putLast(event);
}

_FilaRoutine::~_FilaRoutine() {
    join();
    if(mEnv != nullptr) {
        co_free_thread_env(mEnv);
        mEnv = nullptr;
    }
}

void _FilaRoutine::run() {
    co_init_curr_thread_env();
    co_enable_hook_sys();
    mEnv = co_get_curr_thread_env();

    co_eventloop(co_get_epoll_ct(), nullptr, nullptr,OnIdle,this);
}

void _FilaRoutine::shutdown() {
    mStatus = LocalStatus::Shutdown;

    auto event = FilaRoutineInnerEvent::New(
                    st(FilaRoutineInnerEvent)::Type::Shutdown,
                    nullptr,
                    nullptr);
    postEvent(event);
    interrupt();
}

int _FilaRoutine::OnIdle(void * data) {
    auto croutine =(_FilaRoutine *)data;
    while(true) {
        FilaRoutineInnerEvent event = nullptr;
        {
            AutoLock l(croutine->mFilaMutex);
            event = croutine->innerEvents->takeLast();
        }

        if(event == nullptr) {
            break;
        }

        
        switch(event->event) {
            case st(FilaRoutineInnerEvent)::Type::NewTask: {
                Filament f = event->filament;
                f->start();
                croutine->mFilaments->add(f);
            } break;
            
            case st(FilaRoutineInnerEvent)::Type::Notify: {
                FilaCondition cond = event->cond;
                cond->doNotify();
            } break;

            case st(FilaRoutineInnerEvent)::Type::NotifyAll: {
                FilaCondition cond = event->cond;
                cond->doNotifyAll();
            } break;

            case st(FilaRoutineInnerEvent)::Type::RemoveFilament: {
                croutine->removeFilament(event->filament);
            } break;

            case st(FilaRoutineInnerEvent)::Type::Shutdown: {
                croutine->mStatus = LocalStatus::Terminated;
            } break;
        }
        
        {
            AutoLock l(croutine->mFilaMutex);
            if(croutine->mStatus == LocalStatus::Terminated) {
                if(croutine->innerEvents->size() == 0) {
                    if(croutine->mFilaments->size() == 0) {
                        return -1;
                    } else {
                        croutine->mFilaments->get(0)->resume();
                        break;
                    }
                }
            }
        }
    }
    
    return 0;
}

int _FilaRoutine::awaitTermination(long timeout) {
    Inspect(mStatus == LocalStatus::Running,-1);
    return join(timeout);
}

void _FilaRoutine::removeFilament(Filament f) {
    AutoLock l(mFilaMutex);
    mFilaments->remove(f);
}

int _FilaRoutine::getFilamentSize() {
    AutoLock l(mFilaMutex);
    return mFilaments->size();
}

bool _FilaRoutine::isTerminated() {
    return mStatus != LocalStatus::Running;
}

} // namespace obotcha
