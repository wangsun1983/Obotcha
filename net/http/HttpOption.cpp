#include "HttpOption.hpp"
#include "NetProtocol.hpp"

namespace obotcha {

_HttpOption::_HttpOption() {
    mProtocol = st(NetProtocol)::Http;
}

_HttpOption * _HttpOption::setProtocol(int p) {
    mProtocol = p;
    return this;
}

int _HttpOption::getProtocol() const { 
    return mProtocol; 
}

} // namespace obotcha
