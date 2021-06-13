#ifndef __OBOTCHA_WEB_SOCKET_LINKER_HPP__
#define __OBOTCHA_WEB_SOCKET_LINKER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "ByteArrayReader.hpp"
#include "HttpHeader.hpp"
#include "ByteArray.hpp"
#include "ByteRingArray.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"
#include "AtomicBoolean.hpp"
#include "Socket.hpp"
#include "SocketOutputStream.hpp"
#include "WebSocketListener.hpp"

namespace obotcha {

class _WebSocketComposer;
class _WebSocketParser;
class _WebSocketPermessageDeflate;

DECLARE_SIMPLE_CLASS(WebSocketLinker) {
public:
    _WebSocketLinker(Socket sock);

    //Parser
    sp<_WebSocketParser> getParser();

    void setParser(sp<_WebSocketParser>);

    //Composer
    sp<_WebSocketComposer> getComposer();

    void setComposer(sp<_WebSocketComposer>);

    //PermessageDeflater
    sp<_WebSocketPermessageDeflate> getDeflater();

    void setDeflater(sp<_WebSocketPermessageDeflate>);

    //Listener
    void setWebSocketListener(sp<_WebSocketListener> l);
    sp<_WebSocketListener> getWebSocketListener();

    //Path
    void setPath(String);
    String getPath();
    
    //ConnectUrl
    String getConnectUrl();

    void setConnectUrl(String);

    long sendTextMessage(String);

    long sendBinaryMessage(ByteArray);

    long sendPingMessage(ByteArray);

    long sendPongMessage(ByteArray);

    long sendCloseMessage(ByteArray);

    int getVersion();

    void setVersion(int);

    void reset();

    void setWebSocketKey(String);
    String getWebSocketKey();

    void setProtocols(String);
    String getProtocols();

    Socket getSocket();

private:
    //int mClientFd;
    Socket mSock;
    
    OutputStream mOutputStream;

    sp<_WebSocketParser> mParser;

    sp<_WebSocketComposer> mComposer;

    sp<_WebSocketPermessageDeflate> mDeflate;

    sp<_WebSocketListener> mCallback;

    String mConnectUrl;

    String mKey;

    String mProtocols;

    String mPath;

    int mWsVersion;

    long _send(int type,ByteArray data);
};

}
#endif
