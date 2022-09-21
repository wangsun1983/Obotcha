#include "AsyncOutputChannel.hpp"
#include "ArrayList.hpp"
#include "AsyncOutputChannelPool.hpp"
#include "Error.hpp"
#include "Log.hpp"

namespace obotcha {

sp<_AsyncOutputChannelPool> _AsyncOutputChannel::mPool = nullptr;

_AsyncOutputChannel::_AsyncOutputChannel(AsyncOutputWriter stream,FileDescriptor fd) {
    mFd = fd;
    mMutex = createMutex();
    mDatas = createLinkedList<ByteArray>();
    isClosed = false;

    mWriter = stream;

    static std::once_flag s_flag;
    std::call_once(s_flag, [&]() {
        mPool = createAsyncOutputChannelPool();
    });
}

int _AsyncOutputChannel::write(ByteArray d) {
    AutoLock l(mMutex);
    if (isClosed) {
        return -1;
    }
    
    ByteArray data = createByteArray(d);
    printf("write,data size is %d \n",mDatas->size());
    if (mDatas->size() > 0) {
        mDatas->putLast(data);
        return data->size();
    }
    
    return _write(data);
}

int _AsyncOutputChannel::notifyWrite() {
    AutoLock l(mMutex);
    if (isClosed) {
        return -1;
    }
    printf("notify write,data size is %d \n",mDatas->size());
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
        result = mWriter->asyncWrite(data,offset);
        printf("write result is %d \n",result);
        if (result < 0) {
            if (errno == EAGAIN) {
                ByteArray restData = createByteArray(data->toValue() + offset,data->size() - offset);
                mDatas->putFirst(restData);
                printf("AsyncOutputChannel add channel \n");
                mPool->addChannel(AutoClone(this));
            } else {
                printf("AsyncOutputChannel write fail,reason is %s \n",strerror(errno));
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

    return 0;
}

FileDescriptor _AsyncOutputChannel::getFileDescriptor() {
    return mFd;
}

void _AsyncOutputChannel::close() {
    AutoLock l(mMutex);
    if(isClosed) {
        return;
    }

    if(mDatas != nullptr) {
        mDatas->clear();
        mDatas = nullptr;
    }

    isClosed = true;

    mPool->remove(AutoClone(this));

    mWriter = nullptr;
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
