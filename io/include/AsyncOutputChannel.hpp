#ifndef __OBOTCHA_ASYNC_OUTPUT_CHANNEL_HPP__
#define __OBOTCHA_ASYNC_OUTPUT_CHANNEL_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ByteArray.hpp"
#include "ConcurrentQueue.hpp"
#include "FileDescriptor.hpp"
#include "Handler.hpp"
#include "LinkedList.hpp"

namespace obotcha {

class _AsyncOutputChannelPool;

DECLARE_CLASS(AsyncOutputChannel) {
  public:
    typedef std::function<long(FileDescriptor, ByteArray,int offset)> WriteCallback;

    _AsyncOutputChannel(FileDescriptor fileDescriptor,
                        WriteCallback callback = nullptr);

    int write(ByteArray);

    int notifyWrite();
    
    FileDescriptor getFileDescriptor();
    
    void close();

  private:
    Mutex mMutex;
    LinkedList<ByteArray> mDatas;
    WriteCallback writeCb;
    bool isClosed;
    FileDescriptor mFd;

    static sp<_AsyncOutputChannelPool> mPool;
};

} // namespace obotcha

#endif
