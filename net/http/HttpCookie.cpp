#include "HttpCookie.hpp"
#include "Calendar.hpp"
#include "HttpHeaderContentParser.hpp"
#include "HttpPacket.hpp"

namespace obotcha {

const String _HttpCookie::COOKIE_PROPERTY_SECURE = createString("Secure");

const String _HttpCookie::COOKIE_PROPERTY_HTTPONLY = createString("HttpOnly");

const String _HttpCookie::COOKIE_PROPERTY_PATH = createString("Path");

const String _HttpCookie::COOKIE_PROPERTY_DOMAIN = createString("Domain");

// May no use
const String _HttpCookie::COOKIE_PROPERTY_EXPIRES = createString("Expires");

const String _HttpCookie::COOKIE_PROPERTY_MAX_AGE = createString("Max-Age");

_HttpCookie::_HttpCookie():_HttpCookie(nullptr,nullptr) {
}

_HttpCookie::_HttpCookie(String name, String value) {
    mName = name;
    mValue = value;
    mPropertySecure = false;
    mPropertyHttpOnly = false;
    mPropertyExpires = nullptr;
    mPropertyMaxAge = -1;
}

void _HttpCookie::setValue(String name, String value) {
    mName = name;
    mValue = value;
}

String _HttpCookie::getName() { 
    return mName; 
}

String _HttpCookie::getValue() { 
    return mValue; 
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

void _HttpCookie::setPropertyExpires(HttpDate date) { 
    mPropertyExpires = date; 
}

void _HttpCookie::setPropertyMaxAge(int data) { 
    mPropertyMaxAge = data; 
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

HttpDate _HttpCookie::getPropertyExpires() { 
    return mPropertyExpires; 
}

int _HttpCookie::getPropertyMaxAge() { 
    return mPropertyMaxAge; 
}

String _HttpCookie::toString(int type) {
    switch (type) {
    case st(HttpPacket)::Request:
        return genHttpRequestCookie();
        break;

    case st(HttpPacket)::Response:
        return genHttpResponseCookie();
        break;
    }

    return nullptr;
}

String _HttpCookie::genHttpResponseCookie() {
    // name
    String content = createString(mName)->append("=", mValue, ";");
    //    iterator->next();
    //}

    if (mPropertyHttpOnly) {
        content = content->append(COOKIE_PROPERTY_HTTPONLY, ";");
    }

    if (mPropertySecure) {
        content = content->append(COOKIE_PROPERTY_SECURE, ";");
    }

    if (mPropertyDomain != nullptr) {
        content =
            content->append(COOKIE_PROPERTY_DOMAIN, "=", mPropertyDomain, ";");
    }

    if (mPropertyPath != nullptr) {
        content =
            content->append(COOKIE_PROPERTY_PATH, "=", mPropertyPath, ";");
    }

    if (mPropertyMaxAge != -1) {
        content = content->append(COOKIE_PROPERTY_MAX_AGE, "=",
                                  createString(mPropertyMaxAge), ";");
    }

    if (mPropertyExpires != nullptr) {
        content = content->append(COOKIE_PROPERTY_EXPIRES, "=", mPropertyExpires->toString(), ";");
    }

    content = content->subString(0,content->size() - 1);
    return content;
}

String _HttpCookie::genHttpRequestCookie() {
    String content = createString("Cookie: ");
    content = content->append(mName, "=", mValue,
                              ";"); // TODO:Cookie: name=value; name2=value2
    return content;
}

} // namespace obotcha
