#ifndef __OBOTCHA_HTTP_CONNECTION_BUILDER_HPP__
#define __OBOTCHA_HTTP_CONNECTION_BUILDER_HPP__

#include <mutex>
#include <thread>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "HttpOption.hpp"
#include "HttpUrl.hpp"
#include "HttpConnectionListener.hpp"
#include "HttpAsyncConnectionPool.hpp"
#include "HttpConnection.hpp"
#include "HttpAsyncConnection.hpp"

namespace obotcha {


DECLARE_SIMPLE_CLASS(HttpConnectionBuilder) {

public:
    _HttpConnectionBuilder *setUrl(String);
    _HttpConnectionBuilder *setHttpOption(HttpOption);
    _HttpConnectionBuilder *setListener(HttpConnectionListener);
    _HttpConnectionBuilder *setHandler(Handler);
    HttpConnection createConnection();
    HttpAsyncConnection createAsyncConnection();

private:
    HttpOption mOption;
    HttpUrl mUrl;
    HttpConnectionListener mListener;
    Handler mHandler;

    static std::once_flag s_flag;
    static HttpAsyncConnectionPool mPool;
};

}
#endif
