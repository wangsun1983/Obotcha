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
#include "OutputWriter.hpp"

namespace obotcha {

class _AsyncOutputChannelPool;

//DECLARE_CLASS(AsyncOutputWriter) {
//public:
//  virtual long asyncWrite(ByteArray,int) = 0;
//};

DECLARE_CLASS(AsyncOutputChannel) {
  public:
    friend class _AsyncOutputChannelPool;

    int write(ByteArray);

    FileDescriptor getFileDescriptor();

    void close();

    void dump();
    
  private:
    _AsyncOutputChannel(FileDescriptor descriptor,
                        OutputWriter writer,
                        _AsyncOutputChannelPool* pool);

    Mutex mMutex;
    LinkedList<ByteArray> mDatas;
    
    bool isClosed;
    
    FileDescriptor mFd;

    int notifyWrite();

    int _write(ByteArray);

    OutputWriter mWriter;

    _AsyncOutputChannelPool *mPool;
};

} // namespace obotcha

#endif
