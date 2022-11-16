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
    isClosed = false;
    mWriter = writer;
    mPool = pool;
}

int _AsyncOutputChannel::write(ByteArray d) {
    AutoLock l(mMutex);
    Inspect(isClosed,-1);
    
    if (mDatas->size() > 0) {
        ByteArray data = createByteArray(d);
        mDatas->putLast(data);
        return data->size();
    }
    
    return _write(d);
}

int _AsyncOutputChannel::notifyWrite() {
    AutoLock l(mMutex);
    Inspect(isClosed,-1);
    
    while (mDatas->size() > 0) {
        ByteArray data = mDatas->takeFirst();
        if(_write(data) != 0) {
            break;
        }
    }
    return 0;
}

int _AsyncOutputChannel::_write(ByteArray data) {
    int offset = 0;
    int result = 0;
    while (1) {
        result = mWriter->write(data,offset);
        if (result < 0) {
            if (errno == EAGAIN) {
                ByteArray restData = createByteArray(data->toValue() + offset,data->size() - offset);
                mDatas->putFirst(restData);
                mPool->addChannel(AutoClone(this));
            } else {
                //Write failed,remove channel
                mPool->remove(AutoClone(this));
            }
            return -1;
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
    Inspect(isClosed);
    
    if(mDatas != nullptr) {
        mDatas->clear();
        mDatas = nullptr;
    }

    isClosed = true;

    mPool->remove(AutoClone(this));

    //do not clear this.because ouputstream maybe used in
    //other thread.
    mWriter = nullptr;
    //mPool = nullptr;
}

void _AsyncOutputChannel::dump() {
    printf("---AsyncOutputChannel dump start --- \n");
    if(mDatas != nullptr) {
        printf("data size is %d \n",mDatas->size());
    }
    mPool->dump();
    printf("---AsyncOutputChannel dump end --- \n");
}

} // namespace obotcha
