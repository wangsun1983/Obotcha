#include "HttpHeaderSecWebSocketProtocol.hpp"
#include "HttpHeaderContentParser.hpp"
#include "StringBuffer.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

_HttpHeaderSecWebSocketProtocol::_HttpHeaderSecWebSocketProtocol(String s) {
    load(s->trim());
}

void _HttpHeaderSecWebSocketProtocol::load(String s) {
    protocols->clear();
    st(HttpHeaderContentParser)::load(s,[this](String directive,
                                        [[maybe_unused]] String parameter) {
        protocols->add(directive);
    });
}

ArrayList<String> _HttpHeaderSecWebSocketProtocol::get() const {
    return protocols;
}

String _HttpHeaderSecWebSocketProtocol::get(int index) const {
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