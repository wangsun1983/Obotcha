#ifndef __OBOTCHA_WEB_SOCKET_LINKER_HPP__
#define __OBOTCHA_WEB_SOCKET_LINKER_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "Socket.hpp"
#include "WebSocketComposer.hpp"
#include "WebSocketParser.hpp"
#include "WebSocketPermessageDeflate.hpp"
#include "WebSocketProtocol.hpp"

namespace obotcha {

class _WebSocketListener;

DECLARE_CLASS(WebSocketLinker) {
public:
    _WebSocketLinker(Socket sock);
    ~_WebSocketLinker();
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

    long sendCloseMessage(int status = st(WebSocketProtocol)::CLOSE_STATUS_NORMAL,
                          ByteArray extraInfo = nullptr);

    int getVersion();

    void setVersion(int);

    void reset();

    void setWebSocketKey(String);
    String getWebSocketKey();

    void setProtocols(ArrayList<String>);
    ArrayList<String> getProtocols();

    Socket getSocket();

private:
    long _send(int type,ByteArray data);

    Socket mSock;
    
    OutputStream mOutputStream;

    sp<_WebSocketParser> mParser;

    sp<_WebSocketComposer> mComposer;

    sp<_WebSocketPermessageDeflate> mDeflate;

    sp<_WebSocketListener> mCallback;

    String mConnectUrl;

    String mKey;

    ArrayList<String> mProtocols;

    String mPath;

    int mWsVersion;

    WebSocketFrame mCloseFrame;
};

}
#endif
