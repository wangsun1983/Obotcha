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
#include "WebSocketComposer.hpp"
#include "WebSocketListener.hpp"
#include "HttpOption.hpp"
#include "SocketMonitor.hpp"
#include "OutputStream.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(WebSocketClient) IMPLEMENTS(SocketListener){
public:
    _WebSocketClient(int version = 13);
    
    void updateMask(bool);

    int connect(String url,WebSocketListener l,HttpOption option = nullptr);

    int sendTextMessage(String msg);

    int sendTextMessage(const char*msg);

    int sendPingMessage(String msg);

    int sendPongMessage(String msg);

    int sendCloseMessage(String msg);

    int sendBinaryData(ByteArray data);

    int sendFile(File);

    void close();

private:
    int _send(ArrayList<ByteArray>);
    int _send(ByteArray);
    
    void onSocketMessage(int,Socket,ByteArray);

    int mVersion;

    WebSocketListener mWsListener;

    HttpOption mHttpOption;

    SocketMonitor mSocketMonitor;

    WebSocketParser parser;
    WebSocketComposer composer;

    OutputStream mOutputStream;
    Socket mSocket;
    
};


}
#endif
