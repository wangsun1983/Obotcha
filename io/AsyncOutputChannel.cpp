#include "AsyncOutputChannel.hpp"
#include "ArrayList.hpp"

namespace obotcha {

_AsyncOutputChannel::_AsyncOutputChannel(int fd) {
    mFd = fd;
    mMutex = createMutex();
    mDatas = createLinkedList<ByteArray>();
}

void _AsyncOutputChannel::write(ByteArray data) {
    AutoLock l(mMutex);
    if(mDatas->size() != 0) {
        mDatas->enQueueLast(data);
    }

    while(mDatas->size() > 0) {
        ByteArray data = mDatas->deQueueFirst();
        int result = ::write(mFd,data->toValue(),data->size());
    }
    
}

}