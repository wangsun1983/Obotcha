#include "HttpHeaderCrossOriginOpenerPolicy.hpp"

namespace obotcha {

const String _HttpHeaderCrossOriginOpenerPolicy::UnSafeNone = createString("unsafe-none");
const String _HttpHeaderCrossOriginOpenerPolicy::RequireCorp = createString("require-corp");

_HttpHeaderCrossOriginOpenerPolicy::_HttpHeaderCrossOriginOpenerPolicy() {

}

_HttpHeaderCrossOriginOpenerPolicy::_HttpHeaderCrossOriginOpenerPolicy(String s) {
    import(s);
}

void _HttpHeaderCrossOriginOpenerPolicy::import(String s) {
    policy = s->trim();
}

String _HttpHeaderCrossOriginOpenerPolicy::get() {
    return policy;
}

void _HttpHeaderCrossOriginOpenerPolicy::set(String s) {
    policy = s->trim();
}

String _HttpHeaderCrossOriginOpenerPolicy::toString() {
    return policy;
}


}
