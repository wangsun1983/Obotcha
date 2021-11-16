#include "HttpHeaderSecWebSocketExtensions.hpp"
#include "HttpHeaderContentParser.hpp"
#include "StringBuffer.hpp"

namespace obotcha {

_HttpHeaderSecWebSocketExtensions::_HttpHeaderSecWebSocketExtensions() {
    extensions = createArrayList<String>();
}

_HttpHeaderSecWebSocketExtensions::_HttpHeaderSecWebSocketExtensions(String s):_HttpHeaderSecWebSocketExtensions() {
    import(s->trim());
}

void _HttpHeaderSecWebSocketExtensions::import(String s) {
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
        extensions->add(directive);
    });
}

ArrayList<String> _HttpHeaderSecWebSocketExtensions::get() {
    return extensions;
}

void _HttpHeaderSecWebSocketExtensions::set(ArrayList<String> s) {
    extensions = s;
}

void _HttpHeaderSecWebSocketExtensions::add(String s) {
    extensions->add(s->trim());
}

String _HttpHeaderSecWebSocketExtensions::toString() {
    StringBuffer extension = createStringBuffer();
    auto iterator = extensions->getIterator();
    while(iterator->hasValue()) {
        extension->append(iterator->getValue(),", ");
        iterator->next();
    }
    
    return extension->toString(0,extension->size() - 2);
}


}