#include "HttpHeaderHost.hpp"

namespace obotcha {

_HttpHeaderHost::_HttpHeaderHost() {
    host = nullptr;
    port = -1;
}

_HttpHeaderHost::_HttpHeaderHost(String v):_HttpHeaderHost() {
    import(v);
}

void _HttpHeaderHost::import(String v) {
    int index = v->indexOf(":");
    if(index > 0) {
        host = v->subString(0,index);
        port = v->subString(index + 1,v->size() - index - 1)->toBasicInt();
    } else {
        host = v;
    }
}

void _HttpHeaderHost::setHost(String v) {
    host = v;
}

void _HttpHeaderHost::setPort(int v) {
    port = v;
}

String _HttpHeaderHost::getHost() {
    return host;
}

int _HttpHeaderHost::getPort() {
    return port;
}

String _HttpHeaderHost::toString() {
    String h = host;
    if(port != -1) {
        h = h->append(":",createString(port));
    }

    return h;
}


}