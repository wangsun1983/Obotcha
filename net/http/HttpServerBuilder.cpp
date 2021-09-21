#include "HttpServerBuilder.hpp"

namespace obotcha {

_HttpServerBuilder::_HttpServerBuilder() {
    mAddress = createInetAddress();
    mOption = nullptr;
    mListener = nullptr;
}

_HttpServerBuilder *_HttpServerBuilder::setAddress(InetAddress addr) {
    mAddress = addr;
    return this;
}

_HttpServerBuilder *_HttpServerBuilder::setListener(HttpListener l) {
    mListener = l;
    return this;
}

_HttpServerBuilder *_HttpServerBuilder::setOption(HttpOption option) {
    mOption = option;
    return this;
}

HttpServer _HttpServerBuilder::build() {
    return createHttpServer(mAddress, mListener, mOption);
}

} // namespace obotcha
