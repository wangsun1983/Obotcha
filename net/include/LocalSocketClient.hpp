#ifndef __LOCAL_SOCKET_SERVER_HPP__
#define __LOCAL_SOCKET_SERVER_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <mqueue.h>
#include <fstream>
#include <sys/un.h>


#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ByteArray.hpp"
#include "ArrayList.hpp"
#include "SocketListener.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(LocalSocketClient) {

public:

    _LocalSocketClient(String domain,SocketListener listener);

    void start();

    void send(ByteArray);

private:

    bool init();

    void addfd(int epollfd, int fd, bool enable_et);

    int sock;

    int epfd;

    struct sockaddr_un serverAddr;

    SocketListener listener;

    String mDomain;

};


}
#endif
