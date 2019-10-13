#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Integer.hpp"
#include "StrongPointer.hpp"
#include "Long.hpp"
#include "WebSocketServer.hpp"
#include "WebSocketListener.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"
#include "AutoMutex.hpp"

using namespace obotcha;



DECLARE_SIMPLE_CLASS(MyWsListener) IMPLEMENTS(WebSocketListener) {
public:
    _MyWsListener() {
        mMutex = createMutex();
        mConditaion = createCondition();
    }

    int onMessage(int fd,String message) {
        printf("message is %s \n",message->toChars());
        mMessage = message;
        mConditaion->notify();
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

    String waitMessage() {
        AutoMutex ll(mMutex);
        mConditaion->wait(mMutex);
        return mMessage;
    }

private:
    Mutex mMutex;
    Condition mConditaion;
    String mMessage;   
};



int main() {
    MyWsListener l = createMyWsListener();

    WebSocketServer server = createWebSocketServer();
    server->bind(1111,"/mytest",l);
    server->start();
    printf("websocket start trace1 \n");
    l->waitMessage();
    printf("websocket start trace2 \n");

    server->release();
    printf("websocket start trace3 \n");

    sleep(5);
    printf("websocket start trace4 \n");
}
