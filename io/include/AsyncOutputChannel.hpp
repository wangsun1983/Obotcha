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
    _AsyncOutputChannel(int fd);
    void write(ByteArray);

private:
    int mFd;
    Mutex mMutex;
    LinkedList<ByteArray> mDatas;
};

}

#endif
