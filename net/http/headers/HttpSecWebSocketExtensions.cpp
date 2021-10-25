#include "HttpSecWebSocketExtensions.hpp"
#include "HttpHeaderContentParser.hpp"

namespace obotcha {

_HttpSecWebSocketExtensions::_HttpSecWebSocketExtensions() {
    extensions = createArrayList<String>();
}

_HttpSecWebSocketExtensions::_HttpSecWebSocketExtensions(String s):_HttpSecWebSocketExtensions() {
    import(s);
}

void _HttpSecWebSocketExtensions::import(String s) {
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
        extensions->add(directive);
    });
}

ArrayList<String> _HttpSecWebSocketExtensions::get() {
    return extensions;
}

void _HttpSecWebSocketExtensions::set(ArrayList<String> s) {
    extensions = s;
}

void _HttpSecWebSocketExtensions::add(String s) {
    extensions->add(s);
}

String _HttpSecWebSocketExtensions::toString() {
    String extension = "";
    auto iterator = extensions->getIterator();
    while(iterator->hasValue()) {
        extension = extension->append(iterator->getValue(),", ");
        iterator->next();
    }

    return extension->subString(0,extension->size() - 2);
}


}