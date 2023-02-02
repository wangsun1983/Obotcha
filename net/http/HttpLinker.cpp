#include "HttpLinker.hpp"
#include "HttpPacket.hpp"
#include "HttpServer.hpp"
#include "Http2PacketWriterImpl.hpp"
#include "HttpPacketWriterImpl.hpp"
#include "Http2StreamController.hpp"
#include "HttpSimplePacketWriterImpl.hpp"
#include "HttpSessionManager.hpp"

namespace obotcha {

_HttpLinker::_HttpLinker(Socket s,int protocol) {
    mSocket = s;
    //printf("create http linker,protocol is %d \n",protocol);
    switch(protocol) {
        case st(NetProtocol)::Http_H2:
        case st(NetProtocol)::Http_H2C:
            //default use httpv1 parser
            mHttp2StreamController = createHttp2StreamController(s->getOutputStream());
            mParser = mHttp2StreamController;
            //mWriter = createHttp2PacketWriterImpl(mHttp2StreamController);//TODO
        break;

        default:
            mWriter = createHttpPacketWriterImpl(s->getOutputStream());
            mSimpleWriter = createHttpSimplePacketWriterImpl(s->getOutputStream());
            mParser = createHttpPacketParserImpl();
    }

    mProtocol = protocol;
    //mSession = st(HttpSessionManager)::getInstance()->createSession();
}

int _HttpLinker::getProtocol() {
    return mProtocol;
}

void _HttpLinker::close() {
    mSocket->close();
    if(mSession != nullptr) {
        st(HttpSessionManager)::getInstance()->remove(mSession);
        mSession->invalidate();
        mParser = nullptr;
        mSession = nullptr;
    }
}

InetAddress _HttpLinker::getInetAddress() {
    return mSocket->getInetAddress();
}

int _HttpLinker::pushData(ByteArray array) {
    return mParser->pushData(array);
}

ArrayList<HttpPacket> _HttpLinker::pollPacket() {
    return mParser->doParse();
}

void _HttpLinker::setSessionId(String id) {
    mSession = st(HttpSessionManager)::getInstance()->get(id);
}

HttpSession _HttpLinker::getSession() { 
    if(mSession == nullptr) {
        mSession = st(HttpSessionManager)::getInstance()->createSession();
    }
    return mSession; 
}

HttpPacketWriter _HttpLinker::getWriter() {
    return mWriter;
}

HttpPacketWriter _HttpLinker::getSimpleWriter() {
    return mSimpleWriter;
}

Http2StreamController _HttpLinker::getStreamController() {
    return mHttp2StreamController;
}

} // namespace obotcha