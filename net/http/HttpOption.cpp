#include "HttpOption.hpp"
#include "HttpProtocol.hpp"

namespace obotcha {

_HttpOption::_HttpOption() {
    mKey = nullptr;
    mCretificate = nullptr;
    mProtocol = st(HttpProtocol)::Http;
}

_HttpOption *_HttpOption::setCertificate(String v) {
    mProtocol = st(HttpProtocol)::Https;
    mCretificate = v;
    return this;
}

_HttpOption *_HttpOption::setKey(String v) {
    mProtocol = st(HttpProtocol)::Https;
    mKey = v;
    return this;
}

_HttpOption * _HttpOption::setProtocol(int p) {
    mProtocol = p;
    return this;
}

String _HttpOption::getCertificate() { 
    return mCretificate; 
}

String _HttpOption::getKey() { 
    return mKey; 
}

int _HttpOption::getProtocol() { 
    return mProtocol; 
}

} // namespace obotcha
