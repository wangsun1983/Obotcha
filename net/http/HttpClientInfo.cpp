#include "HttpClientInfo.hpp"
#include "HttpPacket.hpp"
#include "HttpServer.hpp"
#include "HttpClientManager.hpp"

namespace obotcha {

_HttpClientInfo::_HttpClientInfo(Socket s) {
    mParser = createHttpRequestParser();
    
    mSocket = s;
    mSocketOutput = s->getOutputStream();

    mSession = createHttpSession();
}

void _HttpClientInfo::close() {
    mSocket->close();
    mParser = nullptr;
}

String _HttpClientInfo::getClientIp() {
    return mSocket->getInetAddress()->getAddress();
}

int _HttpClientInfo::pushHttpData(ByteArray array) {
    return mParser->pushHttpData(array);
}

ArrayList<HttpPacket> _HttpClientInfo::pollHttpPacket() {
    return mParser->doParse();
}

int _HttpClientInfo::send(ByteArray data) {
    if(mSSLInfo != nullptr) {
        return mSSLInfo->write(data);
    }
    return mSocketOutput->write(data);
}

int _HttpClientInfo::send(ByteArray data,int size) {
    if(mSSLInfo != nullptr) {
        return mSSLInfo->write(data);
    }
    return mSocketOutput->write(data,size);
}

SSLInfo _HttpClientInfo::getSSLInfo() {
    return mSSLInfo;
}

void _HttpClientInfo::setSSLInfo(SSLInfo info) {
    mSSLInfo = info;
}

Socket _HttpClientInfo::getSocket() {
    return mSocket;
}

HttpSession _HttpClientInfo::getSession() {
    return mSession;
}

}