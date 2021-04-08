#ifndef __OBOTCHA_ASYNC_OUTPUT_CHANNEL_MANAGER_HPP__
#define __OBOTCHA_ASYNC_OUTPUT_CHANNEL_MANAGER_HPP__


#include "Object.hpp"
#include "StrongPointer.hpp"

#include "EPollFileObserver.hpp"
#include "AsyncOutputChannel.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(AsyncOutputChannelManager) IMPLEMENTS(EPollFileObserverListener) {
public:
    static sp<_AsyncOutputChannelManager> getInstance();
    void addChannel(AsyncOutputChannel);
    void remove(AsyncOutputChannel);

private:
    _AsyncOutputChannelManager();
    static sp<_AsyncOutputChannelManager> mInstance;

    EPollFileObserver observer;
    int onEvent(int fd,uint32_t events,ByteArray);
};

}

#endif
