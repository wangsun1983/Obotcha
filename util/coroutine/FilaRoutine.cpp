#include "co_routine_inner.h"

#include "FilaRoutine.hpp"
#include "FilaCondition.hpp"
#include "Synchronized.hpp"
#include "ForEveryOne.hpp"
#include "Fila.hpp"

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
    // if(isShutdown == 1) {
    //     return;
    // }
    innerEvents->putLast(event);
}

_FilaRoutine::~_FilaRoutine() {
    
    //shutdown();
    // ForEveryOne(filament,mFilaments) {
    //     auto future = filament->getFuture();
    //     if(future != nullptr) {
    //         future->wait();
    //     }
    // }
    join();
    // co_free_curr_thread_env();
}

void _FilaRoutine::onComplete() {
    //st(FilaRoutineManager)::getInstance()->removeRoutine();
}

void _FilaRoutine::run() {
    co_init_curr_thread_env();
    co_enable_hook_sys();
    mEnv = co_get_curr_thread_env();

    co_eventloop(co_get_epoll_ct(), nullptr, nullptr,OnIdle,this);
}

void _FilaRoutine::shutdown() {
    mStatus = LocalStatus::Shutdown;

    auto event = createFilaRoutineInnerEvent(
                    st(FilaRoutineInnerEvent)::Type::Shutdown,
                    nullptr,
                    nullptr);
    postEvent(event);
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
            if(croutine->innerEvents->size() == 0 
                && croutine->mFilaments->size() == 0 
                && croutine->mStatus == LocalStatus::Terminated) {
                return -1;
            }
        }
    }
    
    return 0;
}

int _FilaRoutine::awaitTermination(long timeout) {
    // while(true) {
    //     {
    //         printf("awaitTermination filament size is %d,innerEvents size is %d \n",mFilaments->size(),innerEvents->size());
    //         AutoLock l1(mFilaMutex);
    //         if(isShutdown == 1 && mFilaments->size() == 0 && innerEvents->size() == 0) {
    //             break;
    //         }
    //     }
    //     usleep(1000*100);
    // }
    // if(mStatus == LocalStatus::Running) {
    //     return -1;
    // }
    printf("awaitTermination trace2 \n");
    // auto event = createFilaRoutineInnerEvent(
    //                 st(FilaRoutineInnerEvent)::Type::Release,
    //                 nullptr,
    //                 nullptr);
    // innerEvents->add(event);

    printf("awaitTermination trace3 \n");
    join();

    if(mEnv != nullptr) {
        co_free_thread_env(mEnv);
        mEnv = nullptr;
    }
    printf("awaitTermination trace4 \n");
    return 0;
}

void _FilaRoutine::removeFilament(Filament f) {
    AutoLock l(mFilaMutex);
    mFilaments->remove(f);
}

int _FilaRoutine::getFilamentSize() {
    AutoLock l(mFilaMutex);
    return mFilaments->size();
}

} // namespace obotcha
