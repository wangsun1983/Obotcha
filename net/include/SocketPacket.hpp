#ifndef __SOCKET_PACKET_HPP__
#define __SOCKET_PACKET_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(SocketPacket) {
public:
    _SocketPacket(char *data,int size);

    char *data();

    int size();

    ~_SocketPacket();
    
private:
    char *sockdata;
    int socksize;    

};

}
#endif
