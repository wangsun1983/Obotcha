#include "SocketPacket.hpp"

#include <memory.h>

namespace obotcha {

_SocketPacket::_SocketPacket(char *data,int size) {
    sockdata = (char *)malloc(size);
    memset(sockdata,0,size);
    memcpy(sockdata,data,size);
}

char *_SocketPacket::data() {
    return sockdata;
}

int _SocketPacket::size() {
    return socksize;
}

_SocketPacket::~_SocketPacket() {
    if(sockdata != nullptr) {
        free(sockdata);
    }
}

}