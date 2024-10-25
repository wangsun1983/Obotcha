#include "HttpServerBuilder.hpp"

namespace obotcha {

_HttpServerBuilder *_HttpServerBuilder::setAddress(InetAddress addr) {
    mAddress = addr;
    return this;
}

_HttpServerBuilder *_HttpServerBuilder::setListener(HttpListener l) {
    mListener = l;
    return this;
}

_HttpServerBuilder *_HttpServerBuilder::setHttp2Listener(Http2Listener l) {
    mHttp2Listener = l;
    return this;
}

_HttpServerBuilder *_HttpServerBuilder::setOption(HttpOption option) {
    mOption = option;
    return this;
}

HttpServer _HttpServerBuilder::build() {
    return HttpServer::New(mAddress, mListener, mOption);
}

Http2Server _HttpServerBuilder::buildHttp2Server() {
    if(mOption == nullptr) {
        mOption = HttpOption::New();
    }

    if(mOption->getSSLCertificatePath() != nullptr) {
        mOption->setProtocol(st(Net)::Protocol::Http_H2);
    } else {
        mOption->setProtocol(st(Net)::Protocol::Http_H2C);
    }
    
    return Http2Server::New(mAddress, mHttp2Listener, mOption);
}

} // namespace obotcha
