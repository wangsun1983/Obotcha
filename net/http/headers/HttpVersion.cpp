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

void _HttpVersion::import(String s) {
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
    

String _HttpVersion::toString() {
    String version = st(HttpText)::ContentHttp->append(
        "/", createString(mMajorVer), ".", createString(mMinorVer));
    return version;
}

} // namespace obotcha
