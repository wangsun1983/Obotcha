#ifndef __OBOTCHA_SYSTEM_SIGNAL_HANDLER_HPP__
#define __OBOTCHA_SYSTEM_SIGNAL_HANDLER_HPP__

#include <thread>
#include <mutex>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ByteArray.hpp"
#include "String.hpp"
#include "HashMap.hpp"
#include "Mutex.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(SystemSignalListener) {
public:
    virtual void onSignal(int) = 0;
};

DECLARE_SIMPLE_CLASS(SystemSignalHandler) {
public:
    friend void _handle(int);
    static sp<_SystemSignalHandler> getInstance();
    void listen(int,sp<_SystemSignalListener>);
    void ignore(int);

private:
    static std::once_flag s_flag;
    static sp<_SystemSignalHandler> mInstance;
    Mutex mMutex;
    HashMap<int,ArrayList<SystemSignalListener>> mListenersMap;
    _SystemSignalHandler();
};

}
#endif
