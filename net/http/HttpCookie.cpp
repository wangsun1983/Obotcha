#include "HttpCookie.hpp"
#include "HttpPacket.hpp"
#include "StringBuffer.hpp"

namespace obotcha {

const String _HttpCookie::COOKIE_PROPERTY_SECURE = createString("Secure");

const String _HttpCookie::COOKIE_PROPERTY_HTTPONLY = createString("HttpOnly");

const String _HttpCookie::COOKIE_PROPERTY_PATH = createString("Path");

const String _HttpCookie::COOKIE_PROPERTY_DOMAIN = createString("Domain");

// May no use
const String _HttpCookie::COOKIE_PROPERTY_EXPIRES = createString("Expires");

const String _HttpCookie::COOKIE_PROPERTY_MAX_AGE = createString("Max-Age");


_HttpCookie::_HttpCookie(String name, String value):mName(name),mValue(value) {
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

bool _HttpCookie::getPropertySecure() const { 
    return mPropertySecure; 
}

bool _HttpCookie::getPropertyHttpOnly() const { 
    return mPropertyHttpOnly; 
}

String _HttpCookie::getPropertyPath() const { 
    return mPropertyPath; 
}

String _HttpCookie::getPropertyDomain() const { 
    return mPropertyDomain; 
}

HttpDate _HttpCookie::getPropertyExpires() const { 
    return mPropertyExpires; 
}

int _HttpCookie::getPropertyMaxAge() const { 
    return mPropertyMaxAge; 
}

String _HttpCookie::toString(st(Http)::PacketType type) {
    switch (type) {
        case st(Http)::PacketType::Request:
            return genHttpRequestCookie();
            
        case st(Http)::PacketType::Response:
            return genHttpResponseCookie();
        
        default:
            return nullptr;
    }
}

String _HttpCookie::genHttpResponseCookie() {
    // name
    StringBuffer content = createStringBuffer();
    content->append(mName,"=", mValue, ";");

    if (mPropertyHttpOnly) {
        content->append(COOKIE_PROPERTY_HTTPONLY, ";");
    }

    if (mPropertySecure) {
        content->append(COOKIE_PROPERTY_SECURE, ";");
    }

    if (mPropertyDomain != nullptr) {
        content->append(COOKIE_PROPERTY_DOMAIN, "=", mPropertyDomain, ";");
    }

    if (mPropertyPath != nullptr) {
        content->append(COOKIE_PROPERTY_PATH, "=", mPropertyPath, ";");
    }

    if (mPropertyMaxAge != -1) {
        content->append(COOKIE_PROPERTY_MAX_AGE, 
                                  "=",
                                  createString(mPropertyMaxAge), ";");
    }

    if (mPropertyExpires != nullptr) {
        content->append(COOKIE_PROPERTY_EXPIRES, "=", mPropertyExpires->toString(), ";");
    }

    return content->subString(0,content->size() - 1)->toString();
}

String _HttpCookie::genHttpRequestCookie() {
    return mName->append("=", mValue,";"); 
}

} // namespace obotcha
