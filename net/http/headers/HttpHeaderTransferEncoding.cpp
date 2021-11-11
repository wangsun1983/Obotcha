#include "HttpHeaderTransferEncoding.hpp"
#include "HttpHeaderContentParser.hpp"

namespace obotcha {

_HttpHeaderTransferEncoding::_HttpHeaderTransferEncoding() {
    encodings = createArrayList<String>();
}

_HttpHeaderTransferEncoding::_HttpHeaderTransferEncoding(String s):_HttpHeaderTransferEncoding() {
    import(s->trim());
}

void _HttpHeaderTransferEncoding::import(String s) {
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
        encodings->add(directive);
    });
}

ArrayList<String> _HttpHeaderTransferEncoding::get() {
    return encodings;
}

void _HttpHeaderTransferEncoding::add(String s) {
    encodings->add(s);
}

String _HttpHeaderTransferEncoding::toString() {
    String encoding = "";
    auto iterator = encodings->getIterator();
    while(iterator->hasValue()) {
        encoding = encoding->append(iterator->getValue(),", ");
        iterator->next();
    }
    
    return encoding->subString(0,encoding->size() - 2);
}



}
