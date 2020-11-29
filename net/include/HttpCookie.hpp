#ifndef __OBOTCHA_HTTP_COOKIE_HPP__
#define __OBOTCHA_HTTP_COOKIE_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HashMap.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpCookie) {

public:
    _HttpCookie();

    void setName(String);
    String getName();

    void setValue(String);
    String getValue();

    void setPath(String);
    String getPath();

    void setDomain(String);
    String getDomain();

    void setExpires(long millsconds);
    long getExpires();

    void setRawExpres(String);
    String getRawExpires();

    void setMaxAge(int);
    int getMaxAge();

    void setSecure(bool);
    bool getSecure();

    void setHttpOnly(bool);
    bool getHttpOnly();

    //void setCookie(String,String);
    //String getCookie(String);
    //void removeCookie(String);

    String genHtml();

    void dump();

    const static String COOKIE_SECURE;
    const static String COOKIE_HTTPONLY;
    const static String COOKIE_PATH;
    const static String COOKIE_DOMAIN;
    const static String COOKIE_EXPIRES;
    const static String COOKIE_MAX_AGE;

private:
    String mName;
    String mValue;
    String mPath;              // optional
    String mDomain;            // optional
    String mExpires;           // optional
    String mRawExpires;        // for reading cookies only

    long mExpiresMillseocnds;

    // MaxAge=0 means no 'Max-Age' attribute specified.
    // MaxAge<0 means delete cookie now, equivalently 'Max-Age: 0'
    // MaxAge>0 means Max-Age attribute present and given in seconds
    int mMaxAge;

    bool mSecure;

    bool mHttpOnly;
    
    String mRaw;
};

}
#endif
