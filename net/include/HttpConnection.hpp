#ifndef __OBOTCHA_HTTP_CONNECTION_HPP__
#define __OBOTCHA_HTTP_CONNECTION_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "HashMap.hpp"
#include "HttpCookie.hpp"
#include "HttpPacketParser.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Socket.hpp"
#include "HttpResponse.hpp"
#include "SocketOutputStream.hpp"
#include "HttpRequestWriter.hpp"
#include "InputStream.hpp"
#include "ThreadPoolExecutor.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"
#include "Handler.hpp"
#include "HttpOption.hpp"
#include "HttpConnectionListener.hpp"
#include "SocketMonitor.hpp"
#include "SocketListener.hpp"

namespace obotcha {

class _HttpUrl;

DECLARE_CLASS(HttpConnection) IMPLEMENTS(SocketListener){

public:
    _HttpConnection(sp<_HttpUrl> url,HttpOption option = nullptr,bool async = false, HttpConnectionListener l = nullptr);
    
    Socket getSocket();
    
    int connect();

    int close();

    HttpResponse execute(HttpRequest req);

private:
    Socket mSocket;

    HttpRequestWriter writer;

    InputStream mInputStream;

    HttpPacketParser mParser;

    sp<_HttpUrl> mUrl;

    HttpOption mOption;

    HttpConnectionListener mListener;

    bool isAsync;

    static SocketMonitor mSocketMonitor;

    void onSocketMessage(int,Socket,ByteArray);
};

}
#endif
