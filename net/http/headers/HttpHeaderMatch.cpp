#include "HttpHeaderMatch.hpp"
#include "HttpHeaderContentParser.hpp"

namespace obotcha {

_HttpHeaderMatchItem::_HttpHeaderMatchItem(String tag,bool week) {
    this->tag = tag;
    this->isWeakAlg = week;    
}

_HttpHeaderMatch::_HttpHeaderMatch() {
    items = createArrayList<HttpHeaderMatchItem>();
}

_HttpHeaderMatch::_HttpHeaderMatch(String v):_HttpHeaderMatch() {
    import(v);
}

void _HttpHeaderMatch::import(String s) {
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
        if(directive->contains("W/")) {
            items->add(createHttpHeaderMatchItem(directive->subString(2,directive->size() - 2),true));
        } else {
            items->add(createHttpHeaderMatchItem(directive,false));
        }
    });
}

ArrayList<HttpHeaderMatchItem> _HttpHeaderMatch::get() {
    return items;
}

void _HttpHeaderMatch::add(String v,bool isWeak) {
    items->add(createHttpHeaderMatchItem(v,isWeak));
}

String _HttpHeaderMatch::toString() {
    String match = "";
    auto iterator = items->getIterator();
    while(iterator->hasValue()) {
        HttpHeaderMatchItem item = iterator->getValue();
        if(item->isWeakAlg) {
            match = match->append("W/\"",item->tag,"\", ");
        } else {
            match = match->append("\"",item->tag,"\", ");
        }
        iterator->next();
    }

    return match->subString(0,match->size() - 2);
}



}