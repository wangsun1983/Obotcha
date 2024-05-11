#include "HttpHeaderKeepAlive.hpp"
#include "HttpHeaderContentParser.hpp"
#include "StringBuffer.hpp"

namespace obotcha {

_HttpHeaderKeepAlive::_HttpHeaderKeepAlive(String s) {
    load(s);
}

void _HttpHeaderKeepAlive::load(String s) {
    st(HttpHeaderContentParser)::load(s,[this](String directive,String parameter) {
        if(directive->equalsIgnoreCase("timeout")) {
            timeout = parameter->toBasicInt();
        } else if(directive->equalsIgnoreCase("max")) {
            max = parameter->toBasicInt();
        } else {
            timeout = directive->toBasicInt();
        }
    });
}

int _HttpHeaderKeepAlive::getTimeout() const {
    return timeout;
}

int _HttpHeaderKeepAlive::getMax() const {
    return max;
}

void _HttpHeaderKeepAlive::setTimeout(int v) {
    timeout = v;
}

void _HttpHeaderKeepAlive::setMax(int v) {
    max = v;
}

String _HttpHeaderKeepAlive::toString() {
    StringBuffer keepalive = StringBuffer::New();
    if(timeout != -1) {
        keepalive->append("timeout=",String::New(timeout),", ");
    }

    if(max != -1) {
        keepalive->append("max=",String::New(max),", ");
    }
    
    if(keepalive->size() > 0) {
        return keepalive->toString(0,keepalive->size() - 2);
    }

    return nullptr;
}

}
