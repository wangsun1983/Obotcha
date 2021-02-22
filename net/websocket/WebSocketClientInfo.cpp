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


_WebSocketClientInfo::_WebSocketClientInfo() {
    mParser = nullptr;
    mComposer = nullptr;
    mHttpHeader = createHttpHeader();
    //mWsHeader = createWebSocketHeader();
    mDeflate = nullptr;
    mProtocols = nullptr;
    mContinueBuffer = nullptr;
    mClientFd = -1;
    mWsVersion = -1;
    //mRand = createRandom();
    mClientId = 0;

    isSend = createAtomicBoolean(true);
    mSendMutex = createMutex();
    mSendCond = createCondition();
}

void _WebSocketClientInfo::reset() {
    mHttpHeader->clear();
    //mWsHeader->clear();
    mDeflate = nullptr;
    mProtocols = nullptr;
    mContinueBuffer = nullptr;
    mClientFd = -1;
    mClientId = 0;
    isSend = createAtomicBoolean(true);
}

void _WebSocketClientInfo::enableSend() {
    isSend = createAtomicBoolean(true);
}

int _WebSocketClientInfo::getClientFd() {
    return this->mClientFd;
}

void _WebSocketClientInfo::setClientFd(int fd) {
    this->mClientFd = fd;
    mClientId = ((uint64_t)fd<<32 | st(WebSocketClientManager)::getInstance()->genRandomUint32());
}

uint64_t _WebSocketClientInfo::getClientId() {
    return mClientId;
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

int _WebSocketClientInfo::_syncsend(ByteArray data) {
     while(1) {
        isSend->set(false);
        int result = write(mClientFd,data->toValue(),data->size());
        if(result < 0) {
            if(errno == EAGAIN) {
                if(!isSend->get()) {
                    AutoLock l(mSendMutex);
                    mSendCond->wait(mSendMutex,100);
                }
                continue;
            }
        }

        if(!isSend->get()) {
            long start = st(System)::currentTimeMillis();
            AutoLock l(mSendMutex);
            mSendCond->wait(mSendMutex,100);
            printf("send socket eagain!!!,wait %d  \n",(int)(st(System)::currentTimeMillis() - start));
        }
        return result;
    }
}

int _WebSocketClientInfo::_send(int type,ByteArray msg) {
    if(mClientFd != -1) {
        int size = 0;
        
        ArrayList<ByteArray> data = nullptr;

        switch(type) {
            case st(WebSocketProtocol)::OPCODE_TEXT:
                data = mComposer->genTextMessage(AutoClone(this),msg->toString());
                break;

            case st(WebSocketProtocol)::OPCODE_BINARY:
                data = mComposer->genBinaryMessage(AutoClone(this),msg);
                break;

            case st(WebSocketProtocol)::OPCODE_CONTROL_CLOSE:
                data = createArrayList<ByteArray>();
                data->add(mComposer->genCloseMessage(AutoClone(this),msg->toString()));
                break;
            
            case st(WebSocketProtocol)::OPCODE_CONTROL_PING:
                data = createArrayList<ByteArray>();
                data->add(mComposer->genPingMessage(AutoClone(this),msg->toString()));
                break;

            case st(WebSocketProtocol)::OPCODE_CONTROL_PONG:
                data = createArrayList<ByteArray>();
                data->add(mComposer->genPongMessage(AutoClone(this),msg->toString()));
                break;

            default:
                throw ProtocolNotSupportException("WebSocketClientInfo not support OPCODE");
        }
        
        ListIterator<ByteArray> iterator = data->getIterator();
        while(iterator->hasValue()) {
            ByteArray sendData = iterator->getValue();
            //size += send(mClientFd,sendData->toValue(),sendData->size(),0);
            size += _syncsend(sendData);
            
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

int _WebSocketClientInfo::getVersion() {
    return mWsVersion;
}

void _WebSocketClientInfo::setVersion(int ver) {
    mWsVersion = ver;
}

}

