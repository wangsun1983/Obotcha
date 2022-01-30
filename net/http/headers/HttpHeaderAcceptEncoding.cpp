#include "HttpHeaderAcceptEncoding.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"
#include "StringBuffer.hpp"

namespace obotcha {
_HttpHeaderAcceptEncodingItem::_HttpHeaderAcceptEncodingItem(String s,float w) {
    weight = w;
    type = s;
}

_HttpHeaderAcceptEncoding::_HttpHeaderAcceptEncoding() {
    encodings = createArrayList<HttpHeaderAcceptEncodingItem>();
}

_HttpHeaderAcceptEncoding::_HttpHeaderAcceptEncoding(String s) {
    import(s);
}

void _HttpHeaderAcceptEncoding::import(String s) {
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
        if(parameter == nullptr) {
            HttpHeaderAcceptEncodingItem item = createHttpHeaderAcceptEncodingItem(directive);
            encodings->add(item);
        } else {
            if(directive->equals("q")) {
                encodings->get(encodings->size() - 1)->weight = parameter->toBasicFloat();
            }
        }
    });
}

ArrayList<HttpHeaderAcceptEncodingItem> _HttpHeaderAcceptEncoding::get() {
    return encodings;
}

void _HttpHeaderAcceptEncoding::add(String s,float w) {
    encodings->add(createHttpHeaderAcceptEncodingItem(s,w));
}

String _HttpHeaderAcceptEncoding::toString() {
    StringBuffer encoding = createStringBuffer();
    auto iterator = encodings->getIterator();
    while(iterator->hasValue()) {
        HttpHeaderAcceptEncodingItem item = iterator->getValue();
        //rfc2616 14.4 Accept-Language
        //The quality value defaults to "q=1". For
        //example,
        //Accept-Language: da, en-gb;q=0.8, en;q=0.7
        if(st(Math)::compareFloat(item->weight,1.0) == st(Math)::AlmostEqual) {
            encoding->append(item->type,",");
        } else {
            encoding->append(item->type,";q=",createString(item->weight,2),",");
        }
        iterator->next();
    }

    return encoding->toString(0,encoding->size() - 1);
}

}
