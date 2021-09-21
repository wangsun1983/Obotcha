#include "HttpOption.hpp"

namespace obotcha {

_HttpOption::_HttpOption() {
    mKey = nullptr;
    mCretificate = nullptr;
}

_HttpOption *_HttpOption::setCertificate(String v) {
    mCretificate = v;
    return this;
}

_HttpOption *_HttpOption::setKey(String v) {
    mKey = v;
    return this;
}

String _HttpOption::getCertificate() { return mCretificate; }

String _HttpOption::getKey() { return mKey; }

} // namespace obotcha
