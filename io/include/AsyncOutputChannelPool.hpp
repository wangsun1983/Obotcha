#ifndef __OBOTCHA_ASYNC_OUTPUT_CHANNEL_POOL_HPP__
#define __OBOTCHA_ASYNC_OUTPUT_CHANNEL_POOL_HPP__

#include "Object.hpp"
#include "AsyncOutputChannel.hpp"
#include "EPollFileObserver.hpp"
#include "FileDescriptor.hpp"
#include "HashMap.hpp"
#include "Mutex.hpp"
#include "OutputWriter.hpp"

namespace obotcha {

DECLARE_CLASS(AsyncOutputChannelPool) IMPLEMENTS(EPollFileObserverListener) {
  public:
    _AsyncOutputChannelPool();
    ~_AsyncOutputChannelPool();
    AsyncOutputChannel createChannel(FileDescriptor fd,OutputWriter stream);

    void addChannel(AsyncOutputChannel);
    void remove(AsyncOutputChannel);
    void close();
    bool isEmpty();
    int size();

  private:
    Mutex mMutex;
    HashMap<int, AsyncOutputChannel> mChannels;
    EPollFileObserver mObserver;
    int onEvent(int fd, uint32_t events);
};

} // namespace obotcha

#endif
