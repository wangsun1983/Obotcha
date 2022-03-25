#ifndef __OBOTCHA_HTTP_LINKER_INFO_HPP__
#define __OBOTCHA_HTTP_LINKER_INFO_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "HashMap.hpp"
#include "HttpCookie.hpp"
#include "HttpUrl.hpp"
#include "HttpHeader.hpp"
#include "ByteRingArray.hpp"
#include "ByteRingArrayReader.hpp"
#include "HttpPacket.hpp"
#include "Random.hpp"
#include "Socket.hpp"
#include "HttpSession.hpp"
#include "HttpPacketParserImpl.hpp"
#include "NetProtocol.hpp"
#include "HttpPacketWriter.hpp"
#include "Http2StreamController.hpp"
#include "InetAddress.hpp"

namespace obotcha {

class _HttpServer;

DECLARE_CLASS(HttpLinker){
public:
    friend class _HttpServer;
    friend class _HttpLinkerManager;
    friend class _WebSocketServer;

    _HttpLinker(Socket,int protocol = st(NetProtocol)::Http);

    int pushData(ByteArray array);

    ArrayList<HttpPacket> pollPacket();

    HttpPacketWriter getWriter();

    HttpPacketWriter getSimpleWriter();

    InetAddress getInetAddress();

    void close();

    HttpSession getSession();

    int getProtocol();

    //use to http2
    //int pushPacket(HttpPacket);
    Http2StreamController getStreamController();

private:
    HttpPacketParser mParser;

    HttpPacketWriter mWriter;

    HttpPacketWriter mSimpleWriter;

    Socket mSocket;

    HttpSession mSession;

    int mProtocol;

    //Http2Stream Controller
    Http2StreamController mHttp2StreamController;
};

}
#endif
