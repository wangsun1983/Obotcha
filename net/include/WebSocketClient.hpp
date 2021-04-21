#ifndef __OBOTCHA_WEBSOCKET_CLIENT_HPP__
#define __OBOTCHA_WEBSOCKET_CLIENT_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <netinet/in.h>
#include <mqueue.h>
#include <fstream>
#include <sys/un.h>


#include "Object.hpp"
#include "StrongPointer.hpp"

#include "WebSocketListener.hpp"
#include "Mutex.hpp"
#include "WebSocketParser.hpp"
#include "WebSocketHybi13Parser.hpp"
#include "WebSocketComposer.hpp"
#include "WebSocketListener.hpp"
#include "HttpOption.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(WebSocketClient) {
public:
    _WebSocketClient(int version);
    
    void updateMask(bool);

    int connect(String url,WebSocketListener l,HttpOption option);

    int sendTextMessage(String msg);

    int sendTextMessage(const char*msg);

    int sendPingMessage(ByteArray msg);

    int sendCloseMessage(ByteArray msg);

    int sendBinaryData(ByteArray data);

    int sendFile(File);

    WebSocketClientInfo getClientInfo();

private:

    int mVersion;

    WebSocketListener mWsListener;

    HttpOption mHttpOption;
};


}
#endif
