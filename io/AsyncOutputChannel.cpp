#include "AsyncOutputChannel.hpp"
#include "AsyncOutputChannelPool.hpp"
#include "ArrayList.hpp"

namespace obotcha {

_AsyncOutputChannel::_AsyncOutputChannel(int fd,WriteCallback callback,Handler h) {
    mFd = fd;
    mMutex = createMutex();
    mDatas = createLinkedList<ByteArray>();
    writeCb = callback;
    mHandler = h;
    isClosed = false;
}

void _AsyncOutputChannel::write(ByteArray data) {
    if(mHandler != nullptr) {
        mHandler->post([](AsyncOutputChannel channel,ByteArray data) {
            channel->_write(data);
        },AutoClone(this),data);
    } else {
        _write(data);
    }
}

void _AsyncOutputChannel::_write(ByteArray data) {
    AutoLock l(mMutex);
    if(isClosed) {
        return;
    }
    
    if(mDatas->size() > 0) {
        mDatas->enQueueLast(data);
        return;
    }

    while(1) {
        int result = 0;
        if(writeCb != nullptr) {
            result = writeCb(mFd,data);
        } else {
            result = ::write(mFd,data->toValue(),data->size());
        }

        if(result < 0) {
            if(errno == EAGAIN) {
                mDatas->enQueueLast(data);
                st(AsyncOutputChannelPool)::getInstance()->addChannel(AutoClone(this));
            }
        } else if(result != data->size()) {
            ByteArray rest_data = createByteArray(data->toValue() + result,data->size() - result);
            data = rest_data;
            continue;
        }
        break;
    }
}

void _AsyncOutputChannel::notifyWrite() {
    AutoLock l(mMutex);
    if(isClosed) {
        return;
    }

    while(mDatas->size() > 0) {
        ByteArray data = mDatas->deQueueFirst();
        int result = 0;
        if(writeCb != nullptr) {
            result = writeCb(mFd,data);
        } else {
            result = ::write(mFd,data->toValue(),data->size());
        }

        if(result < 0) {
            if(errno == EAGAIN) {
                mDatas->enQueueFirst(data);
                break;
            }
        } else if(result != data->size()) {
            ByteArray rest_data = createByteArray(data->toValue() + result,data->size() - result);
            mDatas->enQueueFirst(rest_data);
        }
    }

    if(mDatas->size() == 0) {
        st(AsyncOutputChannelPool)::getInstance()->remove(AutoClone(this));
    }
}


int _AsyncOutputChannel::getFd() {
    return mFd;
}

void _AsyncOutputChannel::close() {
    AutoLock l(mMutex);
    isClosed = true;
    mDatas->clear();
    st(AsyncOutputChannelPool)::getInstance()->remove(AutoClone(this));
}

}