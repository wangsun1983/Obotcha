#include "AsyncOutputChannelPool.hpp"

namespace obotcha {

std::once_flag _AsyncOutputChannelPool::s_flag;
sp<_AsyncOutputChannelPool> _AsyncOutputChannelPool::mInstance;

sp<_AsyncOutputChannelPool> _AsyncOutputChannelPool::getInstance() {
    std::call_once(s_flag, [&]() {
        _AsyncOutputChannelPool *p = new _AsyncOutputChannelPool();
        p->mInstance.set_pointer(p);
    });

    return mInstance;
}

void _AsyncOutputChannelPool::addChannel(AsyncOutputChannel c) {
    AutoLock l(mMutex);
    mChannels->put(c->getFileDescriptor()->getFd(),c);
    mObserver->addObserver(c->getFileDescriptor()->getFd(),st(EPollFileObserver)::EpollOut,AutoClone(this));
}

void _AsyncOutputChannelPool::remove(AsyncOutputChannel c) {
    AutoLock l(mMutex);
    mChannels->remove(c->getFileDescriptor()->getFd());
    mObserver->removeObserver(c->getFileDescriptor()->getFd());
}

_AsyncOutputChannelPool::_AsyncOutputChannelPool() {
    mObserver = createEPollFileObserver();
    mChannels = createHashMap<int,AsyncOutputChannel>();
    mMutex = createMutex();
}

int _AsyncOutputChannelPool::onEvent(int fd,uint32_t events,ByteArray) {
    if((events & st(EPollFileObserver)::EpollOut) != 0) {
        AsyncOutputChannel ch = nullptr;
        {
            AutoLock l(mMutex);
            ch = mChannels->get(fd);
        }
        if(ch != nullptr) {
            ch->notifyWrite();
        }
    }

    return st(EPollFileObserver)::OnEventOK;
}

}
