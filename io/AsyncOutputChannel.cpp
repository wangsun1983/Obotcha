#include "AsyncOutputChannel.hpp"
#include "AsyncOutputChannelPool.hpp"
#include "Log.hpp"
#include "Inspect.hpp"

namespace obotcha {

_AsyncWriteBlock::_AsyncWriteBlock(ByteArray data,size_t offset,bool map) {
    this->data = data;
    this->offset = offset;
    this->map = map;
}

_AsyncOutputChannel::_AsyncOutputChannel(FileDescriptor fd,
                                         OutputWriter writer,
                                         _AsyncOutputChannelPool* pool) {                                     
    mFd = fd;
    mMutex = createMutex();
    mDatas = createLinkedList<AsyncWriteBlock>();
    mWriter = writer;
    mPool = pool;                                    
}

size_t _AsyncOutputChannel::write(ByteArray &data) {
    AutoLock l(mMutex);
    Inspect(mWriter == nullptr,-1)
    if (mDatas->size() > 0) {
        mDatas->putLast(createAsyncWriteBlock(data->clone(),0,false));
        return data->size();
    }
    return directWrite(createAsyncWriteBlock(data,0,true));
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
    ssize_t result = 0;
    auto offset = block->offset;
    while(true) {
        result = mWriter->write(block->data,block->offset);
        if (result == -1) {
            if(errno == EAGAIN) {
                if(block->map) {
                    block->data = createByteArray(block->data->toValue() + block->offset, 
                                                  block->data->size() - block->offset);
                    block->map = false;
                    block->offset = 0;
                }
                mDatas->putFirst(block);
                mPool->addChannel(AutoClone(this));
            } else {
                close();
            }
            return -1;
        } else if (result < (block->data->size() - block->offset)) {
            block->offset += result;
            continue;
        }
        break;
    }

    return block->offset - offset;
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
