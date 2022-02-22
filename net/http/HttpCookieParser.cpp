#include "HttpCookieParser.hpp"
#include "HttpHeaderContentParser.hpp"

namespace obotcha {

ArrayList<HttpCookie> _HttpCookieParser::parse(String value) {
    int pos = 0;
    bool mPropertySecure = false;
    bool mPropertyHttpOnly = false;
    String mPropertyPath = nullptr;
    String mPropertyDomain = nullptr;
    HttpDate mPropertyExpires = nullptr;
    int mPropertyMaxAge = -1;
    ArrayList<HttpCookie> cookies = createArrayList<HttpCookie>();
    st(HttpHeaderContentParser)::import(value,
                                        createString("=;"), /*skip directive*/
                                        createString(";"),  /*skip paramter*/
        [&](String directive,String parameter) {
        if (st(HttpCookie)::COOKIE_PROPERTY_SECURE->equalsIgnoreCase(
                directive)) {
            mPropertySecure = true;
        } else if (st(HttpCookie)::COOKIE_PROPERTY_HTTPONLY->equalsIgnoreCase(
                       directive)) {
            mPropertyHttpOnly = true;
        } else if (st(HttpCookie)::COOKIE_PROPERTY_PATH->equalsIgnoreCase(
                       directive)) {
            mPropertyPath = parameter;
        } else if (st(HttpCookie)::COOKIE_PROPERTY_DOMAIN->equalsIgnoreCase(
                       directive)) {
            mPropertyDomain = parameter;
        } else if (st(HttpCookie)::COOKIE_PROPERTY_EXPIRES->equalsIgnoreCase(
                       directive)) {
            mPropertyExpires = createHttpDate(parameter);
        } else if (st(HttpCookie)::COOKIE_PROPERTY_MAX_AGE->equalsIgnoreCase(
                       directive)) {
            mPropertyMaxAge = st(HttpHeaderContentParser)::parseSeconds(
                parameter, st(Integer)::MAX_VALUE);
        } else {
            // mValues->put(directive,parameter);
            // mName = directive;
            // mValue = parameter;
            if(parameter == nullptr) {
                parameter = createString("");
            }
            cookies->add(createHttpCookie(directive, parameter));
        }
    });

    auto iterator = cookies->getIterator();
    while (iterator->hasValue()) {
        auto cookie = iterator->getValue();
        cookie->setPropertySecure(mPropertySecure);
        cookie->setPropertyHttpOnly(mPropertyHttpOnly);
        if (mPropertyPath != nullptr) {
            cookie->setPropertyPath(mPropertyPath);
        }

        if (mPropertyDomain != nullptr) {
            cookie->setPropertyDomain(mPropertyDomain);
        }

        if (mPropertyExpires != nullptr) {
            cookie->setPropertyExpires(mPropertyExpires);
        }

        if (mPropertyMaxAge != -1) {
            cookie->setPropertyMaxAge(mPropertyMaxAge);
        }
        iterator->next();
    }

    return cookies;
}

} // namespace obotcha
