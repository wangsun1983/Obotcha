#include "HttpHeaderVary.hpp"
#include "HttpHeaderContentParser.hpp"
#include "StringBuffer.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

_HttpHeaderVary::_HttpHeaderVary() {
    varies = createArrayList<String>();
}

_HttpHeaderVary::_HttpHeaderVary(String s):_HttpHeaderVary() {
    import(s);
}

void _HttpHeaderVary::import(String s) {
    String value = s->trim();
    varies->clear();
    st(HttpHeaderContentParser)::import(value,[this](String directive,String parameter) {
        varies->add(directive);
    });
}

ArrayList<String> _HttpHeaderVary::get() {
    return varies;
}

void _HttpHeaderVary::set(ArrayList<String> s) {
    varies = s;
}

void _HttpHeaderVary::add(String s) {
    varies->add(s->trim());
}

String _HttpHeaderVary::toString() {
    StringBuffer vary = createStringBuffer();
    ForEveryOne(item,varies) {
        vary->append(item,", ");
    }
    return vary->toString(0,vary->size() - 2);
}


}