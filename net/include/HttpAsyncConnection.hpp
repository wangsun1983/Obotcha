#ifndef __OBOTCHA_HTTP_ASYNC_CONNECTION_HPP__
#define __OBOTCHA_HTTP_ASYNC_CONNECTION_HPP__

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
#include "HttpConnectionListener.hpp"

namespace obotcha {

class _HttpUrl;
class _HttpAsyncConnectionPool;

DECLARE_SIMPLE_CLASS(HttpAsyncConnection) {

public:
    friend class _HttpAsyncConnectionPool;

    _HttpAsyncConnection(sp<_HttpUrl> url,HttpConnectionListener l,HttpOption option = nullptr);
    
    int connect();

    int close();

    int execute(HttpRequest req);

private:
    void onResponse(int,ByteArray r);

    Socket mSocket;

    HttpRequestWriter writer;

    InputStream mInputStream;

    HttpPacketParser mParser;

    sp<_HttpUrl> mUrl;

    HttpOption mOption;

    HttpConnectionListener mListener;

    sp<_HttpAsyncConnectionPool> mPool;
};

}
#endif
