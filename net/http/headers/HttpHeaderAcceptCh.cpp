#include "HttpHeaderAcceptCh.hpp"
#include "HttpHeaderContentParser.hpp"
#include "StringBuffer.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

_HttpHeaderAcceptCh::_HttpHeaderAcceptCh() {
    accepts = createArrayList<String>();
}

_HttpHeaderAcceptCh::_HttpHeaderAcceptCh(String s) {
    load(s);
}

void _HttpHeaderAcceptCh::load(String s) {
    accepts->clear();
    
    String value = s->trim();
    st(HttpHeaderContentParser)::load(value,[this](String directive,String parameter) {
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
    StringBuffer acceptCh = createStringBuffer();
    ForEveryOne(item,accepts) {
        acceptCh->append(item,", ");
    }
    return acceptCh->toString(0,acceptCh->size() - 2);
}


}
