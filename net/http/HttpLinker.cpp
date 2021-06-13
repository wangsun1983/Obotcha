#include "HttpLinker.hpp"
#include "HttpPacket.hpp"
#include "HttpServer.hpp"
#include "HttpLinkerManager.hpp"

namespace obotcha {

_HttpLinker::_HttpLinker(Socket s) {
    mParser = createHttpPacketParser();
    
    mSocket = s;
    mSocketOutput = s->getOutputStream();

    mSession = createHttpSession();
}

void _HttpLinker::close() {
    mSocket->close();
    mParser = nullptr;
}

String _HttpLinker::getClientIp() {
    return mSocket->getInetAddress()->getAddress();
}

int _HttpLinker::pushHttpData(ByteArray array) {
    return mParser->pushHttpData(array);
}

ArrayList<HttpPacket> _HttpLinker::pollHttpPacket() {
    return mParser->doParse();
}

//int _HttpLinker::send(ByteArray data) {
//    if(mSSLInfo != nullptr) {
//        return mSSLInfo->write(data);
//    }
//    return mSocketOutput->write(data);
//}

//int _HttpLinker::send(ByteArray data,int size) {
//    if(mSSLInfo != nullptr) {
//        return mSSLInfo->write(data);
//    }
//    return mSocketOutput->write(data,size);
//}

SSLInfo _HttpLinker::getSSLInfo() {
    return mSSLInfo;
}

void _HttpLinker::setSSLInfo(SSLInfo info) {
    mSSLInfo = info;
}

Socket _HttpLinker::getSocket() {
    return mSocket;
}

HttpSession _HttpLinker::getSession() {
    return mSession;
}

}