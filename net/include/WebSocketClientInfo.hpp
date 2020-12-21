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
#include "Random.hpp"
#include "WebSocketBuffer.hpp"
#include "Atomic.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"

namespace obotcha {

class _WebSocketComposer;
class _WebSocketParser;
class _WebSocketPermessageDeflate;

DECLARE_SIMPLE_CLASS(WebSocketClientInfo) {
public:
    _WebSocketClientInfo();

    //ClientFd
    int getClientFd();

    void setClientFd(int);

    uint64_t getClientId();

    //Parser
    sp<_WebSocketParser> getParser();

    void setParser(sp<_WebSocketParser>);

    //Composer
    sp<_WebSocketComposer> getComposer();

    void setComposer(sp<_WebSocketComposer>);

    //HttpHeader
    HttpHeader getHttpHeader();

    void setHttpHeader(HttpHeader);

    //PermessageDeflater
    sp<_WebSocketPermessageDeflate> getDeflater();

    void setDeflater(sp<_WebSocketPermessageDeflate>);

    //Protocols
    ArrayList<String> getProtocols();

    void setProtocols(ArrayList<String>);

    //Continue Buffer
    WebSocketBuffer getContinueBuffer();
    void setContinueBuffer(WebSocketBuffer);

    //DefferedBuffer
    WebSocketBuffer getDefferedBuffer();
    void setDefferedBuffer(WebSocketBuffer);

    //ConnectUrl
    String getConnectUrl();

    void setConnectUrl(String);

    int sendTextMessage(String);

    int sendBinaryMessage(ByteArray);

    int sendPingMessage(ByteArray);

    int sendPongMessage(ByteArray);

    int sendCloseMessage(ByteArray);

    int getVersion();

    void setVersion(int);

    void reset();

    void enableSend();

private:
    int mClientFd;

    sp<_WebSocketParser> mParser;

    sp<_WebSocketComposer> mComposer;

    HttpHeader mHttpHeader;
        
    //WebSocketHeader mWsHeader;

    sp<_WebSocketPermessageDeflate> mDeflate;

    ArrayList<String> mProtocols;

    WebSocketBuffer mDefferedBuff;
    WebSocketBuffer mContinueBuffer;

    String mConnectUrl;

    int mWsVersion;

    Random mRand;

    uint64_t mClientId;

    int _send(int type,ByteArray data);
    int _syncsend(ByteArray data);

    Atomic<bool> isSend;
    Mutex mSendMutex;
    Condition mSendCond;
};

}
#endif
