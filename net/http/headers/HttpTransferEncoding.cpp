#include "HttpTransferEncoding.hpp"
#include "HttpHeaderContentParser.hpp"

namespace obotcha {

_HttpTransferEncoding::_HttpTransferEncoding() {
    encodings = createArrayList<String>();
}

_HttpTransferEncoding::_HttpTransferEncoding(String s):_HttpTransferEncoding() {
    import(s->trim());
}

void _HttpTransferEncoding::import(String s) {
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
        encodings->add(directive);
    });
}

ArrayList<String> _HttpTransferEncoding::get() {
    return encodings;
}

void _HttpTransferEncoding::add(String s) {
    encodings->add(s);
}

String _HttpTransferEncoding::toString() {
    String encoding = "";
    auto iterator = encodings->getIterator();
    while(iterator->hasValue()) {
        encoding = encoding->append(iterator->getValue(),", ");
        iterator->next();
    }
    
    return encoding->subString(0,encoding->size() - 2);
}



}
