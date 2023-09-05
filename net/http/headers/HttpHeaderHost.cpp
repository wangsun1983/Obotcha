#include "HttpHeaderHost.hpp"

namespace obotcha {

_HttpHeaderHost::_HttpHeaderHost(String v,int p):host(v),port(p) {
}

void _HttpHeaderHost::load(String h) {
    String v = h->trim();
    size_t index = v->indexOf(":");
    if(index != -1) {
        host = v->subString(0,index);
        port = v->subString(index + 1,v->size() - index - 1)->toBasicInt();
    } else {
        host = v;
    }
}

void _HttpHeaderHost::setHost(String v) {
    host = v->trim();
}

void _HttpHeaderHost::setPort(int v) {
    port = v;
}

String _HttpHeaderHost::getHost() const {
    return host;
}

int _HttpHeaderHost::getPort() const {
    return port;
}

String _HttpHeaderHost::toString() {
    return (port == -1)?host:host->append(":",createString(port));
}

}
