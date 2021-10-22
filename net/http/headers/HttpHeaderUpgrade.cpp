#include "HttpHeaderUpgrade.hpp"

namespace obotcha {

_HttpHeaderUpgrade::_HttpHeaderUpgrade() {

}

_HttpHeaderUpgrade::_HttpHeaderUpgrade(String s) {
    upgrade = s;
}

void _HttpHeaderUpgrade::import(String s) {
    upgrade = s;
}

String _HttpHeaderUpgrade::get() {
    return upgrade;
}

void _HttpHeaderUpgrade::set(String s) {
    upgrade = s;
}

String _HttpHeaderUpgrade::toString() {
    return upgrade;
}

}
