#include "SocketOutputStream.hpp"
#include "InetAddress.hpp"
#include "Socket.hpp"

namespace obotcha {

_SocketOutputStream::_SocketOutputStream(sp<_Socket> s) {
    mSocket = s;
    if (mSocket->getType() == st(Socket)::Udp) {
        auto address = s->getInetAddress();

        switch(address->getType()) {
            case st(InetAddress)::IPV4: {
                server_addr.sin_family = AF_INET;
                server_addr.sin_port = htons(address->getPort());

                if (address != nullptr) {
                    server_addr.sin_addr.s_addr =
                        inet_addr(address->getAddress()->toChars());
                } else {
                    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
                }
            }
            break;

            case st(InetAddress)::IPV6: {
                server_addr_v6.sin6_family = AF_INET6;
                server_addr_v6.sin6_port = htons(s->getInetAddress()->getPort());
                if (address->getAddress() != nullptr) {
                    printf("socket output stream addr is %s \n",address->getAddress()->toChars());
                    inet_pton(AF_INET6, address->getAddress()->toChars(), &server_addr_v6.sin6_addr);
                } else {
                    server_addr_v6.sin6_addr = in6addr_any;
                }
            }
            break;
        }
    }
    
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
    if (mSocket == nullptr || mSocket->isClosed()) {
        return -1;
    }

    byte *sendData = data->toValue();
    switch (mSocket->getType()) {
        case st(Socket)::Udp: {
            struct sockaddr * addr = nullptr;
            int length = 0;

            switch(mSocket->getInetAddress()->getType()) {
                case st(InetAddress)::IPV4: {
                    addr = (sockaddr *)&server_addr;
                    length = sizeof(server_addr);
                }
                break;

                case st(InetAddress)::IPV6: {
                    addr = (sockaddr *)&server_addr_v6;
                    length = sizeof(server_addr_v6);
                }
                break;
            }

            return ::sendto(fd->getFd(), data->toValue() + offset, data->size() - offset, 0,
                            addr, length);
        }
        break;

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