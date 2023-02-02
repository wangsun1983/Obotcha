#include "HttpServerBuilder.hpp"

namespace obotcha {

_HttpServerBuilder::_HttpServerBuilder() {
    mAddress = createInetAddress();
    mOption = nullptr;
    mListener = nullptr;
//    mProtocol = st(NetProtocol)::Http;
}

_HttpServerBuilder *_HttpServerBuilder::setAddress(InetAddress addr) {
    mAddress = addr;
    return this;
}

_HttpServerBuilder *_HttpServerBuilder::setListener(HttpListener l) {
    mListener = l;
    return this;
}

// _HttpServerBuilder *_HttpServerBuilder::setProtocol(int p) {
//     mProtocol = p;
//     return this;
// }

_HttpServerBuilder *_HttpServerBuilder::setHttp2Listener(Http2Listener l) {
    mHttp2Listener = l;
    return this;
}

_HttpServerBuilder *_HttpServerBuilder::setOption(HttpOption option) {
    mOption = option;
    return this;
}

//_HttpServerBuilder *_HttpServerBuilder::setCertificatePath(String s) {
//    mCertificatePath = s;
//    return this;
//}

//_HttpServerBuilder *_HttpServerBuilder::setKeyPath(String s) {
//    mKeyPath = s;
//    return this;
//}

HttpServer _HttpServerBuilder::build() {
//    updateOption();
    return createHttpServer(mAddress, mListener, mOption);
}

Http2Server _HttpServerBuilder::buildHttp2Server() {
//    updateOption();
    if(mOption == nullptr) {
        mOption = createHttpOption();
    }

    if(mOption->getSSLCertificatePath() != nullptr) {
        mOption->setProtocol(st(NetProtocol)::Http_H2);
    } else {
        mOption->setProtocol(st(NetProtocol)::Http_H2C);
    }
    
    return createHttp2Server(mAddress, mHttp2Listener, mOption);
}

} // namespace obotcha
