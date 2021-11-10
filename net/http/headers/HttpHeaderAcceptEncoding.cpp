#include "HttpHeaderAcceptEncoding.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"

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
    String encoding = "";
    auto iterator = encodings->getIterator();
    while(iterator->hasValue()) {
        HttpHeaderAcceptEncodingItem item = iterator->getValue();
        if(st(Math)::compareFloat(item->weight,1.0) == st(Math)::AlmostEqual) {
            encoding = encoding->append(item->type,",");
        } else {
            encoding = encoding->append(item->type,";q=",createString(item->weight,2),",");
        }
        iterator->next();
    }

    return encoding->subString(0,encoding->size() - 1);
}

}
