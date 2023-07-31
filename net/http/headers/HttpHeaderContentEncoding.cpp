#include "HttpHeaderContentEncoding.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"
#include "StringBuffer.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {


_HttpHeaderContentEncoding::_HttpHeaderContentEncoding() {
    encodings = createArrayList<String>();
}

_HttpHeaderContentEncoding::_HttpHeaderContentEncoding(String s):_HttpHeaderContentEncoding() {
    load(s);
}

void _HttpHeaderContentEncoding::load(String s) {
    encodings->clear();
    st(HttpHeaderContentParser)::load(s,[this](String directive,
                                            [[maybe_unused]] String parameter) {
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
    StringBuffer encoding = createStringBuffer();
    ForEveryOne(item,encodings) {
        encoding->append(item,", ");
    }
    return encoding->toString(0,encoding->size() - 2);
}

}
