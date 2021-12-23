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
#include "HttpProtocol.hpp"
#include "HttpPacketWriter.hpp"
#include "Http2StreamController.hpp"

namespace obotcha {

class _HttpServer;

DECLARE_CLASS(HttpLinker){
public:
    friend class _HttpServer;

    _HttpLinker(Socket,int protocol = st(HttpProtocol)::Http);

    int pushHttpData(ByteArray array);

    ArrayList<HttpPacket> pollHttpPacket();

    HttpPacketWriter getWriter();

    String getClientIp();

    void close();

    HttpSession getSession();

    Socket getSocket();

    int getProtocol();

    //use to http2
    int pushPacket(HttpPacket);

private:
    HttpPacketParser mParser;

    HttpPacketWriter mWriter;

    Socket mSocket;

    OutputStream mSocketOutput;

    HttpSession mSession;

    int mProtocol;

    //Http2Stream Controller
    Http2StreamController mHttp2StreamController;
};

}
#endif
