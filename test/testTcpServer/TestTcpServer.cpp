#include "TcpServer.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Thread.hpp"
#include "InitializeException.hpp"
#include "FileOutputStream.hpp"
#include "File.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"
#include "System.hpp"
#include "TcpServer.hpp"

using namespace obotcha;

/*
sudo ufw disable
*/

//client should use 8 thread to send data
DECLARE_SIMPLE_CLASS(MyListener) IMPLEMENTS(SocketListener) {
public:
    _MyListener() {
        connectNum = 0;
        disconnectNum = 0;
        dataLength = 0;
    }

    void onDataReceived(SocketResponser r,ByteArray pack) {
        //printf("pack is %s \n",pack->toString()->toChars());
        dataLength += pack->size();
    }

    void onDisconnect(SocketResponser r) {
        //printf("onDisconnect \n");
        disconnectNum++;
    }

    void onConnect(SocketResponser r) {
        //printf("onConnect \n");
        connectNum++;
    }

    void onTimeout() {

    }

public:
    Atomic<int> connectNum;
    Atomic<int> disconnectNum;
    Atomic<long> dataLength;    
};

int normaltest() {
  MyListener listener = createMyListener();
  TcpServer server = createTcpServer(1992,listener);
  server->start();
  sleep(30);
  printf("connectNum is %d,disconnectNum is %d,dataLength is %ld \n",listener->connectNum->get(),listener->disconnectNum->get(),listener->dataLength->get());
  return 0;
}