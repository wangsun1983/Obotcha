#ifndef __OBOTCHA_ASYNC_OUTPUT_CHANNEL_HPP__
#define __OBOTCHA_ASYNC_OUTPUT_CHANNEL_HPP__


#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ConcurrentQueue.hpp"
#include "ByteArray.hpp"
#include "LinkedList.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(AsyncOutputChannel) {
public:
    typedef std::function<long (int,ByteArray)> WriteCallback;

    _AsyncOutputChannel(int fd,WriteCallback callback = nullptr);
    void write(ByteArray);
    void notifyWrite();
    int getFd();
    void close();

private:
    int mFd;
    Mutex mMutex;
    LinkedList<ByteArray> mDatas;
    WriteCallback writeCb;
};

}

#endif
