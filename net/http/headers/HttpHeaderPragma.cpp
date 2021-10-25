#include "HttpHeaderPragma.hpp"

namespace obotcha {


_HttpHeaderPragma::_HttpHeaderPragma() {

}

_HttpHeaderPragma::_HttpHeaderPragma(String s) {
    pragma = s;
}

void _HttpHeaderPragma::import(String s) {
    pragma = s;
}

String _HttpHeaderPragma::get() {
    return pragma;
}

void _HttpHeaderPragma::set(String s) {
    pragma = s;
}

String _HttpHeaderPragma::toString() {
    return pragma;
}


}