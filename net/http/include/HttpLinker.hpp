#ifndef __OBOTCHA_HTTP_LINKER_INFO_HPP__
#define __OBOTCHA_HTTP_LINKER_INFO_HPP__

#include "Object.hpp"
#include "ArrayList.hpp"
#include "HttpPacket.hpp"
#include "Socket.hpp"
#include "HttpSession.hpp"
#include "NetProtocol.hpp"
#include "HttpPacketWriter.hpp"
#include "Http2StreamController.hpp"
#include "InetAddress.hpp"

namespace obotcha {

class _HttpServer;
class _Http2Server;

DECLARE_CLASS(HttpLinker){
public:
    friend class _HttpServer;
    friend class _Http2Server;
    friend class _WebSocketServer;

    _HttpLinker(Socket,int protocol = st(NetProtocol)::Http);

    int pushData(ByteArray array);

    ArrayList<HttpPacket> pollPacket();

    HttpPacketWriter getWriter();

    HttpPacketWriter getSimpleWriter();

    InetAddress getInetAddress();

    void close();

    void setSessionId(String);
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
