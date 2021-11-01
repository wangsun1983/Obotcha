#include "HttpAcceptCharSet.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"

namespace obotcha {

_HttpAcceptCharSetItem::_HttpAcceptCharSetItem(String s,float w) {
    weight = w;
    type = s;
}

_HttpAcceptCharSet::_HttpAcceptCharSet() {
    charsets = createArrayList<HttpAcceptCharSetItem>();
}

_HttpAcceptCharSet::_HttpAcceptCharSet(String s) {
    import(s);
}

void _HttpAcceptCharSet::import(String s) {
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
        if(parameter == nullptr) {
            HttpAcceptCharSetItem item = createHttpAcceptCharSetItem(directive);
            charsets->add(item);
        } else {
            if(directive->equals("q")) {
                charsets->get(charsets->size() - 1)->weight = parameter->toBasicFloat();
            }
        }
    });
}

ArrayList<HttpAcceptCharSetItem> _HttpAcceptCharSet::get() {
    return charsets;
}

void _HttpAcceptCharSet::add(String s,float w) {
    charsets->add(createHttpAcceptCharSetItem(s,w));
}

String _HttpAcceptCharSet::toString() {
    String charset = "";
    auto iterator = charsets->getIterator();
    while(iterator->hasValue()) {
        HttpAcceptCharSetItem item = iterator->getValue();
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
