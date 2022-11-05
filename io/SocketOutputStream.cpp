#include "SocketOutputStream.hpp"
#include "InetAddress.hpp"
#include "Socket.hpp"

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
    if(!async) {
        mChannel = nullptr;
    } else {
        mChannel = mPool->createChannel(mFileDescriptor,mImpl);
    }
}

long _SocketOutputStream::write(ByteArray data) {
    if (mChannel != nullptr) {
        return mChannel->write(data);
    }
    return _write(data,0);
}

long _SocketOutputStream::write(ByteArray data, int start) {
    return write(data, start, data->size() - start);
}

long _SocketOutputStream::write(ByteArray data, int start, int len) {
    ByteArray senddata = createByteArray(&data->toValue()[start], len);
    
    if (mChannel != nullptr) {
        return mChannel->write(senddata);
    }

    return _write(senddata,0);
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

//long _SocketOutputStream::asyncWrite(ByteArray data,int offset) {
//    return _write(data,offset);
//}

_SocketOutputStream::~_SocketOutputStream() {
    //do nothing
    //close();
}

} // namespace obotcha
