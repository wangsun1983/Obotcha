#include "SocketOutputStream.hpp"
#include "InetAddress.hpp"
#include "Socket.hpp"

namespace obotcha {

_SocketOutputStream::_SocketOutputStream(sp<_Socket> s) {
    mSocket = s;
    if (mSocket->getType() == st(Socket)::Udp) {
        server_addr.sin_family = AF_INET;
        InetAddress address = s->getInetAddress();
        server_addr.sin_port = htons(address->getPort());

        if (address->getAddress() != nullptr) {
            server_addr.sin_addr.s_addr =
                inet_addr(address->getAddress()->toChars());
        } else {
            server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        }
    }
    printf("SocketOutputStream create start \n");

    if (s->getFileDescriptor()->isAsync()) {
        printf("SocketOutputStream create trace1 \n");
    
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
    printf("SocketOutputStream write start \n");
    if (mChannel != nullptr) {
        printf("SocketOutputStream write trace1 \n");
        mChannel->write(data);
        return data->size();
    }
    return _write(mSocket->getFileDescriptor(), data,0);
}

long _SocketOutputStream::write(ByteArray data, int start) {
    return this->write(data, start, data->size() - start);
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
    printf("SocketOutputStream _write start \n");
    if (mSocket == nullptr || mSocket->isClosed()) {
        return -1;
    }

    byte *sendData = data->toValue();
    switch (mSocket->getType()) {
        case st(Socket)::Udp: {
            return ::sendto(fd->getFd(), data->toValue() + offset, data->size() - offset, 0,
                            (struct sockaddr *)&server_addr, sizeof(sockaddr_in));
        } break;

        default:
            return ::write(fd->getFd(), sendData + offset, data->size() - offset);
            break;
    }
    return -1;
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

} // namespace obotcha