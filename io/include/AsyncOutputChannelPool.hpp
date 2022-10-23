#ifndef __OBOTCHA_ASYNC_OUTPUT_CHANNEL_POOL_HPP__
#define __OBOTCHA_ASYNC_OUTPUT_CHANNEL_POOL_HPP__

#include <mutex>
#include <thread>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "AsyncOutputChannel.hpp"
#include "EPollFileObserver.hpp"
#include "FileDescriptor.hpp"
#include "ConcurrentHashMap.hpp"

namespace obotcha {

DECLARE_CLASS(AsyncOutputChannelPool) IMPLEMENTS(EPollFileObserverListener) {
  public:
    _AsyncOutputChannelPool();
    ~_AsyncOutputChannelPool();
    AsyncOutputChannel createChannel(FileDescriptor fd,AsyncOutputWriter stream);
    
    void addChannel(AsyncOutputChannel);
    void remove(AsyncOutputChannel);
    void close();
    void dump();

  private:
    ConcurrentHashMap<int, AsyncOutputChannel> mChannels;

    EPollFileObserver mObserver;
    int onEvent(int fd, uint32_t events);
};

} // namespace obotcha

#endif
