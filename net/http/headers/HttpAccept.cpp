#include "HttpAccept.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"

namespace obotcha {

_HttpAcceptItem::_HttpAcceptItem() {
    weight = 1.0;
}

_HttpAccept::_HttpAccept() {
    accepts = createArrayList<HttpAcceptItem>();
}

_HttpAccept::_HttpAccept(String s) {
    import(s);
}

void _HttpAccept::import(String s) {
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
        if(parameter == nullptr) {
            HttpAcceptItem item = createHttpAcceptItem();
            item->type = directive;
            accepts->add(item);
        } else {
            if(directive->equals("q")) {
                accepts->get(accepts->size() - 1)->weight = parameter->toBasicFloat();
            }
        }
    });
}

ArrayList<HttpAcceptItem> _HttpAccept::getAccepts() {
    return accepts;
}

String _HttpAccept::toString() {
    String accept = "";
    auto iterator = accepts->getIterator();
    while(iterator->hasValue()) {
        HttpAcceptItem item = iterator->getValue();
        if(st(Math)::compareFloat(item->weight,1.0) == st(Math)::AlmostEqual) {
            accept = accept->append(item->type,",");
        } else {
            accept = accept->append(item->type,";q=",createString(item->weight,2),",");
        }
        iterator->next();
    }

    return accept->subString(0,accept->size() - 1);
}

}
