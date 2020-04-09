#include "HttpCookie.hpp"
#include "Calendar.hpp"

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
    mExpiresMillseocnds = 0;
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

void _HttpCookie::setExpires(long v) {
    mExpiresMillseocnds = v;
}

long _HttpCookie::getExpires() {
    return mExpiresMillseocnds;
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

    if(mExpiresMillseocnds != 0) {
        Calendar c = createCalendar(mExpiresMillseocnds);
        DateTime date = c->getGmtDateTime();
        String time = date->toString(st(DateTime)::FormatHTTP);//st(DateTimeFormatter)::format(date,DateTimeFormatHTTP);

        html = html->append(COOKIE_EXPIRES)
                   ->append("=")
                   ->append(time)
                   ->append(";");
    }

    return html;
}

}
