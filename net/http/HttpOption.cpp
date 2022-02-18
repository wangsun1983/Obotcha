#include "HttpOption.hpp"
#include "NetProtocol.hpp"

namespace obotcha {

_HttpOption::_HttpOption() {
    mKey = nullptr;
    mCretificate = nullptr;
    mProtocol = st(NetProtocol)::Http;
}

_HttpOption *_HttpOption::setOpenSSLCertificate(String v) {
    mProtocol = st(NetProtocol)::Https;
    mCretificate = v;
    return this;
}

_HttpOption *_HttpOption::setOpenSSLKey(String v) {
    mProtocol = st(NetProtocol)::Https;
    mKey = v;
    return this;
}

_HttpOption * _HttpOption::setProtocol(int p) {
    mProtocol = p;
    return this;
}

String _HttpOption::getOpenSSLCertificate() { 
    return mCretificate; 
}

String _HttpOption::getOpenSSLKey() { 
    return mKey; 
}

int _HttpOption::getProtocol() { 
    return mProtocol; 
}

} // namespace obotcha
