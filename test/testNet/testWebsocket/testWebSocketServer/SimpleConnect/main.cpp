#include <stdio.h>
#include <unistd.h>

#include "Integer.hpp"
#include "StrongPointer.hpp"
#include "Long.hpp"
#include "WebSocketServer.hpp"
#include "WebSocketListener.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"
#include "AutoLock.hpp"
#include "WebSocketProtocol.hpp"
#include "WebSocketComposer.hpp"
#include "File.hpp"
#include "FileOutputStream.hpp"
#include "AtomicInteger.hpp"


using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyWsListener) IMPLEMENTS(WebSocketListener) {
public:
    _MyWsListener() {
        
    }

    int onData(WebSocketFrame message,sp<_WebSocketLinker> client) {
        //String msg = message->getMessage();
        //printf("msg is %s \n",msg->toChars());
        ByteArray data = message->getData();
        printf("path is %s ,msg is %s \n",client->getPath()->toChars(),data->toString()->toChars());
        return 0;
    }

    int onConnect(WebSocketLinker client) {
        //connectCount->incrementAndGet();
        printf("on connect");
        return 0;
    }

    int onDisconnect(WebSocketLinker client) {
        printf("on disconnect");
        return 0;
    }

    int onPong(WebSocketLinker client) {
        return 0;
    }

    int onPing(WebSocketLinker client) {
        return 0;
    }   
};



int main() {
    MyWsListener l = createMyWsListener();

    
    InetAddress address = createInetAddress(1114);
    WebSocketServer server = createWebSocketServer(address);

    server->bind("mytest",l);
    server->bind("mytest2",l);
    server->start();

    while(1) {sleep(100);}
    
}
