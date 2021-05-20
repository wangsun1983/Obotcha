#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Integer.hpp"
#include "StrongPointer.hpp"
#include "Long.hpp"
#include "WebSocketClient.hpp"
#include "WebSocketListener.hpp"
#include "File.hpp"
#include "FileInputStream.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyWsListener) IMPLEMENTS(WebSocketListener) {
public:    

    int onData(WebSocketFrame data,WebSocketLinker client) {
        if(data->getData() != nullptr) {
            printf("ondata is %s \n",data->getData()->toValue());
        }
        return 0;
    }

    int onConnect(WebSocketLinker client) {
        printf("on connect fd \n");
        return 0;
    }

    int onDisconnect(WebSocketLinker client) {
        printf("111111 on disconnect fd \n");
        return 0;
    }

    int onPong(String,WebSocketLinker client) {
        printf("111111 onPong fd \n");
        return 0;
    }

    int onPing(String,WebSocketLinker client) {
        printf("111111 onPing fd \n");
        return 0;
    }
};



int main() {
    MyWsListener l = createMyWsListener();

    WebSocketClient client = createWebSocketClient(13);
    client->connect(createString("ws://192.168.43.51:1111"),l);
    
    client->sendTextMessage(createString("a"));

    while(1){sleep(1);}

}
