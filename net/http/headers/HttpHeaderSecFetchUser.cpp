#include "HttpHeaderSecFetchUser.hpp"

namespace obotcha {

const String _HttpHeaderSecFetchUser::UserActivate = "?0";
const String _HttpHeaderSecFetchUser::OtherActivate = "?1";

_HttpHeaderSecFetchUser::_HttpHeaderSecFetchUser() {

}

_HttpHeaderSecFetchUser::_HttpHeaderSecFetchUser(String s) {
    import(s);
}

void _HttpHeaderSecFetchUser::import(String s) {
    value = s->trim();
}

void _HttpHeaderSecFetchUser::set(String s) {
    import(s);
}

String _HttpHeaderSecFetchUser::get() {
    return value;
}

String _HttpHeaderSecFetchUser::toString() {
    return value;
}


}
