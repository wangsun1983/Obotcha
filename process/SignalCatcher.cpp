#include <signal.h>

#include "SignalCatcher.hpp"
#include "AutoLock.hpp"

namespace obotcha {

//SIGPIPE!!!

SignalCatcher _SignalCatcher::mInstance = nullptr;

void _handleSignal(int sig) {
    SignalCatcher catcher = st(SignalCatcher)::getInstance();
    AutoLock l(catcher->mMutex);
    ArrayList<SignalListener> list = catcher->mListenersMap->get(createInteger(sig));
    list->foreach([&sig](SignalListener l) {
        l->onSignal(sig);
        return 1;
    });
}

void _ignoreSignal(int) {
    //Do nothing,only ignore signal.
}

SignalCatcher _SignalCatcher::getInstance() {
    static std::once_flag s_flag;
    std::call_once(s_flag, [&]() {
        _SignalCatcher *p = new _SignalCatcher();
        p->mInstance.set_pointer(p);
    });

    return mInstance;
}

void _SignalCatcher::regist(int event,SignalListener l) {
    AutoLock ll(mMutex);
    ArrayList<SignalListener> list = mListenersMap->get(createInteger(event));
    if(list == nullptr) {
        list = createArrayList<SignalListener>();
        mListenersMap->put(createInteger(event),list);
        signal(event,_handleSignal); 
    }

    list->add(l);
}


void _SignalCatcher::ignore(int sig) {
    signal(sig ,_ignoreSignal);
    AutoLock ll(mMutex);
    mListenersMap->remove(createInteger(sig));
}

_SignalCatcher::_SignalCatcher() {
    mListenersMap = createHashMap<Integer,ArrayList<SignalListener>>();
    mMutex = createMutex();
}

}