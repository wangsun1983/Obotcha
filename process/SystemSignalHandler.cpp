#include <signal.h>

#include "SystemSignalHandler.hpp"
#include "AutoLock.hpp"

namespace obotcha {

Mutex _SystemSignalHandler::mMutex = createMutex();
sp<_SystemSignalHandler> _SystemSignalHandler::mInstance = nullptr;

sp<_SystemSignalHandler> _SystemSignalHandler::getInstance() {
    AutoLock l(mMutex);
    if(mInstance != nullptr) {
        mInstance.set_pointer(new _SystemSignalHandler());
    }

    return mInstance;
}

void _SystemSignalHandler::listen(int event,SystemSignalListener l) {
    AutoLock ll(mMutex);
    ArrayList<SystemSignalListener> list = mListenersMap->get(event);
    if(list == nullptr) {
        list = createArrayList<SystemSignalListener>();
        mListenersMap->put(event,list);
        signal(event , mInstance->handle); 
    }

    list->add(l);
}

_SystemSignalHandler::_SystemSignalHandler() {
    mListenersMap = createHashMap<int,ArrayList<SystemSignalListener>>();
}

void _SystemSignalHandler::handle(int sig) {
    AutoLock l(mMutex);
    ArrayList<SystemSignalListener> list = mInstance->mListenersMap->get(sig);
    list->foreach([&sig](SystemSignalListener l) {
        l->onSignal(sig);
        return 1;
    });
}

}
