#ifndef __OBOTCHA_WEB_SOCKET_LINKER_HPP__
#define __OBOTCHA_WEB_SOCKET_LINKER_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "Socket.hpp"
#include "WebSocketComposer.hpp"
#include "WebSocketParser.hpp"
#include "WebSocketPermessageDeflate.hpp"
#include "WebSocketProtocol.hpp"
#include "WebSocketOutputWriter.hpp"
#include "WebSocketInputReader.hpp"
#include "WebSocketInspector.hpp"

namespace obotcha {

class _WebSocketListener;

DECLARE_CLASS(WebSocketLinker) {
public:
    _WebSocketLinker(int version,Socket sock);
    ~_WebSocketLinker() = default;
    
    WebSocketInputReader getInputReader();
    
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

    void setWebSocketKey(String);
    String getWebSocketKey();

    void setProtocols(ArrayList<String>);
    ArrayList<String> getProtocols();

    Socket getSocket();

    WebSocketInspector getInspector();

private:
    long _send(int type,ByteArray data);

    Socket mSock;
    
    OutputStream mOutputStream;

    sp<_WebSocketParser> mParser;

    //sp<_WebSocketComposer> mComposer;
    WebSocketOutputWriter mWriter;
    WebSocketInputReader mReader;

    sp<_WebSocketPermessageDeflate> mDeflate;

    sp<_WebSocketListener> mCallback;

    String mConnectUrl;

    String mKey;

    ArrayList<String> mProtocols;

    String mPath;

    int mWsVersion;

    WebSocketFrame mCloseFrame;

    WebSocketInspector mInspector;
};

}
#endif
