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

DECLARE_SIMPLE_CLASS(MyListener) IMPLEMENTS(SocketListener) {
public:
        
    void onDataReceived(SocketResponser r,ByteArray pack) {

    }

    void onDisconnect(SocketResponser r) {

    }

    void onConnect(SocketResponser r) {
        printf("on connect fd is %d \n",r->getFd());
    }

    void onTimeout() {

    }
};

int main() {
  MyListener listener = createMyListener();
  //TcpServer server = createTcpServer(1212,listener);
  TcpServer server = createTcpServer(1992,listener);
  server->start();
  while(1) {
    sleep(1000);
    //printf("star read \n");
    //ByteArray data = server->recv();
    //if(data != nullptr) {
    //    printf("data is %s \n",data->toString()->toChars());
    //} else {
    //    printf("no data \n");
    //}
  }
}