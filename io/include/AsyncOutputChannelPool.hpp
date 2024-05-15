#ifndef __OBOTCHA_ASYNC_OUTPUT_CHANNEL_POOL_HPP__
#define __OBOTCHA_ASYNC_OUTPUT_CHANNEL_POOL_HPP__

#include "Object.hpp"
#include "AsyncOutputChannel.hpp"
#include "EPollObserver.hpp"
#include "FileDescriptor.hpp"
#include "HashMap.hpp"
#include "Mutex.hpp"
#include "OutputWriter.hpp"

namespace obotcha {

DECLARE_CLASS(AsyncOutputChannelPool) IMPLEMENTS(EPollListener) {
public:
    _AsyncOutputChannelPool();
    ~_AsyncOutputChannelPool() override;
    static AsyncOutputChannel CreateChannel(FileDescriptor fd,OutputWriter stream);

    void addChannel(AsyncOutputChannel,bool ShouldRemovePreviousPool = true);
    void remove(AsyncOutputChannel);
    void close(bool closeAllChannels = false);
    bool isEmpty();
    size_t size();

private:
    Mutex mMutex;
    HashMap<int, AsyncOutputChannel> mChannels;
    EPollObserver mObserver;
    st(IO)::Epoll::Result onEvent(int fd, uint32_t events) override;
};

} // namespace obotcha

#endif
