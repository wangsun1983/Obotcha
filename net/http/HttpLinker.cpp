#include "HttpLinker.hpp"
#include "HttpLinkerManager.hpp"
#include "HttpPacket.hpp"
#include "HttpServer.hpp"
#include "Http2PacketWriterImpl.hpp"
#include "HttpPacketWriterImpl.hpp"
#include "Http2StreamController.hpp"
#include "HttpSimplePacketWriterImpl.hpp"

namespace obotcha {

_HttpLinker::_HttpLinker(Socket s,int protocol) {
    mSocket = s;
    mSession = createHttpSession();

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
}

int _HttpLinker::getProtocol() {
    return mProtocol;
}

void _HttpLinker::close() {
    mSocket->close();
    mSession->invalidate();
    mParser = nullptr;
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

HttpSession _HttpLinker::getSession() { 
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