#include "HttpAccessControlAllowOrigin.hpp"

namespace obotcha {


_HttpAccessControlAllowOrigin::_HttpAccessControlAllowOrigin() {

}

_HttpAccessControlAllowOrigin::_HttpAccessControlAllowOrigin(String v):_HttpAccessControlAllowOrigin() {
    import(v);
}

void _HttpAccessControlAllowOrigin::import(String v) {
    origin = v->trim();
}

void _HttpAccessControlAllowOrigin::set(String v) {
    origin = v->trim();
}

String _HttpAccessControlAllowOrigin::get() {
    return origin;
}

String _HttpAccessControlAllowOrigin::toString() {
    return origin;
}


}
