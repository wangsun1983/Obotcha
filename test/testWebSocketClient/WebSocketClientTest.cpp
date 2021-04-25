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

    int onData(WebSocketFrame data,WebSocketClientInfo client) {
        if(data->getData() != nullptr) {
            printf("ondata is %s \n",data->getData()->toValue());
        }
        return 0;
    }

    int onConnect(WebSocketClientInfo client) {
        printf("on connect fd \n");
        return 0;
    }

    int onDisconnect(WebSocketClientInfo client) {
        printf("111111 on disconnect fd \n");
        return 0;
    }

    int onPong(String,WebSocketClientInfo client) {
        return 0;
    }

    int onPing(String,WebSocketClientInfo client) {
        return 0;
    }
};



int main() {
    MyWsListener l = createMyWsListener();

    WebSocketClient client = createWebSocketClient(13);
    client->connect(createString("ws://192.168.1.6:1111/mytest"),l);
    
    client->sendTextMessage(createString("hello server"));

    while(1){sleep(1);}

}
