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

AtomicInteger connectCount = createAtomicInteger(0);
AtomicInteger disconnectCount = createAtomicInteger(0);
AtomicInteger messageCount = createAtomicInteger(0);

DECLARE_SIMPLE_CLASS(MyWsListener) IMPLEMENTS(WebSocketListener) {
public:
    _MyWsListener() {
        
    }

    int onMessage(WebSocketLinker client,WebSocketFrame message) {
        messageCount->incrementAndGet();
        //String msg = message->getMessage();
        //printf("msg is %s \n",msg->toChars());
        return 0;
    }

    int onData(WebSocketLinker client,WebSocketFrame message) {
        return 0;
    }

    int onConnect(WebSocketLinker client) {
        connectCount->incrementAndGet();
        return 0;
    }

    int onDisconnect(WebSocketLinker client) {
        disconnectCount->incrementAndGet();
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

    WebSocketServer server = createWebSocketServer();
    InetAddress address = createInetAddress("192.168.1.9",1111);
    
    server->bind(address,"/mytest",l);
    server->start();

    sleep(100);
    printf("connectCount is %d,disconnectCount is %d,messageCount is %d \n",connectCount->get(),disconnectCount->get(),messageCount->get());
    sleep(1);
    
}
