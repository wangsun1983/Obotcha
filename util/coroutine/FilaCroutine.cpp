#include "co_routine_inner.h"

#include "FilaCroutine.hpp"
#include <sys/types.h>

namespace obotcha {

_FilaCroutine::_FilaCroutine(ArrayList<Filament> filaments) {
    this->mFilaments = filaments;
}

void _FilaCroutine::start() {
    st(Thread)::start();
}

void _FilaCroutine::run() {
    co_init_curr_thread_env();
    co_enable_hook_sys();
    ListIterator<Filament> iterator = mFilaments->getIterator();
    while(iterator->hasValue()) {
        Filament fila = iterator->getValue();
        fila->start();
        iterator->next();
    }
    co_eventloop( co_get_epoll_ct(),0,0 );
}

void _FilaCroutine::onInterrupt() {
    ListIterator<Filament> iterator = mFilaments->getIterator();
    while(iterator->hasValue()) {
        Filament fila = iterator->getValue();
        if(fila->mRun != nullptr) {
            fila->mRun->onInterrupt();
        }
    }

    stCoEpoll_t * epoll = co_get_epoll_ct();
    if(epoll != nullptr) {
        FreeEpoll(epoll);
    }
}

}
