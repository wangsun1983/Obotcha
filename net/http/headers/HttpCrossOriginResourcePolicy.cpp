#include "HttpCrossOriginResourcePolicy.hpp"

namespace obotcha {

_HttpCrossOriginResourcePolicy::_HttpCrossOriginResourcePolicy() {

}

_HttpCrossOriginResourcePolicy::_HttpCrossOriginResourcePolicy(String s) {
    import(s);
}

void _HttpCrossOriginResourcePolicy::import(String s) {
    policy = s->trim();
}

String _HttpCrossOriginResourcePolicy::get() {
    return policy
}

void _HttpCrossOriginResourcePolicy::set(String s) {
    policy = s->trim();
}

String _HttpCrossOriginResourcePolicy::toString() {
    return policy;
}


}
