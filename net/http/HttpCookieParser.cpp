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
    ListIterator<String> iterator = params->getIterator();
    while(iterator->hasValue()) {
        String value = iterator->getValue();
        ArrayList<String> cookievalue = value->split("=");
        String name = cookievalue->get(0)->trimAll();
        printf("name is %s \n",name->toChars());
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
        iterator->next();
    }

    return cookie;
}

};

