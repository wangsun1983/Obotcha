#include "AsyncOutputChannelPool.hpp"

namespace obotcha {

Mutex _AsyncOutputChannelPool::mMutex = createMutex();

sp<_AsyncOutputChannelPool> _AsyncOutputChannelPool::mInstance = nullptr;

sp<_AsyncOutputChannelPool> _AsyncOutputChannelPool::getInstance() {
    if(mInstance != nullptr) {
        return mInstance;
    }

    AutoLock l(mMutex);

    if(mInstance == nullptr) {
        _AsyncOutputChannelPool *p = new _AsyncOutputChannelPool();
        mInstance.set_pointer(p);
    }

    return mInstance;
}

void _AsyncOutputChannelPool::addChannel(AsyncOutputChannel c) {
    AutoLock l(mMutex);
    mChannels->put(c->getFd(),c);
    mObserver->addObserver(c->getFd(),st(EPollFileObserver)::EpollOut,AutoClone(this));
}

void _AsyncOutputChannelPool::remove(AsyncOutputChannel c) {
    AutoLock l(mMutex);
    mChannels->remove(c->getFd());
    mObserver->removeObserver(c->getFd());
}

_AsyncOutputChannelPool::_AsyncOutputChannelPool() {
    mObserver = createEPollFileObserver();
    mChannels = createHashMap<int,AsyncOutputChannel>();
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
