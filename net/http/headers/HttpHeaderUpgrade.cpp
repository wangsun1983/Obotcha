#include "HttpHeaderUpgrade.hpp"

namespace obotcha {

_HttpHeaderUpgrade::_HttpHeaderUpgrade() {

}

_HttpHeaderUpgrade::_HttpHeaderUpgrade(String s) {
    upgrade = s->trim();
}

void _HttpHeaderUpgrade::load(String s) {
    upgrade = s->trim();
}

String _HttpHeaderUpgrade::get() {
    return upgrade;
}

void _HttpHeaderUpgrade::set(String s) {
    upgrade = s->trim();
}

String _HttpHeaderUpgrade::toString() {
    return upgrade;
}

}
