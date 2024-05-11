#include "HttpHeaderSecWebSocketExtensions.hpp"
#include "HttpHeaderContentParser.hpp"
#include "StringBuffer.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

_HttpHeaderSecWebSocketExtensions::_HttpHeaderSecWebSocketExtensions(String s):_HttpHeaderSecWebSocketExtensions() {
    load(s->trim());
}

void _HttpHeaderSecWebSocketExtensions::load(String s) {
    extensions->clear();
    st(HttpHeaderContentParser)::load(s,[this](String directive,
                                    [[maybe_unused]] String parameter) {
        extensions->add(directive);
    });
}

ArrayList<String> _HttpHeaderSecWebSocketExtensions::get() const {
    return extensions;
}

void _HttpHeaderSecWebSocketExtensions::set(ArrayList<String> s) {
    extensions = s;
}

void _HttpHeaderSecWebSocketExtensions::add(String s) {
    extensions->add(s->trim());
}

String _HttpHeaderSecWebSocketExtensions::toString() {
    StringBuffer extension = StringBuffer::New();
    ForEveryOne(item,extensions) {
        extension->append(item,", ");
    }
    return extension->toString(0,extension->size() - 2);
}


}