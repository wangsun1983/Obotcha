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
#include "WebSocketProtocol.hpp"
#include "ProtocolNotSupportException.hpp"
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

int _WebSocketClientInfo::_send(int type,ByteArray msg) {
    if(mClientFd != -1) {
        WebSocketClientInfo info;
        info.set_pointer(this);
        int size = 0;
        
        ArrayList<ByteArray> data = nullptr;

        switch(type) {
            case st(WebSocketProtocol)::OPCODE_TEXT:
                data = mComposer->genTextMessage(info,msg->toString());
                break;

            case st(WebSocketProtocol)::OPCODE_BINARY:
                data = mComposer->genBinaryMessage(info,msg);
                break;

            case st(WebSocketProtocol)::OPCODE_CONTROL_CLOSE:
                data = createArrayList<ByteArray>();
                data->add(mComposer->genCloseMessage(info,msg->toString()));
                break;
            
            case st(WebSocketProtocol)::OPCODE_CONTROL_PING:
                data = createArrayList<ByteArray>();
                data->add(mComposer->genPingMessage(info,msg->toString()));
                break;

            case st(WebSocketProtocol)::OPCODE_CONTROL_PONG:
                data = createArrayList<ByteArray>();
                data->add(mComposer->genPongMessage(info,msg->toString()));
                break;

            default:
                throw createProtocolNotSupportException("WebSocketClientInfo not support OPCODE");
        }
        
        ListIterator<ByteArray> iterator = data->getIterator();
        while(iterator->hasValue()) {
            ByteArray sendData = iterator->getValue();
            size += st(NetUtils)::sendTcpPacket(mClientFd,sendData);
            iterator->next();
        }

        return size;
    }

    return -1;
}

int _WebSocketClientInfo::sendBinaryMessage(ByteArray data) {
    return _send(st(WebSocketProtocol)::OPCODE_BINARY,data);
}

int _WebSocketClientInfo::sendTextMessage(String data) {
    return _send(st(WebSocketProtocol)::OPCODE_TEXT,createByteArray(data));
}

int _WebSocketClientInfo::sendPingMessage(ByteArray data) {
    return _send(st(WebSocketProtocol)::OPCODE_CONTROL_PING,data);
}

int _WebSocketClientInfo::sendPongMessage(ByteArray data) {
    return _send(st(WebSocketProtocol)::OPCODE_CONTROL_PONG,data);
}

int _WebSocketClientInfo::sendCloseMessage(ByteArray data) {
    return _send(st(WebSocketProtocol)::OPCODE_CONTROL_CLOSE,data);
}

}

