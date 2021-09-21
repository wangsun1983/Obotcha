#include "HttpCookie.hpp"
#include "Calendar.hpp"
#include "HttpHeaderContentParser.hpp"
#include "HttpProtocol.hpp"

namespace obotcha {

const String _HttpCookie::COOKIE_PROPERTY_SECURE = createString("Secure");

const String _HttpCookie::COOKIE_PROPERTY_HTTPONLY = createString("HttpOnly");

const String _HttpCookie::COOKIE_PROPERTY_PATH = createString("Path");

const String _HttpCookie::COOKIE_PROPERTY_DOMAIN = createString("Domain");

// May no use
const String _HttpCookie::COOKIE_PROPERTY_EXPIRES = createString("Expires");

const String _HttpCookie::COOKIE_PROPERTY_MAX_AGE = createString("Max-Age");

_HttpCookie::_HttpCookie() {
    mPropertySecure = false;
    mPropertyHttpOnly = false;
    mPropertyExpiresMillseocnds = -1;
}

_HttpCookie::_HttpCookie(String name, String value) {
    mPropertySecure = false;
    mPropertyHttpOnly = false;
    mPropertyExpiresMillseocnds = -1;
    mName = name;
    mValue = value;
}

void _HttpCookie::setValue(String name, String value) {
    mName = name;
    mValue = value;
}

String _HttpCookie::getName() { return mName; }

String _HttpCookie::getValue() { return mValue; }

void _HttpCookie::setPropertySecure(bool flag) { mPropertySecure = flag; }

void _HttpCookie::setPropertyHttpOnly(bool flag) { mPropertyHttpOnly = flag; }

void _HttpCookie::setPropertyPath(String data) { mPropertyPath = data; }

void _HttpCookie::setPropertyDomain(String data) { mPropertyDomain = data; }

void _HttpCookie::setPropertyExpires(HttpDate date) { mPropertyExpires = date; }

void _HttpCookie::setPropertyMaxAge(int data) { mPropertyMaxAge = data; }

bool _HttpCookie::getPropertySecure() { return mPropertySecure; }

bool _HttpCookie::getPropertyHttpOnly() { return mPropertyHttpOnly; }

String _HttpCookie::getPropertyPath() { return mPropertyPath; }

String _HttpCookie::getPropertyDomain() { return mPropertyDomain; }

HttpDate _HttpCookie::getPropertyExpires() { return mPropertyExpires; }

int _HttpCookie::getPropertyMaxAge() { return mPropertyMaxAge; }

String _HttpCookie::toString(int type) {
    switch (type) {
    case st(HttpProtocol)::HttpRequest:
        return genHttpRequestCookie();
        break;

    case st(HttpProtocol)::HttpResponse:
        return genHttpResponseCookie();
        break;
    }

    return nullptr;
}

void _HttpCookie::dump() {
    String dumpvalue = genHttpRequestCookie();
    printf("%s \n", dumpvalue->toChars());
}

String _HttpCookie::genHttpResponseCookie() {
    // name
    String content = createString("Set-Cookie: ");
    // MapIterator<String,String> iterator = mValues->getIterator();
    // while(iterator->hasValue()) {
    //    String key = iterator->getKey();
    //    String value = iterator->getValue();
    content = content->append(mName, "=", mValue, ";");
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

    if (mPropertyMaxAge != 0) {
        content = content->append(COOKIE_PROPERTY_MAX_AGE, "=",
                                  createString(mPropertyMaxAge), ";");
    }

    if (mPropertyExpiresMillseocnds != -1) {
        Calendar c = createCalendar(mPropertyExpiresMillseocnds);
        DateTime date = c->getGmtDateTime();
        String time = date->toString(
            st(DateTime)::
                FormatHTTP); // st(DateTimeFormatter)::format(date,DateTimeFormatHTTP);

        content = content->append(COOKIE_PROPERTY_EXPIRES, "=", time, ";");
    }

    return content;
}

String _HttpCookie::genHttpRequestCookie() {
    String content = createString("Cookie: ");
    // MapIterator<String,String> iterator = mValues->getIterator();
    // while(iterator->hasValue()) {
    //    String key = iterator->getKey();
    //    String value = iterator->getValue();
    content = content->append(mName, "=", mValue,
                              ";"); // TODO:Cookie: name=value; name2=value2
    //    iterator->next();
    //}
    return content;
}

} // namespace obotcha
