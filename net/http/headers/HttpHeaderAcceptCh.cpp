#include "HttpHeaderAcceptCh.hpp"
#include "HttpHeaderContentParser.hpp"

namespace obotcha {

_HttpHeaderAcceptCh::_HttpHeaderAcceptCh() {
    accepts = createArrayList<String>();
}

_HttpHeaderAcceptCh::_HttpHeaderAcceptCh(String s) {
    import(s);
}

void _HttpHeaderAcceptCh::import(String s) {
    String value = s->trim();
    st(HttpHeaderContentParser)::import(value,[this](String directive,String parameter) {
        accepts->add(directive);
    });
}

ArrayList<String> _HttpHeaderAcceptCh::get() {
    return accepts;
}

void _HttpHeaderAcceptCh::add(String s) {
    accepts->add(s->trim());
}

String _HttpHeaderAcceptCh::toString() {
    String acceptCh = "";
    auto iterator = accepts->getIterator();
    while(iterator->hasValue()) {
        acceptCh = acceptCh->append(iterator->getValue(),", ");
        iterator->next();
    }

    return acceptCh->subString(0,acceptCh->size() - 2);
}


}
