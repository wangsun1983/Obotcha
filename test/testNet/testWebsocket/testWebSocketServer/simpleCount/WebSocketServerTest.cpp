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
#include "CountDownLatch.hpp"
#include "WebSocketServerBuilder.hpp"

using namespace obotcha;

CountDownLatch latch = createCountDownLatch(1024*32);

AtomicInteger messageCount = createAtomicInteger(0);
AtomicInteger connectCount = createAtomicInteger(0);
AtomicInteger disconnectCount = createAtomicInteger(0);

DECLARE_CLASS(MyWsListener) IMPLEMENTS(WebSocketListener) {
public:
    _MyWsListener() {
        
    }

    int onData(WebSocketFrame message,sp<_WebSocketLinker> client) {
        messageCount->incrementAndGet();
        if(!message->getData()->toString()->equals("Hello, World")) {
            printf("---WebSocketServer Simple Count test10 [FAILED]--- \n");
        }
        return 0;
    }

    int onConnect(WebSocketLinker client) {
        //printf("onConnect \n");
        connectCount->incrementAndGet();
        return 0;
    }

    int onDisconnect(WebSocketLinker client) {
        disconnectCount->incrementAndGet();
        latch->countDown();
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

    InetAddress address = createInetAddress(1111);
    
    WebSocketServer server = createWebSocketServerBuilder()
                            ->setInetAddr(address)
                            ->addListener("mytest",l)
                            ->build();

    server->start();
    latch->await();
    server->close();
    if(connectCount->get() != 1024*32) {
        printf("---WebSocketServer Simple Count test1 [FAILED]---,connectCount is %d \n",connectCount->get());
    }

    if(disconnectCount->get() != 1024*32) {
        printf("---WebSocketServer Simple Count test2 [FAILED]---,disconnectCount is %d \n",disconnectCount->get());
    }

    if(messageCount->get() != 1024*32) {
        printf("---WebSocketServer Simple Count test3 [FAILED]---,messageCount is %d \n",messageCount->get());
    }

    printf("---WebSocketServer Simple Count test100 [OK]--- \n");
}
