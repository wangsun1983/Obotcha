#ifndef __OBOTCHA_ASYNC_OUTPUT_CHANNEL_POOL_HPP__
#define __OBOTCHA_ASYNC_OUTPUT_CHANNEL_POOL_HPP__

#include <thread>
#include <mutex>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "EPollFileObserver.hpp"
#include "AsyncOutputChannel.hpp"
#include "FileDescriptor.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(AsyncOutputChannelPool) IMPLEMENTS(EPollFileObserverListener) {
public:
    static sp<_AsyncOutputChannelPool> getInstance();
    void addChannel(AsyncOutputChannel);
    void remove(AsyncOutputChannel);

private:
    _AsyncOutputChannelPool();
    
    static std::once_flag s_flag;
    static sp<_AsyncOutputChannelPool> mInstance;

    Mutex mMutex;
    HashMap<int,AsyncOutputChannel> mChannels;

    EPollFileObserver mObserver;
    int onEvent(int fd,uint32_t events);
};

}

#endif
