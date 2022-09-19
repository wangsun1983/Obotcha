#ifndef __OBOTCHA_ASYNC_OUTPUT_CHANNEL_HPP__
#define __OBOTCHA_ASYNC_OUTPUT_CHANNEL_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ByteArray.hpp"
#include "ConcurrentQueue.hpp"
#include "FileDescriptor.hpp"
#include "Handler.hpp"
#include "LinkedList.hpp"
#include "OutputStream.hpp"

namespace obotcha {

class _AsyncOutputChannelPool;

DECLARE_CLASS(AsyncOutputChannel) {
  public:
    friend class _AsyncOutputChannelPool;

    typedef std::function<long(FileDescriptor, ByteArray,int offset)> WriteCallback;

    _AsyncOutputChannel(OutputStream stream,
                        FileDescriptor fileDescriptor,
                        WriteCallback callback = nullptr);

    int write(ByteArray);

    FileDescriptor getFileDescriptor();

    void close();

    void dump();

  private:
    Mutex mMutex;
    LinkedList<ByteArray> mDatas;
    WriteCallback writeCb;
    bool isClosed;
    FileDescriptor mFd;

    int notifyWrite();
    int _write(ByteArray);

    OutputStream mOutputStream;

    static sp<_AsyncOutputChannelPool> mPool;
};

} // namespace obotcha

#endif
