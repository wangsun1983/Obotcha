#include "SocketOutputStream.hpp"
#include "InetAddress.hpp"
#include "Socket.hpp"

namespace obotcha {

_SocketOutputStream::_SocketOutputStream(sp<_Socket> s):_SocketOutputStream(s->getSockImpl()) {
}

_SocketOutputStream::_SocketOutputStream(SocketImpl sockimpl) {
    impl = sockimpl;
    fileDescriptor = impl->getFileDescriptor();
    if(fileDescriptor == nullptr) {
        printf("socket ouputstream  fd is null");
    }
    printf("socket ouputstream init \n");
    if (fileDescriptor != nullptr && fileDescriptor->isAsync()) {
        //Add a mutex to protect channle for the following issue
        //1.Thread A:call write function to send data
        //2.Thread B(SocketMonitor) :if peer disconnet,close SocketOutputStream.
        //                         mChannel will be set as nullptr.
        //3.Thread A:call mChannel->write and crash(NullPointer...);
        //mChannelMutex = createMutex();
        printf("socket ouputstream init2 \n");
        mChannel = createAsyncOutputChannel(AutoClone(this),fileDescriptor);
    }
    printf("socket ouputstream init3 \n");
}

long _SocketOutputStream::write(char c) {
    ByteArray data = createByteArray(1);
    data[0] = c;
    return write(data, 1);
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
    if(impl != nullptr) {
        return impl->write(data,offset);
    }

    return -1;
}

void _SocketOutputStream::close() {
    if (mChannel != nullptr) {
        mChannel->close();
    }

    impl = nullptr;
}

void _SocketOutputStream::flush() {
    //do nothing
}

long _SocketOutputStream::asyncWrite(ByteArray data,int offset) {
    return _write(data,offset);
}

_SocketOutputStream::~_SocketOutputStream() {
    //do nothing
}

} // namespace obotcha
