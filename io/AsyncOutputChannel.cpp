#include "AsyncOutputChannel.hpp"
#include "AsyncOutputChannelPool.hpp"
#include "Log.hpp"
#include "Inspect.hpp"
#include "InfiniteLoop.hpp"

namespace obotcha {

_AsyncOutputChannel::_AsyncOutputChannel(FileDescriptor fd,
                                         OutputWriter writer,
                                         _AsyncOutputChannelPool* pool) {
    mFd = fd;
    mMutex = createMutex();
    mDatas = createLinkedList<ByteArray>();
    mIsClosed = false;
    mWriter = writer;
    mPool = pool;
}

int _AsyncOutputChannel::write(ByteArray &data) {
    AutoLock l(mMutex);
    Inspect(mIsClosed,-1);
    
    if (mDatas->size() > 0) {
        mDatas->putLast(data->clone());
        return data->size();
    }
    
    return _write(data);
}

int _AsyncOutputChannel::notifyWrite() {
    AutoLock l(mMutex);
    Inspect(mIsClosed,-1);
    while (mDatas->size() > 0
        && _write(mDatas->takeFirst()) > 0) {
        //do nothing
    }
    return 0;
}

int _AsyncOutputChannel::_write(ByteArray data) {
    int offset = 0;
    InfiniteLoop {
        int result = mWriter->write(data,offset);
        if (result < 0) {
            switch(errno) {
                case EAGAIN: {
                    auto retryData = createByteArray(data->toValue() + offset, data->size() - offset);
                    mDatas->putFirst(retryData);
                    mPool->addChannel(AutoClone(this));
                } break;
                default:
                    mPool->remove(AutoClone(this));
                    break;
            }
            return -errno;
        } 
        
        if (result < (data->size() - offset)) {
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
    Inspect(mIsClosed);
    
    if(mDatas != nullptr) {
        mDatas->clear();
        mDatas = nullptr;
    }

    mIsClosed = true;

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
