#include "AsyncOutputChannelPool.hpp"
#include "AsyncOutputChannel.hpp"
#include "ForEveryOne.hpp"
#include "Log.hpp"
#include "Synchronized.hpp"
#include "Inspect.hpp"

namespace obotcha {

AsyncOutputChannel _AsyncOutputChannelPool::createChannel(FileDescriptor descriptor,OutputWriter stream) {
    auto channel = AutoClone(new _AsyncOutputChannel(descriptor,stream,this));
    addChannel(channel);
    return channel;
}

void _AsyncOutputChannelPool::addChannel(AsyncOutputChannel channel) {
    int fd = channel->getFileDescriptor()->getFd();
    Synchronized(mMutex) {
        auto oldChannel = mChannels->get(fd);
        if(oldChannel != nullptr) {
            LOG(ERROR)<<"AsyncOutputChannel already add!!!";
            oldChannel->close();
            mObserver->removeObserver(fd);
        }
        mChannels->put(fd, channel);
    }
    mObserver->addObserver(fd,
                           EPOLLOUT|EPOLLHUP|EPOLLRDHUP,
                           AutoClone(this));
}

void _AsyncOutputChannelPool::remove(AsyncOutputChannel c) {
    Inspect(c == nullptr)
    int fd = c->getFileDescriptor()->getFd();
    Synchronized(mMutex) {
        auto channel = mChannels->get(fd);
        if(channel == c) {
            mChannels->remove(fd);
            mObserver->removeObserver(fd);
        }
    }
}

_AsyncOutputChannelPool::_AsyncOutputChannelPool() {
    mObserver = createEPollFileObserver();
    mChannels = createHashMap<int, AsyncOutputChannel>();
    mMutex = createMutex();
}

int _AsyncOutputChannelPool::onEvent(int fd, uint32_t events) {
    AsyncOutputChannel channel = nullptr;
    Synchronized(mMutex) {
        channel = mChannels->remove(fd);
    }
    mObserver->removeObserver(fd);
    if (channel != nullptr) {
        if((events & (EPOLLHUP|EPOLLRDHUP)) != 0) {
            channel->close();
        }else if ((events & EPOLLOUT) != 0) {
            channel->notifyWrite();
        }
    }
    return st(EPollFileObserver)::OK;
}

void _AsyncOutputChannelPool::close() {
    mObserver->close();

    //remove all channel
    Synchronized(mMutex) {
        ForEveryOne(pair,mChannels) {
            auto channel = pair->getValue();
            channel->close();
        }
        mChannels->clear();
    }
}

_AsyncOutputChannelPool::~_AsyncOutputChannelPool() {
    close();
    mObserver->join();
}

bool _AsyncOutputChannelPool::isEmpty() {
    return mChannels->size() == 0;
}

size_t _AsyncOutputChannelPool::size() {
    return mChannels->size();
}

} // namespace obotcha
