#include "HttpServerBuilder.hpp"

namespace obotcha {

_HttpServerBuilder::_HttpServerBuilder() {
    mAddress = createInetAddress();
    mCert = nullptr;
    mKey = nullptr;
    mListener = nullptr;
}
    
_HttpServerBuilder* _HttpServerBuilder::setAddress(InetAddress addr) {
    mAddress = addr;
    return this;
}

_HttpServerBuilder* _HttpServerBuilder::setCertificate(String c) {
    mCert = c;
    return this;
}

_HttpServerBuilder* _HttpServerBuilder::setKey(String k) {
    mKey = k;
    return this;
}
_HttpServerBuilder* _HttpServerBuilder::setListener(HttpListener l) {
    mListener = l;
    return this;
}

HttpServer _HttpServerBuilder::build() {
    return createHttpServer(mAddress,mListener,mCert,mKey);
}

}
