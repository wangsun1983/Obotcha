#include "WebSocketLinker.hpp"
#include "WebSocketProtocol.hpp"
#include "MethodNotSupportException.hpp"
#include "ProtocolNotSupportException.hpp"
#include "WebSocketListener.hpp"

namespace obotcha {

_WebSocketLinker::_WebSocketLinker(int version,Socket sock) {
    mSock = sock;
    mWriter = createWebSocketOutputWriter(version,st(WebSocketProtocol)::Server,sock);
    mReader = createWebSocketInputReader(version,st(WebSocketProtocol)::Server);
    mInspector = createWebSocketInspector(version);
}

_WebSocketLinker::~_WebSocketLinker() {
    //nothing
}

WebSocketInputReader _WebSocketLinker::getInputReader() {
    return mReader;
}

WebSocketInspector _WebSocketLinker::getInspector() {
    return mInspector;
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
    this->mWriter->setDeflate(d);
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

long _WebSocketLinker::sendBinaryMessage(ByteArray data) {
    return mWriter->sendBinaryMessage(data);
}

long _WebSocketLinker::sendTextMessage(String data) {
    return mWriter->sendTextMessage(data);
}

long _WebSocketLinker::sendPingMessage(ByteArray data) {
    return mWriter->sendPingMessage(data);
}

long _WebSocketLinker::sendPongMessage(ByteArray data) {
    return mWriter->sendPongMessage(data);
}

long _WebSocketLinker::sendCloseMessage(int reason,ByteArray extraInfo) {
    return mWriter->sendCloseMessage(reason,extraInfo);
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
