
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "TcpClient.hpp"
#include "Thread.hpp"
#include "System.hpp"
#include "TcpServer.hpp"
#include "InitializeException.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyAVCSocketListener) IMPLEMENTS(SocketListener) {
public:
    void onDataReceived(SocketResponser r,ByteArray pack){
        if(pack != nullptr) {
          printf("pack is %s \n",pack->toString()->toChars());
        }
        //String hello = createString("hello server123");
        //st(NetUtils)::sendTcpPacket(fd,createByteArray(hello));
    }

    void onDisconnect(SocketResponser r) {

    }

    void onConnect(SocketResponser r){

    }

    void onTimeout(){

    }
};

int testTcpClient() {
    MyAVCSocketListener listener = createMyAVCSocketListener();
    printf("test1 \n");
    TcpClient client = createTcpClient("192.168.1.4",1234,-1,listener);
    client->doConnect();
    printf("test2 \n");
    String hello = createString("hello server");
    printf("test2_1 \n");
    client->doSend(createByteArray(hello));
    printf("test3 \n");
    sleep(10);
    return 0;
}
