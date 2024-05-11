/**
 * @file AsyncOutputChannelPool.cpp
 * @brief  A pool of asynchronous channels for the purpose of resource sharing.
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2024-01-03
 * @license none
 */

#include "AsyncOutputChannelPool.hpp"
#include "AsyncOutputChannel.hpp"
#include "ForEveryOne.hpp"
#include "Log.hpp"
#include "Synchronized.hpp"
#include "Inspect.hpp"

namespace obotcha {

AsyncOutputChannel _AsyncOutputChannelPool::createChannel(FileDescriptor descriptor,OutputWriter stream) {
    auto channel = AutoClone(new _AsyncOutputChannel(descriptor,stream,this));
    return channel;
}

void _AsyncOutputChannelPool::addChannel(AsyncOutputChannel channel,bool ShouldRemovePreviousPool) {
    int fd = channel->getFileDescriptor()->getFd();
    Synchronized(mMutex) {
        //if this channel has register in other channel,
        //remove it first.
        if(ShouldRemovePreviousPool && channel->mPool != this) {
            channel->mPool->remove(channel);
            channel->mPool = this;
        }

        mChannels->put(fd, channel);
        mObserver->addObserver(fd,
                           EPOLLOUT|EPOLLHUP|EPOLLRDHUP,
                           AutoClone(this));
    }
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
    mObserver = EPollObserver::New();
    mChannels = HashMap<int, AsyncOutputChannel>::New();
    mMutex = Mutex::New();
}

st(IO)::Epoll::Result _AsyncOutputChannelPool::onEvent(int fd, uint32_t events) {
    AsyncOutputChannel channel = nullptr;
    Synchronized(mMutex) {
        channel = mChannels->get(fd);
        mObserver->removeObserver(fd);
    }

    if (channel != nullptr) {
        if((events & (EPOLLHUP|EPOLLRDHUP)) != 0) {
            channel->close();
        } else if ((events & EPOLLOUT) != 0) {
            channel->notifyWrite();
        }
    }
    return st(IO)::Epoll::Result::Ok;
}

void _AsyncOutputChannelPool::close(bool closeAllChannels) {
    mObserver->close();
    //remove all channel
    Synchronized(mMutex) {
        ForEveryOne(pair,mChannels) {
            auto channel = pair->getValue();
            if(!closeAllChannels) {
                AutoLock ll(channel->mMutex);
                channel->mPool = nullptr;
            } else {
                channel->close();
            }
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
