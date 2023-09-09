#include "AsyncOutputChannel.hpp"
#include "AsyncOutputChannelPool.hpp"
#include "Log.hpp"
#include "Inspect.hpp"

namespace obotcha {

_AsyncOutputChannel::_AsyncOutputChannel(FileDescriptor fd,
                                         OutputWriter writer,
                                         _AsyncOutputChannelPool* pool) {
    mFd = fd;
    mMutex = createMutex();
    mDatas = createLinkedList<ByteArray>();
    mWriter = writer;
    mPool = pool;
}

int _AsyncOutputChannel::write(ByteArray &data) {
    AutoLock l(mMutex);
    Inspect(mWriter == nullptr,-1)
    if (mDatas->size() > 0) {
        mDatas->putLast(data->clone());
        return data->size();
    }

    return directWrite(data);
}

int _AsyncOutputChannel::notifyWrite() {
    AutoLock l(mMutex);
    Inspect(mWriter == nullptr,-1)
    while (mDatas->size() > 0
        && directWrite(mDatas->takeFirst()) > 0) {
        //do nothing
    }
    return 0;
}

int _AsyncOutputChannel::directWrite(ByteArray data) {
    int offset = 0;
    int result = 0;
    while(true) {
        result = mWriter->write(data,offset);      
        if (result < 0) {
            if(errno == EAGAIN) {
                auto retryData = createByteArray(data->toValue() + offset, data->size() - offset);
                mDatas->putFirst(retryData);
                mPool->addChannel(AutoClone(this));
            } else {
                close();
            }
            return -errno;
        } else if (result < (data->size() - offset)) {
            offset += result;
            continue;
        }
        break;
    }

    return data->size();
}

FileDescriptor _AsyncOutputChannel::getFileDescriptor() {
    return mFd;
}

void _AsyncOutputChannel::close() {
    AutoLock l(mMutex);
    Inspect(mDatas == nullptr)

    if(mDatas != nullptr) {
        mDatas->clear();
        mDatas = nullptr;
    }
    mPool->remove(AutoClone(this));

    //do not clear this.because ouputstream maybe used in
    //other thread.
    mWriter = nullptr;
}

} // namespace obotcha
