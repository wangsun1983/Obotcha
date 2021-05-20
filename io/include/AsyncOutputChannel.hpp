#ifndef __OBOTCHA_ASYNC_OUTPUT_CHANNEL_HPP__
#define __OBOTCHA_ASYNC_OUTPUT_CHANNEL_HPP__


#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ConcurrentQueue.hpp"
#include "ByteArray.hpp"
#include "LinkedList.hpp"
#include "Handler.hpp"
#include "FileDescriptor.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(AsyncOutputChannel) {
public:
    typedef std::function<long (FileDescriptor,ByteArray)> WriteCallback;

    _AsyncOutputChannel(FileDescriptor fileDescriptor,WriteCallback callback = nullptr,Handler h = nullptr);
    void write(ByteArray);
    void notifyWrite();
    FileDescriptor getFileDescriptor();
    void close();

private:
    Mutex mMutex;
    LinkedList<ByteArray> mDatas;
    WriteCallback writeCb;
    Handler mHandler;
    bool isClosed;
    FileDescriptor mFd;

    void _write(ByteArray);
};

}

#endif
