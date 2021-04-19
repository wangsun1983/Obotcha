#ifndef __OBOTCHA_HTTP_URL_CONNECTION_HPP__
#define __OBOTCHA_HTTP_URL_CONNECTION_HPP__

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

namespace obotcha {

class _HttpUrl;

DECLARE_SIMPLE_CLASS(HttpConnectionListener) {
public:
    virtual void onResponse(HttpResponse response) = 0;
    virtual void onDisconnect() = 0;
    virtual void onConnect(int) = 0;
};

DECLARE_SIMPLE_CLASS(HttpUrlConnection) {

public:
    friend class _HttpUrlAsyncConnectionPool;

    _HttpUrlConnection(sp<_HttpUrl> url);
    
    _HttpUrlConnection(sp<_HttpUrl> url,Handler handler);

    void setListener(HttpConnectionListener l);

    _HttpUrlConnection* setTimeout(int timeout);

    _HttpUrlConnection* setKeepAlive(bool keepalive);
    
    bool isKeepAlive();

    int connect();

    int close();

    HttpResponse execute(HttpRequest req);

private:
    int _connect();
    HttpResponse _execute(HttpRequest req);

    void onResponse(int,ByteArray r);

    int mTimeout;
    
    bool mKeepAlive; 

    Socket mSocket;

    HttpRequestWriter writer;

    InputStream mInputStream;

    HttpPacketParser mParser;

    sp<_HttpUrl> mUrl;

    Handler mHandler;

    HttpConnectionListener mListener;
};

}
#endif
