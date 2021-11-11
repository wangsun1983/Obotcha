#include "HttpHeaderCrossOriginOpenerPolicy.hpp"

namespace obotcha {

_HttpHeaderCrossOriginOpenerPolicy::_HttpHeaderCrossOriginOpenerPolicy() {

}

_HttpHeaderCrossOriginOpenerPolicy::_HttpHeaderCrossOriginOpenerPolicy(String s) {
    import(s);
}

void _HttpHeaderCrossOriginOpenerPolicy::import(String s) {
    policy = s->trim();
}

String _HttpHeaderCrossOriginOpenerPolicy::get() {
    return policy
}

void _HttpHeaderCrossOriginOpenerPolicy::set(String s) {
    policy = s->trim();
}

String _HttpHeaderCrossOriginOpenerPolicy::toString() {
    return policy;
}


}
