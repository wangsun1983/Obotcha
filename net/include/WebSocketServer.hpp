#ifndef __WEBSOCKET_SERVER_HPP__
#define __WEBSOCKET_SERVER_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <netinet/in.h>
#include <mqueue.h>
#include <fstream>
#include <sys/un.h>


#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "SocketListener.hpp"
#include "Mutex.hpp"
#include "Pipe.hpp"
#include "AtomicInteger.hpp"
#include "Thread.hpp"
#include "TcpServer.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(WebSocketServer) {
public:
    _WebSocketServer();
    void bind(String ip,int port,String path);
    void bind(int port,String path);
    void start();

private:
    String mPath;
    //TcpServer mServer;
};


}
#endif
