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
#include "WebSocketServer.hpp"
#include "WebSocketClientManager.hpp"
#include "System.hpp"

namespace obotcha {


_WebSocketClientInfo::_WebSocketClientInfo(Socket sock) {
    mParser = nullptr;
    mComposer = nullptr;
    mHttpHeader = createHttpHeader();
    mDeflate = nullptr;
    mProtocols = nullptr;
    mContinueBuffer = nullptr;
    mWsVersion = -1;
    
    //isSend = createAtomicBoolean(true);
    //mSendMutex = createMutex();
    //mSendCond = createCondition();
    mSock = sock;
    mOutputStream = sock->getOutputStream();
}

void _WebSocketClientInfo::reset() {
    mHttpHeader->clear();
    mDeflate = nullptr;
    mProtocols = nullptr;
    mContinueBuffer = nullptr;
    //isSend = createAtomicBoolean(true);
}

//void _WebSocketClientInfo::enableSend() {
//    isSend = createAtomicBoolean(true);
//}

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


WebSocketBuffer _WebSocketClientInfo::getContinueBuffer() {
    return this->mContinueBuffer;
}

void _WebSocketClientInfo::setContinueBuffer(WebSocketBuffer c) {
    this->mContinueBuffer = c;
}

WebSocketBuffer _WebSocketClientInfo::getDefferedBuffer() {
    return mDefferedBuff;
}

void _WebSocketClientInfo::setDefferedBuffer(WebSocketBuffer buff) {
    mDefferedBuff = buff;
}

String _WebSocketClientInfo::getConnectUrl() {
    return mConnectUrl;
}

void _WebSocketClientInfo::setConnectUrl(String l) {
    mConnectUrl = l;
}

long _WebSocketClientInfo::_send(int type,ByteArray msg) {
    if(mSock != nullptr) {
        long size = 0;
        
        ArrayList<ByteArray> data = nullptr;

        switch(type) {
            case st(WebSocketProtocol)::OPCODE_TEXT:
                data = mComposer->genTextMessage(msg->toString());
                break;

            case st(WebSocketProtocol)::OPCODE_BINARY:
                data = mComposer->genBinaryMessage(msg);
                break;

            case st(WebSocketProtocol)::OPCODE_CONTROL_CLOSE:
                data = createArrayList<ByteArray>();
                data->add(mComposer->genCloseMessage(msg->toString()));
                break;
            
            case st(WebSocketProtocol)::OPCODE_CONTROL_PING:
                data = createArrayList<ByteArray>();
                data->add(mComposer->genPingMessage(msg->toString()));
                break;

            case st(WebSocketProtocol)::OPCODE_CONTROL_PONG:
                data = createArrayList<ByteArray>();
                data->add(mComposer->genPongMessage(msg->toString()));
                break;

            default:
                throw ProtocolNotSupportException("WebSocketClientInfo not support OPCODE");
        }
        
        ListIterator<ByteArray> iterator = data->getIterator();
        while(iterator->hasValue()) {
            ByteArray sendData = iterator->getValue();
            //size += send(mClientFd,sendData->toValue(),sendData->size(),0);
            //size += _syncsend(sendData);
            size += mOutputStream->write(sendData);
            iterator->next();
        }

        return size;
    }

    return -1;
}

long _WebSocketClientInfo::sendBinaryMessage(ByteArray data) {
    return _send(st(WebSocketProtocol)::OPCODE_BINARY,data);
}

long _WebSocketClientInfo::sendTextMessage(String data) {
    return _send(st(WebSocketProtocol)::OPCODE_TEXT,createByteArray(data));
}

long _WebSocketClientInfo::sendPingMessage(ByteArray data) {
    return _send(st(WebSocketProtocol)::OPCODE_CONTROL_PING,data);
}

long _WebSocketClientInfo::sendPongMessage(ByteArray data) {
    return _send(st(WebSocketProtocol)::OPCODE_CONTROL_PONG,data);
}

long _WebSocketClientInfo::sendCloseMessage(ByteArray data) {
    return _send(st(WebSocketProtocol)::OPCODE_CONTROL_CLOSE,data);
}

int _WebSocketClientInfo::getVersion() {
    return mWsVersion;
}

void _WebSocketClientInfo::setVersion(int ver) {
    mWsVersion = ver;
}

Socket _WebSocketClientInfo::getSocket() {
    return mSock;
}

}

