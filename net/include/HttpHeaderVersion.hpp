#ifndef __OBOTCHA_HTTP_VERSION_HPP__
#define __OBOTCHA_HTTP_VERSION_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "HashMap.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderVersion) {
public:
    _HttpHeaderVersion();
    _HttpHeaderVersion(int major,int minor);
    void setMajorVer(int);
    void setMinorVer(int);

    int getMajorVer();
    int getMinorVer();

    void import(String);
    
    String toString();
private:

    int mMajorVer;
    int mMinorVer;
};
}

#endif
