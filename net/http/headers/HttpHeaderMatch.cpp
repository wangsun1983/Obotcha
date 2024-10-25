#include "HttpHeaderMatch.hpp"
#include "HttpHeaderContentParser.hpp"
#include "StringBuffer.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

//If-Match: "bfc13a64729c4290ef5b2c2730249c88ca92d82d"
//If-Match: W/"67ab43", "54ed21", "7892dd"
//If-Match: *
_HttpHeaderMatchItem::_HttpHeaderMatchItem(String tag,bool week):isWeakAlg(week) {
    if(tag->contains("\"")) {
        this->tag = tag->subString(1,tag->size() - 2); //match item param
    } else {
        this->tag = tag;
    }  
}

_HttpHeaderMatch::_HttpHeaderMatch(String v) {
    load(v);
}

void _HttpHeaderMatch::load(String s) {
    items->clear();
    st(HttpHeaderContentParser)::load(s,[this](String directive,
                                    [[maybe_unused]] String parameter) {
        if(directive->containsIgnoreCase("W/")) {
            items->add(HttpHeaderMatchItem::New(directive->subString(2,directive->size() - 2),true));
        } else {
            items->add(HttpHeaderMatchItem::New(directive,false));
        }
    });
}

ArrayList<HttpHeaderMatchItem> _HttpHeaderMatch::get() const {
    return items;
}

void _HttpHeaderMatch::add(String v,bool isWeak) {
    items->add(HttpHeaderMatchItem::New(v->trim(),isWeak));
}

String _HttpHeaderMatch::_convertTag(String s) const {
    if(s->sameAs("*")) {
        return s->append(", ");
    } else {
        return String::New("\"")->append(s,"\", ");
    }
}

String _HttpHeaderMatch::toString() {
    StringBuffer match = StringBuffer::New();
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