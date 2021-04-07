#ifndef __OBOTCHA_SYSTEM_SIGNAL_HANDLER_HPP__
#define __OBOTCHA_SYSTEM_SIGNAL_HANDLER_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <mqueue.h>
#include <fstream>


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
    static sp<_SystemSignalHandler> getInstance();
    static void handle(int sig);

    void listen(int,sp<_SystemSignalListener>);
private:
    static Mutex mMutex;
    static sp<_SystemSignalHandler> mInstance;
    HashMap<int,ArrayList<SystemSignalListener>> mListenersMap;
    _SystemSignalHandler();
   
};

}
#endif
