#include "HttpHeaderSecFetchUser.hpp"

namespace obotcha {

const String _HttpHeaderSecFetchUser::kUserActivate = "?0";
const String _HttpHeaderSecFetchUser::kOtherActivate = "?1";

_HttpHeaderSecFetchUser::_HttpHeaderSecFetchUser(String s) {
    load(s);
}

void _HttpHeaderSecFetchUser::load(String s) {
    value = s->trim();
}

void _HttpHeaderSecFetchUser::set(String s) {
    load(s);
}

String _HttpHeaderSecFetchUser::get() {
    return value;
}

String _HttpHeaderSecFetchUser::toString() {
    return value;
}


}
