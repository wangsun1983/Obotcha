#ifndef __OBOTCHA_HTTP_CONNECTION_HPP__
#define __OBOTCHA_HTTP_CONNECTION_HPP__

#include "Object.hpp"
#include "HttpPacketParser.hpp"
#include "Socket.hpp"
#include "InputStream.hpp"
#include "Mutex.hpp"
#include "HttpOption.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "HttpPacketWriter.hpp"
#include "HttpPacketParserImpl.hpp"

namespace obotcha {

class _HttpUrl;

DECLARE_CLASS(HttpConnection) {

public:
    friend class _WebSocketClient;
    _HttpConnection(sp<_HttpUrl> url,HttpOption option = nullptr);
    int connect();
    int close();
    HttpResponse execute(HttpRequest req);

private:
    Socket getSocket();
    Socket mSocket;
    HttpPacketWriter mWriter;
    InputStream mInputStream;
    HttpPacketParser mParser = createHttpPacketParserImpl();
    sp<_HttpUrl> mUrl;
    HttpOption mOption;
    Mutex mMutex = createMutex();
};

}
#endif
