#include "HttpHeaderAccept.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"
#include "StringBuffer.hpp"

namespace obotcha {

_HttpHeaderAcceptItem::_HttpHeaderAcceptItem(String s,float w) {
    weight = w;
    type = s;
}

_HttpHeaderAccept::_HttpHeaderAccept() {
    accepts = createArrayList<HttpHeaderAcceptItem>();
}

_HttpHeaderAccept::_HttpHeaderAccept(String s) {
    import(s);
}

void _HttpHeaderAccept::import(String s) {
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
        if(parameter == nullptr) {
            HttpHeaderAcceptItem item = createHttpHeaderAcceptItem(directive);
            accepts->add(item);
        } else {
            if(directive->equals("q")) {
                accepts->get(accepts->size() - 1)->weight = parameter->toBasicFloat();
            }
        }
    });
}

ArrayList<HttpHeaderAcceptItem> _HttpHeaderAccept::get() {
    return accepts;
}

void _HttpHeaderAccept::add(String s,float w) {
    accepts->add(createHttpHeaderAcceptItem(s,w));
}

String _HttpHeaderAccept::toString() {
    StringBuffer accept = createStringBuffer();
    auto iterator = accepts->getIterator();
    while(iterator->hasValue()) {
        HttpHeaderAcceptItem item = iterator->getValue();
        if(st(Math)::compareFloat(item->weight,1.0) == st(Math)::AlmostEqual) {
            accept->append(item->type,",");
        } else {
            accept->append(item->type,";q=",createString(item->weight,2),",");
        }
        iterator->next();
    }

    return accept->toString(0,accept->size() - 1);
}

}
