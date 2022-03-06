#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ByteArray.hpp"
#include "ByteArrayReader.hpp"
#include "HttpHeader.hpp"
#include "InetAddress.hpp"
#include "ProtocolNotSupportException.hpp"
#include "String.hpp"
#include "System.hpp"
#include "WebSocketComposer.hpp"
#include "WebSocketFrame.hpp"
#include "WebSocketLinker.hpp"
#include "WebSocketListener.hpp"
#include "WebSocketParser.hpp"
#include "WebSocketPermessageDeflate.hpp"
#include "WebSocketProtocol.hpp"
#include "WebSocketServer.hpp"

namespace obotcha {

_WebSocketLinker::_WebSocketLinker(Socket sock) {
    reset();

    mSock = sock;
    mOutputStream = sock->getOutputStream();
}

void _WebSocketLinker::reset() {
    mParser = nullptr;
    mComposer = nullptr;
    mDeflate = nullptr;
    mProtocols = nullptr;
    mKey = nullptr;
    mConnectUrl = nullptr;
    mCallback = nullptr;
    mWsVersion = -1;
}

sp<_WebSocketParser> _WebSocketLinker::getParser() { 
    return this->mParser; 
}

void _WebSocketLinker::setParser(sp<_WebSocketParser> p) { 
    this->mParser = p; 
}

sp<_WebSocketComposer> _WebSocketLinker::getComposer() {
    return this->mComposer;
}

void _WebSocketLinker::setComposer(sp<_WebSocketComposer> p) {
    this->mComposer = p;
}

void _WebSocketLinker::setWebSocketKey(String key) { 
    this->mKey = key; 
}

String _WebSocketLinker::getWebSocketKey() { 
    return mKey; 
}

void _WebSocketLinker::setProtocols(ArrayList<String> p) { 
    this->mProtocols = p; 
}

ArrayList<String> _WebSocketLinker::getProtocols() { 
    return this->mProtocols; 
}

sp<_WebSocketPermessageDeflate> _WebSocketLinker::getDeflater() {
    return mDeflate;
}

void _WebSocketLinker::setDeflater(sp<_WebSocketPermessageDeflate> d) {
    mDeflate = d;
    this->mComposer->setDeflate(d);
}

void _WebSocketLinker::setWebSocketListener(sp<_WebSocketListener> l) {
    mCallback = l;
}

sp<_WebSocketListener> _WebSocketLinker::getWebSocketListener() {
    return mCallback;
}

void _WebSocketLinker::setPath(String path) { 
    mPath = path; 
}

String _WebSocketLinker::getPath() { 
    return mPath; 
}

String _WebSocketLinker::getConnectUrl() { 
    return mConnectUrl; 
}

void _WebSocketLinker::setConnectUrl(String l) { 
    mConnectUrl = l; 
}

long _WebSocketLinker::_send(int type, ByteArray msg) {
    if (mSock != nullptr) {
        long size = 0;

        ArrayList<ByteArray> data = nullptr;

        switch (type) {
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
                throw ProtocolNotSupportException(
                    "WebSocketLinker not support OPCODE");
        }

        ListIterator<ByteArray> iterator = data->getIterator();
        while (iterator->hasValue()) {
            ByteArray sendData = iterator->getValue();
            // size += send(mClientFd,sendData->toValue(),sendData->size(),0);
            // size += _syncsend(sendData);
            size += mOutputStream->write(sendData);
            iterator->next();
        }

        return size;
    }

    return -1;
}

long _WebSocketLinker::sendBinaryMessage(ByteArray data) {
    return _send(st(WebSocketProtocol)::OPCODE_BINARY, data);
}

long _WebSocketLinker::sendTextMessage(String data) {
    return _send(st(WebSocketProtocol)::OPCODE_TEXT, data->toByteArray());
}

long _WebSocketLinker::sendPingMessage(ByteArray data) {
    return _send(st(WebSocketProtocol)::OPCODE_CONTROL_PING, data);
}

long _WebSocketLinker::sendPongMessage(ByteArray data) {
    return _send(st(WebSocketProtocol)::OPCODE_CONTROL_PONG, data);
}

long _WebSocketLinker::sendCloseMessage(ByteArray data) {
    return _send(st(WebSocketProtocol)::OPCODE_CONTROL_CLOSE, data);
}

int _WebSocketLinker::getVersion() { 
    return mWsVersion; 
}

void _WebSocketLinker::setVersion(int ver) { 
    mWsVersion = ver; 
}

Socket _WebSocketLinker::getSocket() { 
    return mSock; 
}

} // namespace obotcha
