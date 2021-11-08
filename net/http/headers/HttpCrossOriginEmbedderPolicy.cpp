#include "HttpCrossOriginEmbedderPolicy.hpp"

namespace obotcha {

_HttpCrossOriginEmbedderPolicy::_HttpCrossOriginEmbedderPolicy() {

}

_HttpCrossOriginEmbedderPolicy::_HttpCrossOriginEmbedderPolicy(String s) {
    import(s);
}

void _HttpCrossOriginEmbedderPolicy::import(String s) {
    policy = s->trim();
}

String _HttpCrossOriginEmbedderPolicy::get() {
    return policy
}

void _HttpCrossOriginEmbedderPolicy::set(String s) {
    policy = s->trim();
}

String _HttpCrossOriginEmbedderPolicy::toString() {
    return policy;
}


}
