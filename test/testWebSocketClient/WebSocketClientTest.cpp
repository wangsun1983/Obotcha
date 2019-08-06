#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Integer.hpp"
#include "StrongPointer.hpp"
#include "Long.hpp"
#include "WebSocketServer.hpp"
#include "WebSocketClient.hpp"
#include "WebSocketListener.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyWsListener) IMPLEMENTS(WebSocketListener) {
public:    
    int onMessage(int fd,String message) {
        printf("message is %s \n",message->toChars());
        return 0;
    }

    int onConnect(int fd) {
        printf("on connect fd is %d \n",fd);
        return 0;
    }

    int onDisconnect(int fd) {
        printf("on disconnect fd is %d \n",fd);
        return 0;
    }

    int onPong(int fd) {
        return 0;
    }

    int onPing(int fd) {
        return 0;
    }
};



int main() {
    MyWsListener l = createMyWsListener();

    WebSocketClient client = createWebSocketClient();
    client->bind("ws://192.168.43.90:1111/mytest",l);
    //server->start();

    sleep(5);
    client->sendMessage(createString("hello world1"));
    sleep(5);
    client->sendMessage(createString("hello world2"));
    sleep(5);
    client->sendPing(createString("wangsl12312312312312312312ping!!!!"));
    while(1){}

}
