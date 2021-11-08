#include "HttpCrossOriginOpenerPolicy.hpp"

namespace obotcha {

_HttpCrossOriginOpenerPolicy::_HttpCrossOriginOpenerPolicy() {

}

_HttpCrossOriginOpenerPolicy::_HttpCrossOriginOpenerPolicy(String s) {
    import(s);
}

void _HttpCrossOriginOpenerPolicy::import(String s) {
    policy = s->trim();
}

String _HttpCrossOriginOpenerPolicy::get() {
    return policy
}

void _HttpCrossOriginOpenerPolicy::set(String s) {
    policy = s->trim();
}

String _HttpCrossOriginOpenerPolicy::toString() {
    return policy;
}


}
