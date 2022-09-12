#include "AsyncOutputChannelPool.hpp"
#include "Error.hpp"

namespace obotcha {

void _AsyncOutputChannelPool::addChannel(AsyncOutputChannel c) {
    //AutoLock l(mMutex);
    mChannels->put(c->getFileDescriptor()->getFd(), c);
    mObserver->addObserver(c->getFileDescriptor()->getFd(),
                           st(EPollFileObserver)::EpollOut|st(EPollFileObserver)::EpollHup|st(EPollFileObserver)::EpollRdHup,
                           AutoClone(this));
}

void _AsyncOutputChannelPool::remove(AsyncOutputChannel c) {
    auto channel = mChannels->get(c->getFileDescriptor()->getFd());
    if(channel == c) {
        mChannels->remove(c->getFileDescriptor()->getFd());
        mObserver->removeObserver(c->getFileDescriptor()->getFd());
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
        }else if ((events & st(EPollFileObserver)::EpollOut) != 0) {
            channel->notifyWrite();
        }

    }

    return st(EPollFileObserver)::OnEventOK;
}

void _AsyncOutputChannelPool::close() {
    mObserver->close();
}

void _AsyncOutputChannelPool::dump() {
    printf("AsyncOutputChannelPool,channel size is %d \n",mChannels->size());
    mObserver->dump();
}

} // namespace obotcha
