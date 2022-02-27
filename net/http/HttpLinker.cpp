#include "HttpLinker.hpp"
#include "HttpLinkerManager.hpp"
#include "HttpPacket.hpp"
#include "HttpServer.hpp"
#include "Http2PacketWriterImpl.hpp"
#include "HttpPacketWriterImpl.hpp"
#include "Http2StreamController.hpp"

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

//Socket _HttpLinker::getSocket() { 
//    return mSocket; 
//}

HttpSession _HttpLinker::getSession() { 
    return mSession; 
}

HttpPacketWriter _HttpLinker::getWriter() {
    return mWriter;
}

Http2StreamController _HttpLinker::getStreamController() {
    return mHttp2StreamController;
}

//int _HttpLinker::pushPacket(HttpPacket p) {
//    Http2Packet packet = Cast<Http2Packet>(p);
//    Http2Stream stream = mHttp2StreamController->newStream();
//    return stream->write(packet);
//}

} // namespace obotcha