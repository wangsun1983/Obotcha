#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Integer.hpp"
#include "StrongPointer.hpp"
#include "Long.hpp"
#include "WebSocketServer.hpp"
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
};



int main() {
    MyWsListener l = createMyWsListener();

    WebSocketServer server = createWebSocketServer();
    server->bind(1112,"mypar",l);
    server->start();


    while(1){}

}
