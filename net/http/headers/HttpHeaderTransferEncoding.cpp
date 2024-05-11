#include "HttpHeaderTransferEncoding.hpp"
#include "HttpHeaderContentParser.hpp"
#include "StringBuffer.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

_HttpHeaderTransferEncoding::_HttpHeaderTransferEncoding(String s):_HttpHeaderTransferEncoding() {
    load(s->trim());
}

void _HttpHeaderTransferEncoding::load(String s) {
    encodings->clear();
    st(HttpHeaderContentParser)::load(s,[this](String directive,[[maybe_unused]]String parameter) {
        encodings->add(directive);
    });
}

ArrayList<String> _HttpHeaderTransferEncoding::get() const {
    return encodings;
}

void _HttpHeaderTransferEncoding::add(String s) {
    encodings->add(s);
}

String _HttpHeaderTransferEncoding::toString() {
    StringBuffer encoding = StringBuffer::New();
    ForEveryOne(item,encodings) {
        encoding->append(item,", ");
    }
    return encoding->toString(0,encoding->size() - 2);
}



}
