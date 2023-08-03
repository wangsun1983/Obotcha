#ifndef __OBOTCHA_HTTP_VERSION_HPP__
#define __OBOTCHA_HTTP_VERSION_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderVersion) {
public:
    _HttpHeaderVersion() = default;
    _HttpHeaderVersion(int major,int minor);
    void setMajorVer(int);
    void setMinorVer(int);

    int getMajorVer() const;
    int getMinorVer() const;

    void load(String);
    
    String toString() override;
private:

    int mMajorVer = 0;
    int mMinorVer = 0;
};
}

#endif
