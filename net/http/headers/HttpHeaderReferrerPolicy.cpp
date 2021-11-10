#include "HttpHeaderReferrerPolicy.hpp"
#include "HttpHeaderContentParser.hpp"

namespace obotcha {

_HttpHeaderReferrerPolicy::_HttpHeaderReferrerPolicy() {
    policies = createArrayList<String>();
}

_HttpHeaderReferrerPolicy::_HttpHeaderReferrerPolicy(String s):_HttpHeaderReferrerPolicy() {
    import(s);
}

void _HttpHeaderReferrerPolicy::import(String s) {
    String value = s->trim();
    st(HttpHeaderContentParser)::import(value,[this](String directive,String parameter) {
        policies->add(directive);
    });
}

ArrayList<String> _HttpHeaderReferrerPolicy::get() {
    return policies;
}

void _HttpHeaderReferrerPolicy::set(ArrayList<String> s) {
    policies = s;
}

void _HttpHeaderReferrerPolicy::add(String s) {
    policies->add(s->trim());
}

String _HttpHeaderReferrerPolicy::toString() {
    String policy = "";
    auto iterator = policies->getIterator();
    while(iterator->hasValue()) {
        policy = policy->append(iterator->getValue(),", ");
        iterator->next();
    }

    return policy->subString(0,policy->size() - 2);
}


}