#include "AsyncOutputChannelPool.hpp"
#include "Error.hpp"

namespace obotcha {

void _AsyncOutputChannelPool::addChannel(AsyncOutputChannel c) {
    AutoLock l(mMutex);
    mChannels->put(c->getFileDescriptor()->getFd(), c);
    mObserver->addObserver(c->getFileDescriptor()->getFd(),
                           st(EPollFileObserver)::EpollOut|st(EPollFileObserver)::EpollHup|st(EPollFileObserver)::EpollRdHup,
                           AutoClone(this));
}

void _AsyncOutputChannelPool::remove(AsyncOutputChannel c) {
    AutoLock l(mMutex);
    auto channel = mChannels->get(c->getFileDescriptor()->getFd());
    if(channel == c) {
        mChannels->remove(c->getFileDescriptor()->getFd());
        mObserver->removeObserver(c->getFileDescriptor()->getFd());
    }
}

_AsyncOutputChannelPool::_AsyncOutputChannelPool() {
    mObserver = createEPollFileObserver();
    mChannels = createHashMap<int, AsyncOutputChannel>();
    mMutex = createMutex();
}

int _AsyncOutputChannelPool::onEvent(int fd, uint32_t events) {
    AsyncOutputChannel ch = nullptr;
    {
        AutoLock l(mMutex);
        ch = mChannels->get(fd);
        remove(ch);
    }

    if (ch != nullptr) {
        if((events & (st(EPollFileObserver)::EpollHup|st(EPollFileObserver)::EpollRdHup)) != 0) {
            ch->close();
        }else if ((events & st(EPollFileObserver)::EpollOut) != 0) {
            ch->notifyWrite();
        }

    }

    return st(EPollFileObserver)::OnEventOK;
}

} // namespace obotcha
