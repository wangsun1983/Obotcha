#include "HttpHeaderContentEncoding.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"

namespace obotcha {


_HttpHeaderContentEncoding::_HttpHeaderContentEncoding() {
    encodings = createArrayList<String>();
}

_HttpHeaderContentEncoding::_HttpHeaderContentEncoding(String s):_HttpHeaderContentEncoding() {
    import(s);
}

void _HttpHeaderContentEncoding::import(String s) {
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
        encodings->add(directive);
    });
}

ArrayList<String> _HttpHeaderContentEncoding::get() {
    return encodings;
}

void _HttpHeaderContentEncoding::add(String v) {
    encodings->add(v->trim());
}


String _HttpHeaderContentEncoding::toString() {
    String encoding = "";
    auto iterator = encodings->getIterator();
    while(iterator->hasValue()) {
        encoding = encoding->append(iterator->getValue(),", ");
        iterator->next();
    }

    return encoding->subString(0,encoding->size() - 2);
}

}