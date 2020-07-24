
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "TcpClient.hpp"
#include "Thread.hpp"
#include "System.hpp"
#include "TcpServer.hpp"
#include "NetUtils.hpp"
#include "InitializeException.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyAVCSocketListener) IMPLEMENTS(SocketListener) {
public:
    void onAccept(int fd,String ip,int port,ByteArray pack){
        if(pack != nullptr) {
          printf("pack is %s \n",pack->toString()->toChars());
        }
        String hello = createString("hello server123");
        st(NetUtils)::sendTcpPacket(fd,createByteArray(hello));
    }

    void onDisconnect(int fd) {

    }

    void onConnect(int fd,String ip,int port){

    }

    void onConnect(int fd,String domain){

    }

    void onTimeout(){

    }
};

int main() {
    MyAVCSocketListener listener = createMyAVCSocketListener();
    printf("test1 \n");
    TcpClient client = createTcpClient("192.168.1.4",9999,-1,listener);
    client->doConnect();
    printf("test2 \n");
    String hello = createString("hello server");
    printf("test2_1 \n");
    client->doSend(createByteArray(hello));
    printf("test3 \n");
    while(1) {
        sleep(1);  
    }
    
}
