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

    std::once_flag s_flag;
    std::call_once(s_flag, [&]() {
        mPool = createAsyncOutputChannelPool();
    });
}

int _AsyncOutputChannel::write(ByteArray d) {
    int result = 0;
    int offset = 0;
    printf("_AsyncOutputChannel write trace1 \n");
    ByteArray data = createByteArray(d);
    
    AutoLock l(mMutex);
    if (isClosed) {
        return -AlreadyDestroy;
    }

    if (mDatas->size() > 0) {
        mDatas->putLast(data);
        printf("_AsyncOutputChannel write trace2,size is %d \n",mDatas->size());
        return 0;
    }

    while (1) {
        printf("_AsyncOutputChannel write trace3 \n");
        if (writeCb != nullptr) {
            result = writeCb(mFd, data,offset);
        } else {
            result = ::write(mFd->getFd(), data->toValue() + offset, data->size() - offset);
        }
        printf("_AsyncOutputChannel write trace4,result is %d,offset is %d,data size is %d \n",result,offset,data->size());
        if (result < 0) {
            if (errno == EAGAIN) {
                printf("_AsyncOutputChannel write trace5 \n");
                ByteArray restData = createByteArray(data->toValue() + offset,data->size() - offset);
                mDatas->putLast(restData);
                mPool->addChannel(AutoClone(this));
                break;
            }

            LOG(ERROR)<<"write failed,err is "<<strerror(errno);
            return -WriteFail;
        } else if (result != (data->size() - offset)) {
            offset += result;
            continue;
        }
        printf("_AsyncOutputChannel write trace6 \n");
        break;
    }
    
    return 0;
}

int _AsyncOutputChannel::notifyWrite() {
    printf("asyncoutput channel notifywrite!!!mDatas->size() is %d \n",mDatas->size());
    AutoLock l(mMutex);
    if (isClosed) {
        return -AlreadyDestroy;
    }
    
    while (mDatas->size() > 0) {
        printf("asyncoutput channel notifywrite data size is %d \n",mDatas->size());
        ByteArray data = mDatas->takeFirst();
        int offset = 0;
        int result = 0;
        while (1) {
            printf("asyncoutput channel notifywrite write trace3 \n");
            if (writeCb != nullptr) {
                result = writeCb(mFd, data,offset);
            } else {
                result = ::write(mFd->getFd(), data->toValue() + offset, data->size() - offset);
            }
            printf("asyncoutput channel notifywrite write trace4,result is %d,offset is %d,data size is %d \n",result,offset,data->size());
            if (result < 0) {
                if (errno == EAGAIN) {
                    printf("asyncoutput channel notifywrite write trace5 \n");
                    ByteArray restData = createByteArray(data->toValue() + offset,data->size() - offset);
                    mDatas->putFirst(restData);
                    mPool->addChannel(AutoClone(this));
                }
                LOG(ERROR)<<"write failed,err is "<<strerror(errno);
                return -WriteFail;
            } else if (result != (data->size() - offset)) {
                offset += result;
                continue;
            } 
            break;
        }
    }
    printf("asyncoutput channel notifywrite!!! \n");
    return 0;
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