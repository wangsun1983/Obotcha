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
#include "WsServerListener.hpp"
#include "JsonReader.hpp"
#include "WsCommands.hpp"
#include "Atomic.hpp"

using namespace obotcha;

_WsServerListener::_WsServerListener() {
    mConnectCounts = 0;
    mDisconnectCounts = 0;
    mRcvDataSize = 0;
}

int _WsServerListener::onMessage(sp<_WebSocketClientInfo> client,WebSocketFrame frame) {
    String message = frame->getMessage();
    if(message != nullptr) {
        //printf("message is %s \n",message->toChars());
        JsonReader reader = createJsonReader(message);
        JsonValue value = reader->get();
        //printf("value size is %d \n",value->size());
        Integer req = value->getInteger("command");
        if(req == nullptr) {
            return 0;
        }

        switch(req->toValue()) {
            case st(WsCommands)::RequestClearRecords: {
                mConnectCounts = 0;
                mDisconnectCounts = 0;
                mRcvDataSize = 0;
                break;
            }

            case st(WsCommands)::RequestStatistics: {
                JsonValue response = createJsonValue();
                response->put(createString("command"),st(WsCommands)::ResponseStatistics);
                response->put(createString("connectsum"),mConnectCounts->get());
                response->put(createString("disconnectsum"),mDisconnectCounts->get());
                response->put(createString("recvsum"),(uint64_t)mRcvDataSize->get());
                client->sendTextMessage(response->toString());
                break;
            }

            case st(WsCommands)::RequestReply: {
                String msg = value->getString("msg");
                JsonValue response = createJsonValue();
                response->put(createString("rep"),st(WsCommands)::ResponseReply);
                response->put(createString("reply"),msg);
                client->sendTextMessage(response->toString());
                break;
            }
        }
    }
    return 0;
}

int _WsServerListener::onData(sp<_WebSocketClientInfo> client,WebSocketFrame data) {
    
}

int _WsServerListener::onConnect(sp<_WebSocketClientInfo> client) {
    //printf("wangsl,get an onConnect message,fd is %d \n",client->getClientFd());
    //mConnectCounts->incrementAndGet();
    mConnectCounts++;
}

int _WsServerListener::onDisconnect(sp<_WebSocketClientInfo> client) {
    //printf("wangsl,get an onDisConnect message \n");
    //printf("wangsl,get an disonConnect message,fd is %d \n",client->getClientFd());
    //mDisconnectCounts->incrementAndGet();
    mDisconnectCounts++;
}

int _WsServerListener::onPong(sp<_WebSocketClientInfo> client,String) {
    return PingResultResponse;
}

int _WsServerListener::onPing(sp<_WebSocketClientInfo> client,String) {
    return PingResultResponse;
}