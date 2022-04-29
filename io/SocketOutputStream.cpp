#include "SocketOutputStream.hpp"
#include "InetAddress.hpp"
#include "Socket.hpp"

namespace obotcha {

_SocketOutputStream::_SocketOutputStream(sp<_Socket> s) {
    impl = s->getSockImpl();
    
    fileDescriptor = s->getFileDescriptor();
    
    if (fileDescriptor!= nullptr && fileDescriptor->isAsync()) {
        //Add a mutex to protect channle for the following issue
        //1.Thread A:call write function to send data
        //2.Thread B(SocketMonitor) :if peer disconnet,close SocketOutputStream.
        //                         mChannel will be set as nullptr.
        //3.Thread A:call mChannel->write and crash(NullPointer...);
        mChannelMutex = createMutex();
        mChannel = createAsyncOutputChannel(
            fileDescriptor,
            std::bind(&_SocketOutputStream::_write, this, std::placeholders::_1,
                      std::placeholders::_2,std::placeholders::_3));
    }
}

long _SocketOutputStream::write(char c) {
    ByteArray data = createByteArray(1);
    data[0] = c;
    return write(data, 1);
}

long _SocketOutputStream::write(ByteArray data) {
    if(mChannelMutex != nullptr) {
        AutoLock l(mChannelMutex);
        if (mChannel != nullptr) {
            mChannel->write(data);
            return data->size();
        }
    }

    return _write(fileDescriptor, data,0);
}

long _SocketOutputStream::write(ByteArray data, int start) {
    return write(data, start, data->size() - start);
}

long _SocketOutputStream::write(ByteArray data, int start, int len) {
    ByteArray senddata = createByteArray(&data->toValue()[start], len);
    if(mChannelMutex != nullptr) {
        AutoLock l(mChannelMutex);
        if (mChannel != nullptr) {
            mChannel->write(senddata);
            return senddata->size();
        }
    }
    return _write(fileDescriptor, senddata,0);
}

long _SocketOutputStream::_write(FileDescriptor fd, ByteArray data,int offset) {
    if(impl != nullptr) {
        return impl->write(data,offset);
    }

    return -1;
}

void _SocketOutputStream::close() {
    if(mChannelMutex != nullptr) {   
        AutoLock l(mChannelMutex);
        if (mChannel != nullptr) {
            mChannel->close();
            mChannel = nullptr;
        }
    }
}

void _SocketOutputStream::flush() {
    //do nothing
}

_SocketOutputStream::~_SocketOutputStream() {
    //do nothing
}

} // namespace obotcha