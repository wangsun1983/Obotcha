#include "HttpHeaderServer.hpp"

namespace obotcha {

_HttpHeaderServer::_HttpHeaderServer() {
    server = nullptr;
}

_HttpHeaderServer::_HttpHeaderServer(String s) {
    import(s);
}

void _HttpHeaderServer::import(String s) {
    server = s->trim();
}

String _HttpHeaderServer::toString() {
    return server;
}

String _HttpHeaderServer::get() {
    return server;
}

void _HttpHeaderServer::set(String s) {
    server = s->trim();
}


}
