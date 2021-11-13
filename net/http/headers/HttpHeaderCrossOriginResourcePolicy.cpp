#include "HttpHeaderCrossOriginResourcePolicy.hpp"

namespace obotcha {

const String _HttpHeaderCrossOriginResourcePolicy::UnSafeNone = createString("unsafe-none");
const String _HttpHeaderCrossOriginResourcePolicy::RequireCorp = createString("require-corp");

_HttpHeaderCrossOriginResourcePolicy::_HttpHeaderCrossOriginResourcePolicy() {

}

_HttpHeaderCrossOriginResourcePolicy::_HttpHeaderCrossOriginResourcePolicy(String s) {
    import(s);
}

void _HttpHeaderCrossOriginResourcePolicy::import(String s) {
    policy = s->trim();
}

String _HttpHeaderCrossOriginResourcePolicy::get() {
    return policy;
}

void _HttpHeaderCrossOriginResourcePolicy::set(String s) {
    policy = s->trim();
}

String _HttpHeaderCrossOriginResourcePolicy::toString() {
    return policy;
}


}
