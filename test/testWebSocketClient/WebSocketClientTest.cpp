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
#include "NetUtils.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyWsListener) IMPLEMENTS(WebSocketListener) {
public:    
    int onMessage(WebSocketClientInfo client,String message) {
        printf("message is %s \n",message->toChars());
        return 0;
    }

    int onData(WebSocketClientInfo client,ByteArray data) {
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

    int onPong(WebSocketClientInfo client,String) {
        return 0;
    }

    int onPing(WebSocketClientInfo client,String) {
        return 0;
    }
};



int main() {
    MyWsListener l = createMyWsListener();

    WebSocketClient client = createWebSocketClient(13);
    client->connect("ws://192.168.43.90:1111/mytest",l);
    //server->start();

    sleep(5);

    WebSocketClientInfo info = client->getClientInfo();
    ArrayList<ByteArray> contents = info->getComposer()->genTextMessage(info,createString("hello world1"));
    ByteArray content = contents->get(0);
    int clientFd = info->getClientFd();
    printf("clientFd is %d,content size is %d  \n",clientFd,content->size());

    for(int i = 0;i<content->size();i++) {
        ByteArray data = createByteArray(1);
        data->fill(0,content->at(i));
        st(NetUtils)::sendTcpPacket(info->getClientFd(),data);
        //sleep(5);
    }


    //client->sendMessage(createString("hello world1"));
    //sleep(5);
    //client->sendMessage(createString("hello world2"));

#if 0
    printf("start send file ..... \n");
    sleep(5);
    File file = createFile("log");
    FileInputStream stream = createFileInputStream(file);
    stream->open();
    ByteArray content = stream->readAll();
    client->sendBinaryData(content);
#endif

    while(1){}

}
