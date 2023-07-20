#ifndef __OBOTCHA_HTTP_VERSION_HPP__
#define __OBOTCHA_HTTP_VERSION_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderVersion) {
public:
    _HttpHeaderVersion();
    _HttpHeaderVersion(int major,int minor);
    void setMajorVer(int);
    void setMinorVer(int);

    int getMajorVer();
    int getMinorVer();

    void load(String);
    
    String toString();
private:

    int mMajorVer;
    int mMinorVer;
};
}

#endif
