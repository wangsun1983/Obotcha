#include "Object.hpp"
#include "StrongPointer.hpp"

#include "HttpText.hpp"
#include "HttpHeaderVersion.hpp"
#include "String.hpp"

namespace obotcha {

_HttpHeaderVersion::_HttpHeaderVersion() {
    mMajorVer = 1;
    mMinorVer = 1;
}

_HttpHeaderVersion::_HttpHeaderVersion(int major, int minor) {
    mMajorVer = major;
    mMinorVer = minor;
}

int _HttpHeaderVersion::getMajorVer() { return mMajorVer; }

int _HttpHeaderVersion::getMinorVer() { return mMinorVer; }

void _HttpHeaderVersion::setMajorVer(int v) { mMajorVer = v; }

void _HttpHeaderVersion::setMinorVer(int v) { mMinorVer = v; }

void _HttpHeaderVersion::import(String s) {
    ArrayList<String> strings = s->trim()->split("/");
    if (strings == nullptr || strings->size() != 2) {
        return;
    }

    String versions = strings->get(1);
    ArrayList<String> vstrings = versions->split(".");
    if (vstrings->size() != 2) {
        return;
    }

    String major = vstrings->get(0);
    String minor = vstrings->get(1);
    mMajorVer = major->toBasicInt();
    mMinorVer = minor->toBasicInt();
}
    

String _HttpHeaderVersion::toString() {
    String version = st(HttpText)::ContentHttp->append(
        "/", createString(mMajorVer), ".", createString(mMinorVer));
    return version;
}

} // namespace obotcha
