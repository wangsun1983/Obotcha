#include <mutex>
#include <signal.h>

#include "SignalCatcher.hpp"
#include "AutoLock.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {


_SignalListenerLambda::_SignalListenerLambda(_SignalLambda s):func(s) {
}

void _SignalListenerLambda::onSignal(int sig) {
    func(sig);
}

//SIGPIPE!!!
SignalCatcher _SignalCatcher::mInstance = nullptr;

void _handleSignal(int sig) {
    SignalCatcher catcher = st(SignalCatcher)::getInstance();
    AutoLock l(catcher->mMutex);
    ArrayList<SignalListener> list = catcher->mListenersMap->get(Integer::New(sig));
    ForEveryOne(ll,list) {
        ll->onSignal(sig);
    }
}

void _ignoreSignal(int) {
    //Do nothing,only ignore signal.
}

SignalCatcher _SignalCatcher::getInstance() {
    static std::once_flag s_flag;
    std::call_once(s_flag, []() {
        mInstance = AutoClone(new _SignalCatcher());
    });

    return mInstance;
}

void _SignalCatcher::regist(int event,SignalListener l) {
    AutoLock ll(mMutex);
    ArrayList<SignalListener> list = mListenersMap->get(Integer::New(event));
    if(list == nullptr) {
        list = ArrayList<SignalListener>::New();
        mListenersMap->put(Integer::New(event),list);
        signal(event,_handleSignal); 
    }

    list->add(l);
}

void _SignalCatcher::regist(int event,_SignalLambda f) {
    SignalListener l = SignalListenerLambda::New(f);
    regist(event,l);
}

void _SignalCatcher::ignore(int sig) {
    signal(sig ,_ignoreSignal);
    AutoLock ll(mMutex);
    mListenersMap->remove(Integer::New(sig));
}

_SignalCatcher::_SignalCatcher() {
    mListenersMap = HashMap<Integer,ArrayList<SignalListener>>::New();
    mMutex = Mutex::New();
}

}
