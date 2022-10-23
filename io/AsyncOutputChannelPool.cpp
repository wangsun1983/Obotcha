#include "AsyncOutputChannelPool.hpp"
#include "AsyncOutputChannel.hpp"
#include "ForEveryOne.hpp"
#include "Error.hpp"

namespace obotcha {

AsyncOutputChannel _AsyncOutputChannelPool::createChannel(FileDescriptor descriptor,AsyncOutputWriter stream) {
    auto *_channel = new _AsyncOutputChannel(descriptor,stream,AutoClone(this));
    auto channel = AutoClone(_channel);

    addChannel(channel);
    return channel;
}

void _AsyncOutputChannelPool::addChannel(AsyncOutputChannel channel) {
    //AutoLock l(mMutex);
    int fd = channel->getFileDescriptor()->getFd();

    mChannels->put(fd, channel);
    mObserver->addObserver(fd,
                           st(EPollFileObserver)::EpollOut
                           |st(EPollFileObserver)::EpollHup
                           |st(EPollFileObserver)::EpollRdHup,
                           AutoClone(this));
}

void _AsyncOutputChannelPool::remove(AsyncOutputChannel c) {
    if(c == nullptr) {
        return;
    }

    int fd = c->getFileDescriptor()->getFd();

    auto channel = mChannels->get(fd);
    if(channel == c) {
        mChannels->remove(fd);
        mObserver->removeObserver(fd);
        //channel->mPool = nullptr;
        //channel->mWriter = nullptr;
    }
}

_AsyncOutputChannelPool::_AsyncOutputChannelPool() {
    mObserver = createEPollFileObserver();
    mChannels = createConcurrentHashMap<int, AsyncOutputChannel>();
}

int _AsyncOutputChannelPool::onEvent(int fd, uint32_t events) {
    auto channel = mChannels->remove(fd);
    mObserver->removeObserver(fd);
    if (channel != nullptr) {
        if((events & (st(EPollFileObserver)::EpollHup|st(EPollFileObserver)::EpollRdHup)) != 0) {
            channel->close();
            //channel->mPool = nullptr;
            //channel->mWriter = nullptr;
        }else if ((events & st(EPollFileObserver)::EpollOut) != 0) {
            channel->notifyWrite();
        }
    }
    return st(EPollFileObserver)::OnEventOK;
}

void _AsyncOutputChannelPool::close() {
    mObserver->close();
    //remove all channel
    ForEveryOne(pair,mChannels) {
        auto channel = pair->getValue();
        channel->close();
        //channel->mPool = nullptr;
        //channel->mWriter = nullptr;
    }

    mChannels->clear();
}

_AsyncOutputChannelPool::~_AsyncOutputChannelPool() {
    close();
}

void _AsyncOutputChannelPool::dump() {
    mObserver->dump();
}

} // namespace obotcha
