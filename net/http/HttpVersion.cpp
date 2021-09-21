#include "Object.hpp"
#include "StrongPointer.hpp"

#include "HttpText.hpp"
#include "HttpVersion.hpp"
#include "String.hpp"

namespace obotcha {

_HttpVersion::_HttpVersion() {
    mMajorVer = 1;
    mMinorVer = 1;
}

_HttpVersion::_HttpVersion(int major, int minor) {
    mMajorVer = major;
    mMinorVer = minor;
}

int _HttpVersion::getMajorVer() { return mMajorVer; }

int _HttpVersion::getMinorVer() { return mMinorVer; }

void _HttpVersion::setMajorVer(int v) { mMajorVer = v; }

void _HttpVersion::setMinorVer(int v) { mMinorVer = v; }

String _HttpVersion::toString() {
    String version = st(HttpText)::ContentHttp->append(
        "/", createString(mMajorVer), ".", createString(mMinorVer));
    return version;
}

} // namespace obotcha
