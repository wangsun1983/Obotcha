#include "HttpOption.hpp"

namespace obotcha {

_HttpOption::_HttpOption() {
    mProtocol = st(Net)::Protocol::Http;
}

_HttpOption * _HttpOption::setProtocol(st(Net)::Protocol p) {
    mProtocol = p;
    return this;
}

st(Net)::Protocol _HttpOption::getProtocol() const { 
    return mProtocol; 
}

} // namespace obotcha
