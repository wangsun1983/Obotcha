#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "WebSocketFrame.hpp"
#include "ByteArrayReader.hpp"
#include "HttpHeader.hpp"
#include "WebSocketParser.hpp"
#include "WebSocketComposer.hpp"
#include "WebSocketClientInfo.hpp"
#include "WebSocketPermessageDeflate.hpp"
#include "NetUtils.hpp"

namespace obotcha {


_WebSocketClientInfo::_WebSocketClientInfo() {
    mParser = nullptr;
    mComposer = nullptr;
    mHttpHeader = createHttpHeader();
    mWsHeader = createWebSocketHeader();
    mDeflate = nullptr;
    mProtocols = nullptr;
    mClientFd = -1;
}

int _WebSocketClientInfo::getClientFd() {
    return this->mClientFd;
}

void _WebSocketClientInfo::setClientFd(int fd) {
    this->mClientFd = fd;
}


sp<_WebSocketParser> _WebSocketClientInfo::getParser() {
    return this->mParser;
}

void _WebSocketClientInfo::setParser(sp<_WebSocketParser> p) {
    this->mParser = p;
}

sp<_WebSocketComposer> _WebSocketClientInfo::getComposer() {
    return this->mComposer;
}

void _WebSocketClientInfo::setComposer(sp<_WebSocketComposer> p) {
    this->mComposer = p;
}

HttpHeader _WebSocketClientInfo::getHttpHeader() {
    return mHttpHeader;
}

void _WebSocketClientInfo::setHttpHeader(HttpHeader header) {
    mHttpHeader = header;
}

WebSocketHeader _WebSocketClientInfo::getWebSocketHeader() {
    return mWsHeader;
}

void _WebSocketClientInfo::setWebSocketHeader(WebSocketHeader header) {
    mWsHeader = header;
}

sp<_WebSocketPermessageDeflate> _WebSocketClientInfo::getDeflater() {
    return mDeflate;
}

void _WebSocketClientInfo::setDeflater(sp<_WebSocketPermessageDeflate> d) {
    mDeflate = d;
}

ArrayList<String> _WebSocketClientInfo::getProtocols() {
    return mProtocols;
}

void _WebSocketClientInfo::setProtocols(ArrayList<String> p) {
    mProtocols = p;
}

WebSocketContinueBuffer _WebSocketClientInfo::getContinueBuffer() {
    return this->mContinueBuffer;
}

void _WebSocketClientInfo::setContinueBuffer(WebSocketContinueBuffer c) {
    this->mContinueBuffer = c;
}

WebSocketEntireBuffer _WebSocketClientInfo::getEntireBuffer() {
    return this->mEntireBuffer;
}

void _WebSocketClientInfo::setEntireBuffer(WebSocketEntireBuffer c) {
    this->mEntireBuffer = c;
}

String _WebSocketClientInfo::getConnectUrl() {
    return mConnectUrl;
}

void _WebSocketClientInfo::setConnectUrl(String l) {
    mConnectUrl = l;
}

int _WebSocketClientInfo::sendMessage(ByteArray content) {
    if(mClientFd != -1) {
        printf("sendContent is %s \n",content->toString()->toChars());
        return st(NetUtils)::sendTcpPacket(mClientFd,content);
    }

    return -1;
}

}

