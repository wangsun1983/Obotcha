#ifndef __OBOTCHA_SIGNAL_CATCHER_HPP__
#define __OBOTCHA_SIGNAL_CATCHER_HPP__

#include <thread>
#include <mutex>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ByteArray.hpp"
#include "String.hpp"
#include "HashMap.hpp"
#include "Mutex.hpp"

namespace obotcha {

DECLARE_CLASS(SignalListener) {
public:
    virtual void onSignal(int) = 0;
};

DECLARE_CLASS(SignalCatcher) {
public:
    friend void _handleSignal(int);

    static SignalCatcher getInstance();
    void regist(int,SignalListener);
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
