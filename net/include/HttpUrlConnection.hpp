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
#include "HttpOption.hpp"

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
    _HttpUrlConnection(sp<_HttpUrl> url,HttpOption option = nullptr);
    
    _HttpUrlConnection(sp<_HttpUrl> url,Handler handler,HttpOption option = nullptr);

    void setListener(HttpConnectionListener l);

    Socket getSocket();
    
    int connect();

    int close();

    HttpResponse execute(HttpRequest req);

    void execute(HttpRequest req,int what);

private:
    int _connect();

    HttpResponse _execute(HttpRequest req);

    void onResponse(int,ByteArray r);

    Socket mSocket;

    HttpRequestWriter writer;

    InputStream mInputStream;

    HttpPacketParser mParser;

    sp<_HttpUrl> mUrl;

    Handler mHandler;

    HttpConnectionListener mListener;

    HttpOption mOption;
};

}
#endif
