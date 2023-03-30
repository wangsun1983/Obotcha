#include "HttpHeaderMatch.hpp"
#include "HttpHeaderContentParser.hpp"
#include "StringBuffer.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

//If-Match: "bfc13a64729c4290ef5b2c2730249c88ca92d82d"
//If-Match: W/"67ab43", "54ed21", "7892dd"
//If-Match: *
_HttpHeaderMatchItem::_HttpHeaderMatchItem(String tag,bool week) {
    if(tag->contains("\"")) {
        this->tag = tag->subString(1,tag->size() - 2); //match item param
    } else {
        this->tag = tag;
    }

    this->isWeakAlg = week;    
}

_HttpHeaderMatch::_HttpHeaderMatch() {
    items = createArrayList<HttpHeaderMatchItem>();
}

_HttpHeaderMatch::_HttpHeaderMatch(String v):_HttpHeaderMatch() {
    import(v);
}

void _HttpHeaderMatch::import(String s) {
    items->clear();
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
        if(directive->containsIgnoreCase("W/")) {
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
    items->add(createHttpHeaderMatchItem(v->trim(),isWeak));
}

String _HttpHeaderMatch::_convertTag(String s) {
    if(s->equals("*")) {
        return s->append(", ");
    } else {
        return createString("\"")->append(s,"\", ");
    }
}

String _HttpHeaderMatch::toString() {
    StringBuffer match = createStringBuffer();
    ForEveryOne(item,items) {
        if(item->isWeakAlg) {
            match->append("W/",_convertTag(item->tag));
        } else {
            match->append(_convertTag(item->tag));
        }
    }
    return match->toString(0,match->size() - 2);
}



}