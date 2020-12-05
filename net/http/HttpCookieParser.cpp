#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HashMap.hpp"
#include "HttpCookie.hpp"
#include "HttpCookieParser.hpp"

namespace obotcha {

HttpCookie _HttpCookieParser::parseCookie(String content) {
    HttpCookie cookie = createHttpCookie();

    ArrayList<String> params = content->split(";");
    if(params != nullptr) {
        ListIterator<String> iterator = params->getIterator();
        while(iterator->hasValue()) {
            String value = iterator->getValue();
            parseLine(cookie,value);
            iterator->next();
        }
    } else {
        parseLine(cookie,content);
    }

    return cookie;
}

void _HttpCookieParser::parseLine(HttpCookie cookie,String value) {
    ArrayList<String> cookievalue = value->split("=");
    String name = nullptr;
    if(cookievalue == nullptr) {
        name = value;
    } else {
        name = cookievalue->get(0)->trimAll();
    }

    if(name->equalsIgnoreCase(st(HttpCookie)::COOKIE_PROPERTY_SECURE)) {
        cookie->setPropertySecure(true);
    } else if(name->equalsIgnoreCase(st(HttpCookie)::COOKIE_PROPERTY_HTTPONLY)) {
        cookie->setPropertyHttpOnly(true);
    } else if(name->equalsIgnoreCase(st(HttpCookie)::COOKIE_PROPERTY_PATH)) {
        cookie->setPropertyPath(cookievalue->get(1)->trimAll());
    } else if(name->equalsIgnoreCase(st(HttpCookie)::COOKIE_PROPERTY_DOMAIN)) {
        cookie->setPropertyDomain(cookievalue->get(1)->trimAll());
    } else if(name->equalsIgnoreCase(st(HttpCookie)::COOKIE_PROPERTY_EXPIRES)) {
        cookie->setPropertyExpires(cookievalue->get(1)->trimAll());
    } else if(name->equalsIgnoreCase(st(HttpCookie)::COOKIE_PROPERTY_MAX_AGE)) {
        cookie->setPropertyMaxAge(cookievalue->get(1)->trimAll());
    } else {
        cookie->setValue(name,cookievalue->get(1)->trimAll());
    }
}

};

