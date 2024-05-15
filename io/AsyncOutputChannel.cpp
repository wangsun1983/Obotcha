/**
 * @file AsyncOutputChannel.cpp
 * @brief  A channel that supports asynchronous I/O operations.
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2024-01-03
 * @license none
 */

#include "AsyncOutputChannel.hpp"
#include "AsyncOutputChannelPool.hpp"
#include "Log.hpp"
#include "Inspect.hpp"

namespace obotcha {

_AsyncWriteBlock::_AsyncWriteBlock(ByteArray d,size_t o,bool m):data(d),offset(o),map(m) {
}

_AsyncOutputChannel::_AsyncOutputChannel(FileDescriptor fd,
                                         OutputWriter writer,
                                         _AsyncOutputChannelPool* pool):mFd(fd),mWriter(writer),mPool(pool) {
    mMutex = Mutex::New();
    mDatas = LinkedList<AsyncWriteBlock>::New();
}

size_t _AsyncOutputChannel::write(ByteArray &data) {
    AutoLock l(mMutex);
    Inspect(mWriter == nullptr,-1)
    if (mDatas->size() > 0 ) {
        mDatas->putLast(AsyncWriteBlock::New(data->clone(),0,false));
        return data->size();
    }
    return directWrite(AsyncWriteBlock::New(data,0,true));
}

int _AsyncOutputChannel::notifyWrite() {
    AutoLock l(mMutex);
    Inspect(mWriter == nullptr,-1)
    while (mDatas != nullptr && mDatas->size() > 0
        && directWrite(mDatas->takeFirst()) != -1) {
        //do nothing
    }
    return 0;
}

size_t _AsyncOutputChannel::directWrite(AsyncWriteBlock block) {
    ssize_t writelen = 0;
    while(block->offset < block->data->size()) {
        //whether mWriter is nullptr is checked by notifyWrite().
        ssize_t result = mWriter->write(block->data,block->offset);
        if (result == -1) {
            if(errno == EAGAIN) {
                if(block->map) {
                    block->data = ByteArray::New(block->data->toValue() + block->offset, 
                                                  block->data->size() - block->offset);
                    block->map = false;
                    block->offset = 0;
                }
                mDatas->putFirst(block);
                if(mPool != nullptr) {
                    mPool->addChannel(AutoClone(this));
                }
            } else {
                close();
            }
            return -1;
        }
        block->offset += result;
        writelen += result;
    }
    return writelen;
}

FileDescriptor _AsyncOutputChannel::getFileDescriptor() {
    return mFd;
}

void _AsyncOutputChannel::updatePool(_AsyncOutputChannelPool* pool) {
    this->mPool = pool;
}

void _AsyncOutputChannel::close() {
    AutoLock l(mMutex);
    Inspect(mDatas == nullptr)

    if(mDatas != nullptr) {
        mDatas->clear();
        mDatas = nullptr;
    }

    if(mPool != nullptr) {
        mPool->remove(AutoClone(this));
        mPool = nullptr;
    }
    //do not clear this.because ouputstream maybe used in
    //other thread.
    mWriter = nullptr;
}

} // namespace obotcha
