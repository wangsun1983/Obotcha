#ifndef __OBOTCHA_WEB_SOCKET_CLIENT_INFO_HPP__
#define __OBOTCHA_WEB_SOCKET_CLIENT_INFO_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "WebSocketFrame.hpp"
#include "ByteArrayReader.hpp"
#include "HttpHeader.hpp"
#include "ByteArray.hpp"
#include "ByteRingArray.hpp"

namespace obotcha {

class _WebSocketComposer;
class _WebSocketParser;
class _WebSocketPermessageDeflate;

DECLARE_SIMPLE_CLASS(WebSocketContinueBuffer) {
public:
    ByteArray mBuffer;
    int mType;
};

DECLARE_SIMPLE_CLASS(WebSocketEntireBuffer) {
public:
    ByteArray mBuffer;

};

DECLARE_SIMPLE_CLASS(WebSocketClientInfo) {
public:
    _WebSocketClientInfo();

    //ClientFd
    int getClientFd();

    void setClientFd(int);

    //Parser
    sp<_WebSocketParser> getParser();

    void setParser(sp<_WebSocketParser>);

    //Composer
    sp<_WebSocketComposer> getComposer();

    void setComposer(sp<_WebSocketComposer>);

    //HttpHeader
    HttpHeader getHttpHeader();

    void setHttpHeader(HttpHeader);

    //WebSocketHeader
    WebSocketHeader getWebSocketHeader();

    void setWebSocketHeader(WebSocketHeader);

    //PermessageDeflater
    sp<_WebSocketPermessageDeflate> getDeflater();

    void setDeflater(sp<_WebSocketPermessageDeflate>);

    //Protocols
    ArrayList<String> getProtocols();

    void setProtocols(ArrayList<String>);

    //Continue Buffer
    WebSocketContinueBuffer getContinueBuffer();

    void setContinueBuffer(WebSocketContinueBuffer);

    //WebSocketEntireBuffer
    WebSocketEntireBuffer getEntireBuffer();

    void setEntireBuffer(WebSocketEntireBuffer);

    //ConnectUrl
    String getConnectUrl();

    void setConnectUrl(String);

    int sendTextMessage(String);

    int sendBinaryMessage(ByteArray);

    int sendPingMessage(ByteArray);

    int sendPongMessage(ByteArray);

    int sendCloseMessage(ByteArray);

private:
    int mClientFd;

    sp<_WebSocketParser> mParser;

    sp<_WebSocketComposer> mComposer;

    HttpHeader mHttpHeader;
        
    WebSocketHeader mWsHeader;

    sp<_WebSocketPermessageDeflate> mDeflate;

    ArrayList<String> mProtocols;

    WebSocketContinueBuffer mContinueBuffer;

    WebSocketEntireBuffer mEntireBuffer;

    String mConnectUrl;

    int _send(int type,ByteArray data);
};

}
#endif
