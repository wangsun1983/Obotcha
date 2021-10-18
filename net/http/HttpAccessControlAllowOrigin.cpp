#include "HttpAccessControlAllowOrigin.hpp"

namespace obotcha {


_HttpAccessControlAllowOrigin::_HttpAccessControlAllowOrigin() {

}

_HttpAccessControlAllowOrigin::_HttpAccessControlAllowOrigin(String v):_HttpAccessControlAllowOrigin() {
    import(v);
}

void _HttpAccessControlAllowOrigin::import(String v) {
    origin = v;
}

void _HttpAccessControlAllowOrigin::setOrigin(String v) {
    origin = v;
}

String _HttpAccessControlAllowOrigin::getOrigin() {
    return origin;
}

String _HttpAccessControlAllowOrigin::toString() {
    return origin;
}


}
