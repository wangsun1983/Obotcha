#include "HttpConnectionBuilder.hpp"
#include "HttpUrlParser.hpp"

namespace obotcha {

std::once_flag _HttpConnectionBuilder::s_flag;
HttpAsyncConnectionPool _HttpConnectionBuilder::mPool;

_HttpConnectionBuilder *_HttpConnectionBuilder::setUrl(String url) {
    mUrl = st(HttpUrlParser)::parseUrl(url);
    return this;
}

_HttpConnectionBuilder *_HttpConnectionBuilder::setHttpOption(HttpOption option) {
    mOption = option;
    return this;
}

_HttpConnectionBuilder *_HttpConnectionBuilder::setListener(HttpConnectionListener l) {
    mListener = l;
    return this;
}

_HttpConnectionBuilder *_HttpConnectionBuilder::setHandler(Handler h) {
    mHandler = h;
    return this;
}

HttpConnection _HttpConnectionBuilder::createConnection() {
    HttpConnection c = createHttpConnection(mUrl,mOption);
    c->setListener(mListener);
    return c;
}

HttpAsyncConnection _HttpConnectionBuilder::createAsyncConnection() {
    std::call_once(s_flag, [&]() {
        mPool = createHttpAsyncConnectionPool();
    });

    HttpAsyncConnection c = mPool->createConnection(mUrl,mListener,mOption);
    return c;
}

}
