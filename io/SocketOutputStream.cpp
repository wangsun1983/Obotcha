#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>  
#include <arpa/inet.h>
#include <functional>

#include "SocketOutputStream.hpp"
#include "Socket.hpp"
#include "InetAddress.hpp"


namespace obotcha {

_SocketOutputStream::_SocketOutputStream(sp<_Socket> s) {
    mSocket = s;
    if(mSocket->getType() == st(Socket)::Udp) {
        server_addr.sin_family = AF_INET;
        InetAddress address = s->getInetAddress();
        server_addr.sin_port = htons(address->getPort());      
        
        if(address->getAddress() != nullptr) {
            server_addr.sin_addr.s_addr = inet_addr(address->getAddress()->toChars());
        } else {
            server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        }
    }

    if(s->getFileDescriptor()->isAsync()) {
        mChannel = createAsyncOutputChannel(s->getFileDescriptor(),
                                            std::bind(&_SocketOutputStream::_write,this,std::placeholders::_1,std::placeholders::_2));
    }
}

long _SocketOutputStream::write(char c) {
    ByteArray data = createByteArray(1);
    data[0] = c;
    return write(data,1);
}

long _SocketOutputStream::write(ByteArray data) {
    if(mChannel != nullptr) {
        mChannel->write(data);
        return data->size();
    }
    return _write(mSocket->getFileDescriptor(),data);
}

long _SocketOutputStream::write(ByteArray data,int start) {
    return this->write(data,start,data->size() - 1);
}

long _SocketOutputStream::write(ByteArray data,int start,int len) {
    ByteArray senddata = createByteArray(&data->toValue()[start],len);
    if(mChannel != nullptr) {
        mChannel->write(senddata);
        return senddata->size();
    }
    return _write(mSocket->getFileDescriptor(),senddata);
}


long _SocketOutputStream::_write(FileDescriptor fd,ByteArray data) {
    byte *sendData = data->toValue();
    if(mSocket == nullptr || mSocket->isClosed()) {
        return -1;
    }
    
    switch(mSocket->getType()) {
        case st(Socket)::Udp: {
            return ::sendto(fd->getFd(), data->toValue(), data->size(), 0, (struct sockaddr *)&server_addr, sizeof(sockaddr_in));
        }
        break;

        default:
            return ::write(fd->getFd(),sendData,data->size());
        break;
    }
    return -1;
}

void _SocketOutputStream::close() {
    mSocket = nullptr;
    if(mChannel != nullptr) {
        mChannel->close();
    }

}

void _SocketOutputStream::flush() {
    //TODO
}


}