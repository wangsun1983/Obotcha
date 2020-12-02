#include "HttpCookie.hpp"
#include "Calendar.hpp"

namespace obotcha {

const String _HttpCookie::COOKIE_PROPERTY_SECURE = "Secure";

const String _HttpCookie::COOKIE_PROPERTY_HTTPONLY = "HttpOnly";

const String _HttpCookie::COOKIE_PROPERTY_PATH = "Path";

const String _HttpCookie::COOKIE_PROPERTY_DOMAIN = "Domain";

//May no use
const String _HttpCookie::COOKIE_PROPERTY_EXPIRES = "Expires";

const String _HttpCookie::COOKIE_PROPERTY_MAX_AGE = "Max-Age";

_HttpCookie::_HttpCookie() {
    mValues = createHashMap<String,String>();
    mPropertySecure = false;
    mPropertyHttpOnly = false;
}

void _HttpCookie::setValue(String key,String value) {
    mValues->put(key,value);
}

String _HttpCookie::get(String key) {
    return mValues->get(key);
}

void _HttpCookie::setPropertySecure(bool flag) {
    mPropertySecure = flag;
}

void _HttpCookie::setPropertyHttpOnly(bool flag) {
    mPropertyHttpOnly = flag;
}

void _HttpCookie::setPropertyPath(String data) {
    mPropertyPath = data;
}

void _HttpCookie::setPropertyDomain(String data) {
    mPropertyDomain = data;
}

void _HttpCookie::setPropertyExpires(String data) {
    mPropertyExpires = data;
}

void _HttpCookie::setPropertyMaxAge(String data) {
    mPropertyMaxAge = data->toBasicInt();
}

bool _HttpCookie::getPropertySecure() {
    return mPropertySecure;
}

bool _HttpCookie::getPropertyHttpOnly() {
    return mPropertyHttpOnly;
}

String _HttpCookie::getPropertyPath() {
    return mPropertyPath;
}

String _HttpCookie::getPropertyDomain() {
    return mPropertyDomain;
}

String _HttpCookie::getPropertyExpires() {
    return mPropertyExpires;
}

int _HttpCookie::getPropertyMaxAge() {
    return mPropertyMaxAge;
}


String _HttpCookie::genHtml() {
    //name
    String html;
/*
    if(mName != nullptr) {
        html = mName->append("=",mValue,";");
    } else {
        html = createString("");
    }

    if(mSecure) {
        html = html->append(COOKIE_SECURE,";");
    }

    if(mHttpOnly) {
        html = html->append(COOKIE_HTTPONLY,";");
    }

    if(mDomain != nullptr) {
        html = html->append(COOKIE_DOMAIN,"=",mDomain,";");
    }

    if(mPath != nullptr) {
        html = html->append(COOKIE_PATH,"=",mPath,";");
    }

    if(mMaxAge != 0) {
        html = html->append(COOKIE_MAX_AGE,"=",createString(mMaxAge),";");
    }

    if(mExpiresMillseocnds != 0) {
        Calendar c = createCalendar(mExpiresMillseocnds);
        DateTime date = c->getGmtDateTime();
        String time = date->toString(st(DateTime)::FormatHTTP);//st(DateTimeFormatter)::format(date,DateTimeFormatHTTP);

        html = html->append(COOKIE_EXPIRES,"=",time,";");
    }
 */
    return html;
}

}
