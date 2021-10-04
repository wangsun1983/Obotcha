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

AtomicInteger connectCount = createAtomicInteger(0);
AtomicInteger disconnectCount = createAtomicInteger(0);
AtomicInteger messageCount = createAtomicInteger(0);
CountDownLatch latch = createCountDownLatch(1024*12);

DECLARE_CLASS(MyWsListener) IMPLEMENTS(WebSocketListener) {
public:
    _MyWsListener() {
        
    }

    int onData(WebSocketFrame message,WebSocketLinker client) {
        messageCount->incrementAndGet();

        if(!message->getData()->toString()->equals("Hello, World")) {
            printf("---WebSocketServer MultiThread test2 [FAILED]---,message is %s \n",message->getData()->toString()->toChars());
        }
        return 0;
    }

    int onConnect(WebSocketLinker client) {
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

    if(connectCount->get() != 12*1024 || disconnectCount->get() != 12*1024 || messageCount->get() != 12*1024) {
        printf("---WebSocketServer MultiThread test1 [FAILED]---,connect is %d,disconnect is %d,message is %d \n",
                connectCount->get(),
                disconnectCount->get(),
                messageCount->get());
    }
    printf("---WebSocketServer MultiThread test100 [OK]--- \n");
}
