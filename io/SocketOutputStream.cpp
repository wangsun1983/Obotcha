/**
 * @file SocketOutputStream.cpp
 * @brief SocketOutputStream is meant for write memory-mapped file of raw bytes 
 *        by socket.
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2024-01-03
 * @license none
 */
#include "SocketOutputStream.hpp"
#include "Socket.hpp"
#include "Inspect.hpp"
#include "NullPointerException.hpp"

namespace obotcha {

AsyncOutputChannelPool _SocketOutputStream::defaultOutputChannelPool = nullptr;

_SocketOutputStream::_SocketOutputStream(sp<_Socket> s,AsyncOutputChannelPool pool):_SocketOutputStream(s->mSockImpl,pool) {
}

_SocketOutputStream::_SocketOutputStream(SocketImpl sockImpl,AsyncOutputChannelPool pool):mImpl(sockImpl) {
    static std::once_flag s_flag;
    std::call_once(s_flag, []() {
        st(SocketOutputStream)::defaultOutputChannelPool = AsyncOutputChannelPool::New();
    });

    mFileDescriptor = mImpl->getFileDescriptor();
    mPool = (pool == nullptr)?defaultOutputChannelPool:pool;
    
    if (mFileDescriptor->isAsync() || pool != nullptr) {
        //Add a mutex to protect channle for the following issue
        //1.Thread A:call write function to send data
        //2.Thread B(SocketMonitor) :if peer disconnet,close SocketOutputStream.
        //                         mChannel will be set as nullptr.
        //3.Thread A:call mChannel->write and crash(NullPointer...);
        //mChannelMutex = Mutex::New();
        //mChannel = createAsyncOutputChannel(AutoClone(this),fileDescriptor);
        mFileDescriptor->setAsync(true);
        mChannel = st(AsyncOutputChannelPool)::CreateChannel(mFileDescriptor,mImpl);
        mPool->add(mChannel);
    }
}

long _SocketOutputStream::write(char c) {
    ByteArray data = ByteArray::New(1);
    data[0] = c;
    return write(data, 1);
}

void _SocketOutputStream::setAsync(bool async,AsyncOutputChannelPool pool) {
    mPool->remove(mChannel);
    mChannel = (async)?st(AsyncOutputChannelPool)::CreateChannel(mFileDescriptor,mImpl)
                        :nullptr;

    if(mChannel != nullptr) {
        mPool->add(mChannel);
    }
}

long _SocketOutputStream::write(ByteArray data) {
    return (mChannel == nullptr)?_write(data,0):mChannel->write(data);
}

long _SocketOutputStream::write(ByteArray data, uint64_t start) {
    return write(data, start, data->size() - start);
}

long _SocketOutputStream::write(ByteArray data, uint64_t start, uint64_t len) {
    Inspect(data->isOverflow(start,len),-1)
    return this->write(ByteArray::New(&data->toValue()[start], len,true));
}

long _SocketOutputStream::_write(ByteArray data,uint64_t offset) {
    Inspect(mImpl == nullptr,-1)
    return mImpl->write(data,offset);
}

void _SocketOutputStream::close() {
    if (mChannel != nullptr) {
        mChannel->close();
        mChannel = nullptr;
    }

    mImpl = nullptr;
}

void _SocketOutputStream::flush() {
    //do nothing
}

SocketImpl _SocketOutputStream::getSocket() {
    return mImpl;
}

} // namespace obotcha
