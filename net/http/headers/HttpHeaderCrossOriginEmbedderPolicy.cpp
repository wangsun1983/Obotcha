#include "HttpHeaderCrossOriginEmbedderPolicy.hpp"

namespace obotcha {

const String _HttpHeaderCrossOriginEmbedderPolicy::UnSafeNone = createString("unsafe-none");
const String _HttpHeaderCrossOriginEmbedderPolicy::RequireCorp = createString("require-corp");

_HttpHeaderCrossOriginEmbedderPolicy::_HttpHeaderCrossOriginEmbedderPolicy() {

}

_HttpHeaderCrossOriginEmbedderPolicy::_HttpHeaderCrossOriginEmbedderPolicy(String s) {
    import(s);
}

void _HttpHeaderCrossOriginEmbedderPolicy::import(String s) {
    policy = s->trim();
}

String _HttpHeaderCrossOriginEmbedderPolicy::get() {
    return policy;
}

void _HttpHeaderCrossOriginEmbedderPolicy::set(String s) {
    policy = s->trim();
}

String _HttpHeaderCrossOriginEmbedderPolicy::toString() {
    return policy;
}


}
