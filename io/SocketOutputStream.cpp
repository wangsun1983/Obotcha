#include "SocketOutputStream.hpp"
#include "Socket.hpp"
#include "Inspect.hpp"

namespace obotcha {

AsyncOutputChannelPool _SocketOutputStream::defaultOutputChannelPool = nullptr;

_SocketOutputStream::_SocketOutputStream(sp<_Socket> s,AsyncOutputChannelPool pool):_SocketOutputStream(s->mSockImpl,pool) {
}

_SocketOutputStream::_SocketOutputStream(SocketImpl sockImpl,AsyncOutputChannelPool pool) {
    static std::once_flag s_flag;
    std::call_once(s_flag, [&]() {
        defaultOutputChannelPool = createAsyncOutputChannelPool();
    });

    mImpl = sockImpl;
    mFileDescriptor = mImpl->getFileDescriptor();

    if(pool != nullptr) {
        mFileDescriptor->setAsync(true);
        mPool = pool; 
    } else {
        mPool = defaultOutputChannelPool;
    }
    
    if (mFileDescriptor != nullptr && mFileDescriptor->isAsync()) {
        //Add a mutex to protect channle for the following issue
        //1.Thread A:call write function to send data
        //2.Thread B(SocketMonitor) :if peer disconnet,close SocketOutputStream.
        //                         mChannel will be set as nullptr.
        //3.Thread A:call mChannel->write and crash(NullPointer...);
        //mChannelMutex = createMutex();
        //mChannel = createAsyncOutputChannel(AutoClone(this),fileDescriptor);
        mChannel = mPool->createChannel(mFileDescriptor,mImpl);
    }
}

long _SocketOutputStream::write(char c) {
    ByteArray data = createByteArray(1);
    data[0] = c;
    return write(data, 1);
}

void _SocketOutputStream::setAsync(bool async,AsyncOutputChannelPool pool) {
    mPool->remove(mChannel);
    mChannel = (!async)?mChannel:mPool->createChannel(mFileDescriptor,mImpl);
}

long _SocketOutputStream::write(ByteArray data) {
    return (mChannel == nullptr)?_write(data,0):mChannel->write(data);
}

long _SocketOutputStream::write(ByteArray data, int start) {
    return write(data, start, data->size() - start);
}

long _SocketOutputStream::write(ByteArray data, int start, int len) {
    Inspect(start + len > data->size(),-1);
    ByteArray senddata = createByteArray(&data->toValue()[start], len);
    return this->write(senddata);
}

long _SocketOutputStream::_write(ByteArray data,int offset) {
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
    

_SocketOutputStream::~_SocketOutputStream() {
    //do nothing
}

} // namespace obotcha
