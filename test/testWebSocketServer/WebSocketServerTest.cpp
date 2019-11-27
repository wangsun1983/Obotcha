#include <stdio.h>
#include <unistd.h>

#include "Integer.hpp"
#include "StrongPointer.hpp"
#include "Long.hpp"
#include "WebSocketServer.hpp"
#include "WebSocketListener.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"
#include "AutoMutex.hpp"
#include "NetUtils.hpp"
#include "WebSocketFrameComposer.hpp"
#include "WebSocketProtocol.hpp"
#include "WebSocketComposer.hpp"
#include "File.hpp"
#include "FileOutputStream.hpp"

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
        String response = createString("hello from server ");
        printf("message len is %d \n",response->size());
        ByteArray array = createByteArray(response);
        printf("array size is %d \n",array->size());
        WebSocketFrameComposer mComposer = createWebSocketFrameComposer(false);
        
        //int ret = st(NetUtils)::sendTcpPacket(fd,mComposer->generateMessageFrame(st(WebSocketProtocol)::OPCODE_TEXT,createByteArray(response)));
        WebSocketComposer composer = st(WebSocketClientManager)::getInstance()->getClient(fd)->mComposer;

        String text = composer->genTextMessage(st(WebSocketClientManager)::getInstance()->getClient(fd),createString("hello world from server"));
        int ret = st(NetUtils)::sendTcpPacket(fd,createByteArray(text));
        printf("onMessage send result is %d \n",ret);
        mConditaion->notify();
        return 0;
    }

    int onData(int fd,ByteArray message) {
        //printf("data message size is %d,message is %s \n",message->size(),message->toValue());
        File file = createFile("recvfile");
        FileOutputStream stream = createFileOutputStream(file);
        stream->open(FileOpenType::Trunc);
        stream->write(message);
        stream->flush();
        stream->close();
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

    while(1) {sleep(1);}
    server->release();
    printf("websocket start trace3 \n");

    
    printf("websocket start trace4 \n");
}
