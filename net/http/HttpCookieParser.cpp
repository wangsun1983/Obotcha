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

    while (pos < value->size()) {
        int tokenStart = pos;
        pos = st(HttpHeaderContentParser)::skipUntil(value, pos,
                                                     createString("=,;"));
        String directive =
            value->subString(tokenStart, pos - tokenStart)->trim();
        String parameter = nullptr;

        if (pos == value->size() || value->charAt(pos) == ',' ||
            value->charAt(pos) == ';') {
            pos++; // consume ',' or ';' (if necessary)
            parameter = nullptr;
        } else {
            pos++; // consume '='
            pos = st(HttpHeaderContentParser)::skipWhitespace(value, pos);
            // quoted string
            if (pos < value->size() && value->charAt(pos) == '\"') {
                pos++; // consume '"' open quote
                int parameterStart = pos;
                pos = st(HttpHeaderContentParser)::skipUntil(
                    value, pos, createString("\""));
                parameter = value->subString(parameterStart, pos);
                pos++; // consume '"' close quote (if necessary)
                // unquoted string
            } else {
                int parameterStart = pos;
                if (directive->endsWithIgnoreCase(
                        st(HttpCookie)::COOKIE_PROPERTY_EXPIRES)) {
                    pos = st(HttpHeaderContentParser)::skipUntil(
                        value, pos, createString(";"));
                } else {
                    pos = st(HttpHeaderContentParser)::skipUntil(
                        value, pos, createString(",;"));
                }
                parameter =
                    value->subString(parameterStart, (pos - parameterStart))
                        ->trim();
                pos++;
            }
        }
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
            cookies->add(createHttpCookie(directive, parameter));
        }
    }

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
