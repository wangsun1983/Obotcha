#include "HttpHeaderKeepAlive.hpp"
#include "HttpHeaderContentParser.hpp"

namespace obotcha {

_HttpHeaderKeepAlive::_HttpHeaderKeepAlive() {
    max = -1;
    timeout = -1;
}

_HttpHeaderKeepAlive::_HttpHeaderKeepAlive(String s):_HttpHeaderKeepAlive() {
    import(s);
}

void _HttpHeaderKeepAlive::import(String s) {
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
        if(directive->equalsIgnoreCase("timeout")) {
            timeout = parameter->toBasicInt();
        } else if(directive->equalsIgnoreCase("max")) {
            max = parameter->toBasicInt();
        } else {
            max = directive->toBasicInt();
        }
    });
}

int _HttpHeaderKeepAlive::getTimeout() {
    return timeout;
}

int _HttpHeaderKeepAlive::getMax() {
    return max;
}

void _HttpHeaderKeepAlive::setTimeout(int v) {
    timeout = v;
}

void _HttpHeaderKeepAlive::setMax(int v) {
    max = v;
}

String _HttpHeaderKeepAlive::toString() {
    String keepalive = "";
    if(max != -1) {
        //keepalive = keepalive->append("max=",createString(max),", ");
        keepalive = keepalive->append(createString(max),", ");
    }

    if(timeout != -1) {
        keepalive = keepalive->append("timeout=",createString(timeout),", ");
    }
    
    if(keepalive->size() > 0) {
        return keepalive->subString(0,keepalive->size() - 2);
    }

    return keepalive;
}

}
