#include "HttpHeaderUserAgent.hpp"

namespace obotcha {

_HttpHeaderUserAgent::_HttpHeaderUserAgent() {

}

_HttpHeaderUserAgent::_HttpHeaderUserAgent(String v) {
    agent = v;
}

void _HttpHeaderUserAgent::import(String v) {
    agent = v->trim();
}

void _HttpHeaderUserAgent::set(String v) {
    agent = v->trim();
}

String _HttpHeaderUserAgent::get() {
    return agent;
}

String _HttpHeaderUserAgent::toString() {
    return agent;
}

}
