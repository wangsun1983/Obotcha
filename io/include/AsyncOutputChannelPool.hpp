#ifndef __OBOTCHA_ASYNC_OUTPUT_CHANNEL_POOL_HPP__
#define __OBOTCHA_ASYNC_OUTPUT_CHANNEL_POOL_HPP__

#include <mutex>
#include <thread>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "AsyncOutputChannel.hpp"
#include "EPollFileObserver.hpp"
#include "FileDescriptor.hpp"

namespace obotcha {

DECLARE_CLASS(AsyncOutputChannelPool) IMPLEMENTS(EPollFileObserverListener) {
  public:
    _AsyncOutputChannelPool();
    void addChannel(AsyncOutputChannel);
    void remove(AsyncOutputChannel);

  private:
    Mutex mMutex;
    HashMap<int, AsyncOutputChannel> mChannels;

    EPollFileObserver mObserver;
    int onEvent(int fd, uint32_t events);
};

} // namespace obotcha

#endif
