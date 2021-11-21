#include "SocketOutputStream.hpp"
#include "InetAddress.hpp"
#include "Socket.hpp"

namespace obotcha {

_SocketOutputStream::_SocketOutputStream(sp<_Socket> s) {
    mSocket = s;
    
    if (s->getFileDescriptor()->isAsync()) {
        mChannel = createAsyncOutputChannel(
            s->getFileDescriptor(),
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
    if (mChannel != nullptr) {
        mChannel->write(data);
        return data->size();
    }
    return _write(mSocket->getFileDescriptor(), data,0);
}

long _SocketOutputStream::write(ByteArray data, int start) {
    return write(data, start, data->size() - start);
}

long _SocketOutputStream::write(ByteArray data, int start, int len) {
    ByteArray senddata = createByteArray(&data->toValue()[start], len);
    if (mChannel != nullptr) {
        mChannel->write(senddata);
        return senddata->size();
    }
    return _write(mSocket->getFileDescriptor(), senddata,0);
}

long _SocketOutputStream::_write(FileDescriptor fd, ByteArray data,int offset) {
    if (mSocket == nullptr || mSocket->isClosed()) {
        return -1;
    }

    return mSocket->mSock->write(data,offset);
}

void _SocketOutputStream::close() {
    mSocket = nullptr;
    if (mChannel != nullptr) {
        mChannel->close();
        mChannel = nullptr;
    }
}

void _SocketOutputStream::flush() {
    // TODO
}

_SocketOutputStream::~_SocketOutputStream() {
    mSocket = nullptr;
}

} // namespace obotcha