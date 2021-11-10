#include "HttpHeaderAcceptCharSet.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"

namespace obotcha {

_HttpHeaderAcceptCharSetItem::_HttpHeaderAcceptCharSetItem(String s,float w) {
    weight = w;
    type = s;
}

_HttpHeaderAcceptCharSet::_HttpHeaderAcceptCharSet() {
    charsets = createArrayList<HttpHeaderAcceptCharSetItem>();
}

_HttpHeaderAcceptCharSet::_HttpHeaderAcceptCharSet(String s) {
    import(s);
}

void _HttpHeaderAcceptCharSet::import(String s) {
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
        if(parameter == nullptr) {
            HttpHeaderAcceptCharSetItem item = createHttpHeaderAcceptCharSetItem(directive);
            charsets->add(item);
        } else {
            if(directive->equals("q")) {
                charsets->get(charsets->size() - 1)->weight = parameter->toBasicFloat();
            }
        }
    });
}

ArrayList<HttpHeaderAcceptCharSetItem> _HttpHeaderAcceptCharSet::get() {
    return charsets;
}

void _HttpHeaderAcceptCharSet::add(String s,float w) {
    charsets->add(createHttpHeaderAcceptCharSetItem(s,w));
}

String _HttpHeaderAcceptCharSet::toString() {
    String charset = "";
    auto iterator = charsets->getIterator();
    while(iterator->hasValue()) {
        HttpHeaderAcceptCharSetItem item = iterator->getValue();
        if(st(Math)::compareFloat(item->weight,1.0) == st(Math)::AlmostEqual) {
            charset = charset->append(item->type,", ");
        } else {
            charset = charset->append(item->type,";q=",createString(item->weight,2),", ");
        }
        iterator->next();
    }

    return charset->subString(0,charset->size() - 2);
}

}
