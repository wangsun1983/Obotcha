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

using namespace obotcha;

DECLARE_CLASS(MyWsListener) IMPLEMENTS(WebSocketListener) {
public:
    _MyWsListener() {
        mMutex = createMutex();
        mConditaion = createCondition();
    }

    
    int onData(WebSocketFrame message,WebSocketLinker client) {
        printf("message is %s \n",message->getData()->toValue());
        //mMessage = message->getData();
        String response = createString("hello from server ");
        printf("message len is %d \n",response->size());
        ByteArray array = createByteArray(response);
        printf("array size is %d \n",array->size());
        //WebSocketFrameComposer mComposer = createWebSocketFrameComposer(false);
        
        //int ret = st(NetUtils)::sendTcpPacket(fd,mComposer->generateMessageFrame(st(WebSocketProtocol)::OPCODE_TEXT,createByteArray(response)));
        WebSocketComposer composer = client->getComposer();

        //ArrayList<ByteArray> text = composer->genTextMessage(client,createString("hello world from server"));
        //int ret = st(NetUtils)::sendTcpPacket(fd,text->get(0));
        sleep(1);
        int ret = client->sendTextMessage(createString("hello world from server"));
        printf("onMessage send result is %d \n",ret);
        mConditaion->notify();
        return 0;
    }

    int onConnect(WebSocketLinker client) {
        printf("on connect fd  \n");
        return 0;
    }

    int onDisconnect(WebSocketLinker client) {
        printf("on disconnect fd\n");
        return 0;
    }

    int onPong(WebSocketLinker client) {
        return 0;
    }

    int onPing(WebSocketLinker client) {
        return 0;
    }

    //String waitMessage() {
     //   AutoLock ll(mMutex);
    //    mConditaion->wait(mMutex);
    //    return mMessage;
    //}

private:
    Mutex mMutex;
    Condition mConditaion;
    //String mMessage;   
};



int main() {
    MyWsListener l = createMyWsListener();

    WebSocketServer server = createWebSocketServer();
    InetAddress address = createInetAddress("192.168.43.252",1234);
    
    server->bind(address,"/mytest",l);
    server->start();
    printf("websocket start trace1 \n");
    //l->waitMessage();
    printf("websocket start trace2 \n");

    while(1) {sleep(1);}
    server->close();
    printf("websocket start trace3 \n");

    
    printf("websocket start trace4 \n");
}
