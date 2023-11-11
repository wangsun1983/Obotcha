#ifndef __OBOTCHA_ASYNC_OUTPUT_CHANNEL_HPP__
#define __OBOTCHA_ASYNC_OUTPUT_CHANNEL_HPP__

#include "Object.hpp"
#include "ByteArray.hpp"
#include "FileDescriptor.hpp"
#include "LinkedList.hpp"
#include "OutputWriter.hpp"
#include "Mutex.hpp"

namespace obotcha {

class _AsyncOutputChannelPool;

DECLARE_CLASS(AsyncWriteBlock) {
public:
    _AsyncWriteBlock(ByteArray,size_t offset,bool map);
    ByteArray data;
    size_t offset;
    bool map;
};

DECLARE_CLASS(AsyncOutputChannel) {
public:
    friend class _AsyncOutputChannelPool;

    size_t write(ByteArray &);
    FileDescriptor getFileDescriptor();
    void close();

private:
    _AsyncOutputChannel(FileDescriptor descriptor,
                        OutputWriter writer,
                        _AsyncOutputChannelPool* pool);
    int notifyWrite();
    size_t directWrite(AsyncWriteBlock);

    Mutex mMutex;
    LinkedList<AsyncWriteBlock> mDatas;
    FileDescriptor mFd;
    OutputWriter mWriter;
    _AsyncOutputChannelPool *mPool;
};

} // namespace obotcha

#endif
