#include "AsyncOutputChannelPool.hpp"
#include "Error.hpp"

namespace obotcha {

void _AsyncOutputChannelPool::addChannel(AsyncOutputChannel c) {
    AutoLock l(mMutex);
    mChannels->put(c->getFileDescriptor()->getFd(), c);
    mObserver->addObserver(c->getFileDescriptor()->getFd(),
                           st(EPollFileObserver)::EpollOut, AutoClone(this));
}

void _AsyncOutputChannelPool::remove(AsyncOutputChannel c) {
    AutoLock l(mMutex);
    mChannels->remove(c->getFileDescriptor()->getFd());
    mObserver->removeObserver(c->getFileDescriptor()->getFd());
}

_AsyncOutputChannelPool::_AsyncOutputChannelPool() {
    mObserver = createEPollFileObserver();
    mChannels = createHashMap<int, AsyncOutputChannel>();
    mMutex = createMutex();
}

int _AsyncOutputChannelPool::onEvent(int fd, uint32_t events) {
    if ((events & st(EPollFileObserver)::EpollOut) != 0) {
        printf("asyncoutput pool onevent!!!!!!!!!!!!!!!!!!!!!!!!! \n");
        AsyncOutputChannel ch = nullptr;
        {
            AutoLock l(mMutex);
            ch = mChannels->get(fd);
            remove(ch);
        }

        if (ch != nullptr) {
            ch->notifyWrite();
        }
    }

    return st(EPollFileObserver)::OnEventOK;
}

} // namespace obotcha
