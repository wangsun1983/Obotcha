#include "HttpCookie.hpp"

namespace obotcha {

const String _HttpCookie::COOKIE_SECURE = "Secure";

const String _HttpCookie::COOKIE_HTTPONLY = "HttpOnly";

const String _HttpCookie::COOKIE_PATH = "Path";

const String _HttpCookie::COOKIE_DOMAIN = "Domain";

//May no use
const String _HttpCookie::COOKIE_EXPIRES = "Expires";

const String _HttpCookie::COOKIE_MAX_AGE = "Max-Age";

_HttpCookie::_HttpCookie() {
    //mCookies = createHashMap<String,String>();
}

void _HttpCookie::setName(String v) {
    mName = v;
}

String _HttpCookie::getName() {
    return mName;
}

void _HttpCookie::setValue(String v) {
    mValue = v;
}

String _HttpCookie::getValue() {
    return mValue;
}

void _HttpCookie::setPath(String v) {
    mPath = v;
}

String _HttpCookie::getPath() {
    return mPath;
}

void _HttpCookie::setDomain(String v) {
    mDomain = v;
}

String _HttpCookie::getDomain() {
    return mDomain;
}

void _HttpCookie::setExpires(String v) {
    mExpires = v;
}

String _HttpCookie::getExpires() {
    return mExpires;
}

void _HttpCookie::setRawExpres(String v) {
    mRawExpires = v;
}

String _HttpCookie::getRawExpires() {
    return mRawExpires;
}

void _HttpCookie::setMaxAge(int v) {
    mMaxAge = v;
}

int _HttpCookie::getMaxAge() {
    return mMaxAge;
}

void _HttpCookie::setSecure(bool v) {
    mSecure = v;
}

bool _HttpCookie::getSecure() {
    return mSecure;
}

void _HttpCookie::setHttpOnly(bool v) {
    mHttpOnly = v;
}

bool _HttpCookie::getHttpOnly() {
    return mHttpOnly;
}

/*
void _HttpCookie::setCookie(String k,String v) {
    mCookies->put(k,v);
}

String _HttpCookie::getCookie(String k) {
    return mCookies->get(k);
}

void _HttpCookie::removeCookie(String k) {
    mCookies->remove(k);
}
*/

String _HttpCookie::genHtml() {
    //name
    String html;

    if(mName != nullptr) {
        html = mName->append("=")
                       ->append(mValue)
                       ->append(";");
    } else {
        html = createString("");
    }

    if(mSecure) {
        html = html->append(COOKIE_SECURE)
                   ->append(";");
    }

    if(mHttpOnly) {
        html = html->append(COOKIE_HTTPONLY)
                   ->append(";");
    }

    if(mDomain != nullptr) {
        html = html->append(COOKIE_DOMAIN)
                   ->append("=")
                   ->append(mDomain)
                   ->append(";");
    }

    if(mPath != nullptr) {
        html = html->append(COOKIE_PATH)
                   ->append("=")
                   ->append(mPath)
                   ->append(";");
    }

    if(mMaxAge != 0) {
        html = html->append(COOKIE_MAX_AGE)
                   ->append("=")
                   ->append(createString(mMaxAge))
                   ->append(";");
    }

    return html;
}

}
