#ifndef __OBOTCHA_HTTP_URL_ASYNC_CONNECTION_HPP__
#define __OBOTCHA_HTTP_URL_ASYNC_CONNECTION_HPP__

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
#include "HttpOption.hpp"

namespace obotcha {

class _HttpUrl;

DECLARE_SIMPLE_CLASS(HttpAsyncConnectionListener) {
public:
    virtual void onResponse(HttpResponse response) = 0;
    virtual void onDisconnect() = 0;
    virtual void onConnect(int) = 0;
};

DECLARE_SIMPLE_CLASS(HttpUrlAsyncConnection) {

public:
    friend class _HttpUrlAsyncConnectionPool;

    _HttpUrlAsyncConnection(sp<_HttpUrl> url,HttpAsyncConnectionListener l,HttpOption option = nullptr);
    
    int connect();

    int close();

    int execute(HttpRequest req);

private:
    //int _connect();
    //HttpResponse _execute(HttpRequest req);

    void onResponse(int,ByteArray r);

    Socket mSocket;

    HttpRequestWriter writer;

    InputStream mInputStream;

    HttpPacketParser mParser;

    sp<_HttpUrl> mUrl;

    HttpOption mOption;

    HttpAsyncConnectionListener mListener;
};

}
#endif
