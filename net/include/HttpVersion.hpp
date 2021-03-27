#ifndef __OBOTCHA_HTTP_VERSION_HPP__
#define __OBOTCHA_HTTP_VERSION_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "HashMap.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpVersion) {
public:
    _HttpVersion();
    _HttpVersion(int major,int minor);
    void setMajorVer(int);
    void setMinorVer(int);

    int getMajorVer();
    int getMinorVer();

    String toString();
private:

    int mMajorVer;
    int mMinorVer;
};
}

#endif
