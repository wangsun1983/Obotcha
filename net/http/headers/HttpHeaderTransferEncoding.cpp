#include "HttpHeaderTransferEncoding.hpp"
#include "HttpHeaderContentParser.hpp"
#include "StringBuffer.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

_HttpHeaderTransferEncoding::_HttpHeaderTransferEncoding() {
    encodings = createArrayList<String>();
}

_HttpHeaderTransferEncoding::_HttpHeaderTransferEncoding(String s):_HttpHeaderTransferEncoding() {
    import(s->trim());
}

void _HttpHeaderTransferEncoding::import(String s) {
    encodings->clear();
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
    StringBuffer encoding = createStringBuffer();
    ForEveryOne(item,encodings) {
        encoding->append(item,", ");
    }
    return encoding->toString(0,encoding->size() - 2);
}



}
