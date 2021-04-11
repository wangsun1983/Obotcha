#ifndef __OBOTCHA_ASYNC_OUTPUT_CHANNEL_POOL_HPP__
#define __OBOTCHA_ASYNC_OUTPUT_CHANNEL_POOL_HPP__


#include "Object.hpp"
#include "StrongPointer.hpp"

#include "EPollFileObserver.hpp"
#include "AsyncOutputChannel.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(AsyncOutputChannelPool) IMPLEMENTS(EPollFileObserverListener) {
public:
    static sp<_AsyncOutputChannelPool> getInstance();
    void addChannel(AsyncOutputChannel);
    void remove(AsyncOutputChannel);

private:
    _AsyncOutputChannelPool();
    static Mutex mMutex;
    static sp<_AsyncOutputChannelPool> mInstance;

    HashMap<int,AsyncOutputChannel> mChannels;

    EPollFileObserver mObserver;
    int onEvent(int fd,uint32_t events,ByteArray);
};

}

#endif
