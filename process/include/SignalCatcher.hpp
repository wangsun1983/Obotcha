#ifndef __OBOTCHA_SIGNAL_CATCHER_HPP__
#define __OBOTCHA_SIGNAL_CATCHER_HPP__

#include "Object.hpp"
#include "HashMap.hpp"
#include "Mutex.hpp"

namespace obotcha {

DECLARE_CLASS(SignalListener) {
public:
    virtual void onSignal(int) = 0;
};

using _SignalLambda = std::function<void(int)>;
DECLARE_CLASS(SignalListenerLambda) IMPLEMENTS(SignalListener) {
public:
    explicit _SignalListenerLambda(_SignalLambda);
    void onSignal(int sig);

private:
    _SignalLambda func;
};

DECLARE_CLASS(SignalCatcher) {
public:
    friend void _handleSignal(int);

    static SignalCatcher getInstance();
    void regist(int,SignalListener);
    void regist(int,_SignalLambda);

    void unregist(int,SignalListener);
    void ignore(int);

private:
    static SignalCatcher mInstance;
    Mutex mMutex;
    HashMap<Integer,ArrayList<SignalListener>> mListenersMap;
    _SignalCatcher();
};

}
#endif
