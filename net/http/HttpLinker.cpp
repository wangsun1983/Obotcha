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
    mSocketOutput = s->getOutputStream();
    mSession = createHttpSession();

    switch(protocol) {
        case st(HttpProtocol)::Http_H2:
        case st(HttpProtocol)::Http_H2C:
            mWriter = createHttp2PacketWriterImpl(mSocketOutput);//TODO
            
            //default use httpv1 parser
            mHttp2StreamController = createHttp2StreamController(mSocketOutput);
            mParser = mHttp2StreamController;
        break;

        default:
            mWriter = createHttpPacketWriterImpl(mSocketOutput);
            mParser = createHttpPacketParserImpl();
    }

    mProtocol = protocol;
}

int _HttpLinker::getProtocol() {
    return mProtocol;
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

Socket _HttpLinker::getSocket() { 
    return mSocket; 
}

HttpSession _HttpLinker::getSession() { 
    return mSession; 
}

HttpPacketWriter _HttpLinker::getWriter() {
    return mWriter;
}

int _HttpLinker::pushPacket(HttpPacket p) {
    Http2Packet packet = Cast<Http2Packet>(p);
    Http2Stream stream = mHttp2StreamController->newStream();
    return stream->write(packet);
}

} // namespace obotcha