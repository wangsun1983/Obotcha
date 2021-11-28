#include "HttpServerBuilder.hpp"

namespace obotcha {

_HttpServerBuilder::_HttpServerBuilder() {
    mAddress = createInetAddress();
    mOption = nullptr;
    mListener = nullptr;
    mProtocol = st(HttpProtocol)::Http;
}

_HttpServerBuilder *_HttpServerBuilder::setAddress(InetAddress addr) {
    mAddress = addr;
    return this;
}

_HttpServerBuilder *_HttpServerBuilder::setListener(HttpListener l) {
    mListener = l;
    return this;
}

_HttpServerBuilder *_HttpServerBuilder::setProtocol(int p) {
    mProtocol = p;
    return this;
}


_HttpServerBuilder *_HttpServerBuilder::setOption(HttpOption option) {
    mOption = option;
    return this;
}

_HttpServerBuilder *_HttpServerBuilder::setCertificatePath(String s) {
    mCertificatePath = s;
    return this;
}

_HttpServerBuilder *_HttpServerBuilder::setKeyPath(String s) {
    mKeyPath = s;
    return this;
}

HttpServer _HttpServerBuilder::build() {
    if(mOption == nullptr) {
        mOption = createHttpOption();
    }
    
    mOption->setCertificate(mCertificatePath);
    mOption->setKey(mKeyPath);
    mOption->setProtocol(mProtocol);

    return createHttpServer(mAddress, mListener, mOption);
}

} // namespace obotcha
