#include "HttpHeaderSecFetchUser.hpp"

namespace obotcha {

const String _HttpHeaderSecFetchUser::UserActivate = "?0";
const String _HttpHeaderSecFetchUser::OtherActivate = "?1";

_HttpHeaderSecFetchUser::_HttpHeaderSecFetchUser() {
}

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
