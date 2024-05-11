#include "HttpHeaderVary.hpp"
#include "HttpHeaderContentParser.hpp"
#include "StringBuffer.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

_HttpHeaderVary::_HttpHeaderVary(String s):_HttpHeaderVary() {
    load(s);
}

void _HttpHeaderVary::load(String s) {
    String value = s->trim();
    varies->clear();
    st(HttpHeaderContentParser)::load(value,[this](String directive,
                                [[maybe_unused]] String parameter) {
        varies->add(directive);
    });
}

ArrayList<String> _HttpHeaderVary::get() const {
    return varies;
}

void _HttpHeaderVary::set(ArrayList<String> s) {
    varies = s;
}

void _HttpHeaderVary::add(String s) {
    varies->add(s->trim());
}

String _HttpHeaderVary::toString() {
    StringBuffer vary = StringBuffer::New();
    ForEveryOne(item,varies) {
        vary->append(item,", ");
    }
    return vary->toString(0,vary->size() - 2);
}


}