#include "TcpServer.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Thread.hpp"
#include "NetUtils.hpp"
#include "InitializeException.hpp"
#include "FileOutputStream.hpp"
#include "File.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"
#include "System.hpp"
#include "TcpServer.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyListener) IMPLEMENTS(SocketListener) {
public:
    void onAccept(int fd,String ip,int port,ByteArray pack) {
        if(pack != nullptr) {
            printf("pack is %s \n",pack->toString()->toChars());
        }

        
    }

    void onDisconnect(int fd) {

    }

    void onConnect(int fd,String ip,int port) {

    }

    void onConnect(int fd,String domain) {

    }

    void onTimeout() {

    }
};

int main() {
  MyListener listener = createMyListener();
  //TcpServer server = createTcpServer(1212,listener);
  TcpServer server = createTcpServer(1212);
  server->start();
  while(1) {
    printf("star read \n");
    ByteArray data = server->recv();
    if(data != nullptr) {
        printf("data is %s \n",data->toString()->toChars());
    } else {
        printf("no data \n");
    }
  }
}