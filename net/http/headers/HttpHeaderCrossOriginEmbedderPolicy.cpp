#include "HttpHeaderCrossOriginEmbedderPolicy.hpp"

namespace obotcha {

_HttpHeaderCrossOriginEmbedderPolicy::_HttpHeaderCrossOriginEmbedderPolicy() {

}

_HttpHeaderCrossOriginEmbedderPolicy::_HttpHeaderCrossOriginEmbedderPolicy(String s) {
    import(s);
}

void _HttpHeaderCrossOriginEmbedderPolicy::import(String s) {
    policy = s->trim();
}

String _HttpHeaderCrossOriginEmbedderPolicy::get() {
    return policy
}

void _HttpHeaderCrossOriginEmbedderPolicy::set(String s) {
    policy = s->trim();
}

String _HttpHeaderCrossOriginEmbedderPolicy::toString() {
    return policy;
}


}
