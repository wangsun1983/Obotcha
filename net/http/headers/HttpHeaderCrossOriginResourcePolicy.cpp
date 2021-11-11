#include "HttpHeaderCrossOriginResourcePolicy.hpp"

namespace obotcha {

_HttpHeaderCrossOriginResourcePolicy::_HttpHeaderCrossOriginResourcePolicy() {

}

_HttpHeaderCrossOriginResourcePolicy::_HttpHeaderCrossOriginResourcePolicy(String s) {
    import(s);
}

void _HttpHeaderCrossOriginResourcePolicy::import(String s) {
    policy = s->trim();
}

String _HttpHeaderCrossOriginResourcePolicy::get() {
    return policy
}

void _HttpHeaderCrossOriginResourcePolicy::set(String s) {
    policy = s->trim();
}

String _HttpHeaderCrossOriginResourcePolicy::toString() {
    return policy;
}


}
