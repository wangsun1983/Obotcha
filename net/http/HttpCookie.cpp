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

String _HttpCookie::genServerCookieString() {
    //name
    String content = createString("Set-Cookie: ");
    MapIterator<String,String> iterator = mValues->getIterator();
    while(iterator->hasValue()) {
        String key = iterator->getKey();
        String value = iterator->getKey();
        content = content->append(key,"=",value,";");
        iterator->next();
    }

    if(mPropertyHttpOnly) {
        content = content->append(COOKIE_PROPERTY_HTTPONLY,";");
    }

    if(mPropertySecure) {
        content = content->append(COOKIE_PROPERTY_SECURE,";");
    }

    if(mPropertyDomain != nullptr) {
        content = content->append(COOKIE_PROPERTY_DOMAIN,"=",mPropertyDomain,";");
    }

    if(mPropertyPath != nullptr) {
        content = content->append(COOKIE_PROPERTY_PATH,"=",mPropertyPath,";");
    }

    if(mPropertyMaxAge != 0) {
        content = content->append(COOKIE_PROPERTY_MAX_AGE,"=",createString(mPropertyMaxAge),";");
    }

    if(mPropertyExpiresMillseocnds != 0) {
        Calendar c = createCalendar(mPropertyExpiresMillseocnds);
        DateTime date = c->getGmtDateTime();
        String time = date->toString(st(DateTime)::FormatHTTP);//st(DateTimeFormatter)::format(date,DateTimeFormatHTTP);

        content = content->append(COOKIE_PROPERTY_EXPIRES,"=",time,";");
    }

    return content;
}

String _HttpCookie::genClientCookieString() {
    String content = createString("Cookie: ");
    MapIterator<String,String> iterator = mValues->getIterator();
    while(iterator->hasValue()) {
        String key = iterator->getKey();
        String value = iterator->getKey();
        content = content->append(key,"=",value,";"); //TODO:Cookie: name=value; name2=value2  
        iterator->next();
    }

    return content;
}

}
