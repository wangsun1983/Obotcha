#include "HttpHeaderReferrerPolicy.hpp"
#include "HttpHeaderContentParser.hpp"
#include "StringBuffer.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

_HttpHeaderReferrerPolicy::_HttpHeaderReferrerPolicy(String s) {
    load(s);
}

void _HttpHeaderReferrerPolicy::load(String s) {
    String value = s->trim();
    policies->clear();
    st(HttpHeaderContentParser)::load(value,[this](String directive,
                            [[maybe_unused]] String parameter) {
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
    StringBuffer policy = createStringBuffer();
    ForEveryOne(item,policies) {
        policy->append(item,", ");
    }
    return policy->toString(0,policy->size() - 2);
}


}