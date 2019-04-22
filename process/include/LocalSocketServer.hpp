#ifndef __LOCAL_SOCKET_SERVER_HPP__
#define __LOCAL_SOCKET_SERVER_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <mqueue.h>
#include <fstream>


#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ByteArray.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(LocalSocketServer) {
public:
    _LocalSocketServer(String domain);

    bool init();

    bool send(ByteArray data,int prio);

    bool send(ByteArray data);

    int receive(ByteArray buff);

private:
    String mDomain;

};

}
#endif
