#ifndef __OBOTCHA_HTTP_COOKIE_HPP__
#define __OBOTCHA_HTTP_COOKIE_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "HttpDate.hpp"

namespace obotcha {


DECLARE_CLASS(HttpCookie) {

public:
    _HttpCookie();
    _HttpCookie(String name,String value);

    void setValue(String key,String value);
    String getName();
    String getValue();

    void setPropertySecure(bool);
    void setPropertyHttpOnly(bool);
    void setPropertyPath(String);
    void setPropertyDomain(String);
    void setPropertyExpires(HttpDate);
    void setPropertyMaxAge(int);

    bool getPropertySecure();
    bool getPropertyHttpOnly();
    String getPropertyPath();
    String getPropertyDomain();
    HttpDate getPropertyExpires();
    int getPropertyMaxAge();

    String toString(int);

    const static String COOKIE_PROPERTY_SECURE;
    const static String COOKIE_PROPERTY_HTTPONLY;
    const static String COOKIE_PROPERTY_PATH;
    const static String COOKIE_PROPERTY_DOMAIN;
    const static String COOKIE_PROPERTY_EXPIRES;
    const static String COOKIE_PROPERTY_MAX_AGE;

private:
    String mPropertyPath;              // optional
    String mPropertyDomain;            // optional
    //String mPropertyExpires;           // optional
    HttpDate mPropertyExpires;
    String mPropertyRawExpires;        // for reading cookies only

    long mPropertyExpiresMillseocnds;

    // MaxAge=0 means no 'Max-Age' attribute specified.
    // MaxAge<0 means delete cookie now, equivalently 'Max-Age: 0'
    // MaxAge>0 means Max-Age attribute present and given in seconds
    int mPropertyMaxAge;

    bool mPropertySecure;

    bool mPropertyHttpOnly;
    
    String mRaw;

    //HashMap<String,String> mValues;
    String mName;
    String mValue;
    
    String genHttpRequestCookie();
    String genHttpResponseCookie();
};

}
#endif