#include "AsyncOutputChannel.hpp"
#include "ArrayList.hpp"
#include "AsyncOutputChannelPool.hpp"
#include "Error.hpp"
#include "Log.hpp"

namespace obotcha {

sp<_AsyncOutputChannelPool> _AsyncOutputChannel::mPool = nullptr;

_AsyncOutputChannel::_AsyncOutputChannel(FileDescriptor fd,
                                         WriteCallback callback) {
    mFd = fd;
    mMutex = createMutex();
    mDatas = createLinkedList<ByteArray>();
    writeCb = callback;
    isClosed = false;

    static std::once_flag s_flag;
    std::call_once(s_flag, [&]() {
        mPool = createAsyncOutputChannelPool();
    });
}

int _AsyncOutputChannel::write(ByteArray d) {
    ByteArray data = createByteArray(d);
    
    AutoLock l(mMutex);
    if (isClosed) {
        return -AlreadyDestroy;
    }

    if (mDatas->size() > 0) {
        mDatas->putLast(data);
        return 0;
    }

    return _write(data);
}

int _AsyncOutputChannel::notifyWrite() {
    AutoLock l(mMutex);
    if (isClosed) {
        return -AlreadyDestroy;
    }
    
    while (mDatas->size() > 0) {
        ByteArray data = mDatas->takeFirst();
        if(_write(data) != SUCCESS) {
            break;
        }
    }
    return 0;
}

int _AsyncOutputChannel::_write(ByteArray data) {
    int offset = 0;
    int result = 0;
    while (1) {
        if (writeCb != nullptr) {
            result = writeCb(mFd, data,offset);
        } else {
            result = ::write(mFd->getFd(), data->toValue() + offset, data->size() - offset);
        }
        if (result < 0) {
            if (errno == EAGAIN) {
                ByteArray restData = createByteArray(data->toValue() + offset,data->size() - offset);
                mDatas->putFirst(restData);
                mPool->addChannel(AutoClone(this));
            }
            return -WriteFail;
        } else if (result != (data->size() - offset)) {
            offset += result;
            continue;
        } 
        break;
    }

    return SUCCESS;
}

FileDescriptor _AsyncOutputChannel::getFileDescriptor() { 
    return mFd; 
}

void _AsyncOutputChannel::close() {
    AutoLock l(mMutex);
    if(mDatas != nullptr) {
        mDatas->clear();
        mDatas = nullptr;
    }

    isClosed = true;
    mPool->remove(AutoClone(this));
}

} // namespace obotcha