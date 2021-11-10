#include "HttpHeaderVary.hpp"
#include "HttpHeaderContentParser.hpp"

namespace obotcha {

_HttpHeaderVary::_HttpHeaderVary() {
    varies = createArrayList<String>();
}

_HttpHeaderVary::_HttpHeaderVary(String s):_HttpHeaderVary() {
    import(s);
}

void _HttpHeaderVary::import(String s) {
    String value = s->trim();
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
    String vary = "";
    auto iterator = varies->getIterator();
    while(iterator->hasValue()) {
        vary = vary->append(iterator->getValue(),", ");
        iterator->next();
    }

    return vary->subString(0,vary->size() - 2);
}


}