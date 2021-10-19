#include "HttpContentEncoding.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"

namespace obotcha {


_HttpContentEncoding::_HttpContentEncoding() {
    encodings = createArrayList<String>();
}

_HttpContentEncoding::_HttpContentEncoding(String s) {
    import(s);
}

void _HttpContentEncoding::import(String s) {
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
        encodings->add(directive);
    });
}

ArrayList<String> _HttpContentEncoding::get() {
    return encodings;
}

void _HttpContentEncoding::add(String v) {
    encodings->add(v);
}


String _HttpContentEncoding::toString() {
    String encoding = "";
    auto iterator = encodings->getIterator();
    while(iterator->hasValue()) {
        encoding = encoding->append(iterator->getValue(),", ");
        iterator->next();
    }

    return encoding->subString(0,encoding->size() - 2);
}

}
