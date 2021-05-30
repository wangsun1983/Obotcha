#include <signal.h>

#include "SystemSignalHandler.hpp"
#include "AutoLock.hpp"

namespace obotcha {

//SIGPIPE!!!

void _handle(int sig) {
    SystemSignalHandler _handle = st(SystemSignalHandler)::getInstance();
    AutoLock l(_handle->mMutex);
    ArrayList<SystemSignalListener> list = _handle->mListenersMap->get(sig);
    list->foreach([&sig](SystemSignalListener l) {
        l->onSignal(sig);
        return 1;
    });
}

void _ignore(int) {

}

sp<_SystemSignalHandler> _SystemSignalHandler::mInstance = nullptr;
std::once_flag _SystemSignalHandler::s_flag;

sp<_SystemSignalHandler> _SystemSignalHandler::getInstance() {
    std::call_once(s_flag, [&]() {
        _SystemSignalHandler *p = new _SystemSignalHandler();
        p->mInstance.set_pointer(p);
    });

    return mInstance;
}

void _SystemSignalHandler::listen(int event,SystemSignalListener l) {
    AutoLock ll(mMutex);
    ArrayList<SystemSignalListener> list = mListenersMap->get(event);
    if(list == nullptr) {
        list = createArrayList<SystemSignalListener>();
        mListenersMap->put(event,list);
        signal(event , _handle); 
    }

    list->add(l);
}


void _SystemSignalHandler::ignore(int sig) {
    signal(sig , _ignore);
    AutoLock ll(mMutex);
    mListenersMap->remove(sig);
}

_SystemSignalHandler::_SystemSignalHandler() {
    mListenersMap = createHashMap<int,ArrayList<SystemSignalListener>>();
    mMutex = createMutex();
}

}
