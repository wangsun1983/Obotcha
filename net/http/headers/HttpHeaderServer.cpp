#include "HttpHeaderServer.hpp"

namespace obotcha {

_HttpHeaderServer::_HttpHeaderServer(String s) {
    load(s);
}

void _HttpHeaderServer::load(String s) {
    server = s->trim();
}

String _HttpHeaderServer::toString() {
    return server;
}

String _HttpHeaderServer::get() const{
    return server;
}

void _HttpHeaderServer::set(String s) {
    server = s->trim();
}


}
