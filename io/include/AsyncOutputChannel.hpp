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

DECLARE_CLASS(AsyncOutputChannel) {
public:
    friend class _AsyncOutputChannelPool;

    int write(ByteArray &);
    FileDescriptor getFileDescriptor();
    void close();

private:
    _AsyncOutputChannel(FileDescriptor descriptor,
                        OutputWriter writer,
                        _AsyncOutputChannelPool* pool);
    int notifyWrite();
    int directWrite(ByteArray);

    Mutex mMutex;
    LinkedList<ByteArray> mDatas;
    FileDescriptor mFd;
    OutputWriter mWriter;
    _AsyncOutputChannelPool *mPool;
};

} // namespace obotcha

#endif
