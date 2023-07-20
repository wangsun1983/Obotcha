#include "HttpHeaderSecWebSocketProtocol.hpp"
#include "HttpHeaderContentParser.hpp"
#include "StringBuffer.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

_HttpHeaderSecWebSocketProtocol::_HttpHeaderSecWebSocketProtocol() {
    protocols = createArrayList<String>();
}

_HttpHeaderSecWebSocketProtocol::_HttpHeaderSecWebSocketProtocol(String s):_HttpHeaderSecWebSocketProtocol() {
    load(s->trim());
}

void _HttpHeaderSecWebSocketProtocol::load(String s) {
    protocols->clear();
    st(HttpHeaderContentParser)::load(s,[this](String directive,String parameter) {
        protocols->add(directive);
    });
}

ArrayList<String> _HttpHeaderSecWebSocketProtocol::get() {
    return protocols;
}

String _HttpHeaderSecWebSocketProtocol::get(int index) {
    return protocols->get(index);
}

void _HttpHeaderSecWebSocketProtocol::add(String s) {
    protocols->add(s->trim());
}

void _HttpHeaderSecWebSocketProtocol::set(ArrayList<String> s) {
    protocols = s;
}

String _HttpHeaderSecWebSocketProtocol::toString() {
    StringBuffer protocol = createStringBuffer();
    ForEveryOne(item,protocols) {
        protocol->append(item,", ");
    }
    return protocol->toString(0,protocol->size() - 2);
}


}