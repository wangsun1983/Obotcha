#include "HttpSecWebSocketProtocol.hpp"
#include "HttpHeaderContentParser.hpp"

namespace obotcha {

_HttpSecWebSocketProtocol::_HttpSecWebSocketProtocol() {
    protocols = createArrayList<String>();
}

_HttpSecWebSocketProtocol::_HttpSecWebSocketProtocol(String s):_HttpSecWebSocketProtocol() {
    import(s->trim());
}

void _HttpSecWebSocketProtocol::import(String s) {
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
        protocols->add(directive);
    });
}

ArrayList<String> _HttpSecWebSocketProtocol::get() {
    return protocols;
}

void _HttpSecWebSocketProtocol::add(String s) {
    protocols->add(s->trim());
}

void _HttpSecWebSocketProtocol::set(ArrayList<String> s) {
    protocols = s;
}

String _HttpSecWebSocketProtocol::toString() {
    String protocol = "";
    auto iterator = protocols->getIterator();
    while(iterator->hasValue()) {
        protocol = protocol->append(iterator->getValue(),", ");
        iterator->next();
    }

    return protocol->subString(0,protocol->size() - 2);
}


}