#include "HttpAcceptEncoding.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"

namespace obotcha {

_HttpAcceptEncodingItem::_HttpAcceptEncodingItem(String s,float w) {
    weight = w;
    type = s;
}

_HttpAcceptEncoding::_HttpAcceptEncoding() {
    encodings = createArrayList<HttpAcceptEncodingItem>();
}

_HttpAcceptEncoding::_HttpAcceptEncoding(String s) {
    import(s);
}

void _HttpAcceptEncoding::import(String s) {
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
        if(parameter == nullptr) {
            HttpAcceptEncodingItem item = createHttpAcceptEncodingItem(directive);
            encodings->add(item);
        } else {
            if(directive->equals("q")) {
                encodings->get(encodings->size() - 1)->weight = parameter->toBasicFloat();
            }
        }
    });
}

ArrayList<HttpAcceptEncodingItem> _HttpAcceptEncoding::get() {
    return encodings;
}

void _HttpAcceptEncoding::add(String s,float w) {
    encodings->add(createHttpAcceptEncodingItem(s,w));
}

String _HttpAcceptEncoding::toString() {
    String encoding = "";
    auto iterator = encodings->getIterator();
    while(iterator->hasValue()) {
        HttpAcceptEncodingItem item = iterator->getValue();
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
