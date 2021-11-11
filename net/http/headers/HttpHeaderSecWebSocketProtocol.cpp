#include "HttpHeaderSecWebSocketProtocol.hpp"
#include "HttpHeaderContentParser.hpp"

namespace obotcha {

_HttpHeaderSecWebSocketProtocol::_HttpHeaderSecWebSocketProtocol() {
    protocols = createArrayList<String>();
}

_HttpHeaderSecWebSocketProtocol::_HttpHeaderSecWebSocketProtocol(String s):_HttpHeaderSecWebSocketProtocol() {
    import(s->trim());
}

void _HttpHeaderSecWebSocketProtocol::import(String s) {
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
        protocols->add(directive);
    });
}

ArrayList<String> _HttpHeaderSecWebSocketProtocol::get() {
    return protocols;
}

void _HttpHeaderSecWebSocketProtocol::add(String s) {
    protocols->add(s->trim());
}

void _HttpHeaderSecWebSocketProtocol::set(ArrayList<String> s) {
    protocols = s;
}

String _HttpHeaderSecWebSocketProtocol::toString() {
    String protocol = "";
    auto iterator = protocols->getIterator();
    while(iterator->hasValue()) {
        protocol = protocol->append(iterator->getValue(),", ");
        iterator->next();
    }

    return protocol->subString(0,protocol->size() - 2);
}


}