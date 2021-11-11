#include "HttpHeaderSecWebSocketExtensions.hpp"
#include "HttpHeaderContentParser.hpp"

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
    String extension = "";
    auto iterator = extensions->getIterator();
    while(iterator->hasValue()) {
        extension = extension->append(iterator->getValue(),", ");
        iterator->next();
    }
    
    return extension->subString(0,extension->size() - 2);
}


}