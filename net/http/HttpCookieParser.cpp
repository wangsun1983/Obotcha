#include "HttpCookieParser.hpp"
#include "HttpHeaderContentParser.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

ArrayList<HttpCookie> _HttpCookieParser::parse(String value) {
    bool mPropertySecure = false;
    bool mPropertyHttpOnly = false;
    String mPropertyPath = nullptr;
    String mPropertyDomain = nullptr;
    HttpDate mPropertyExpires = nullptr;
    int mPropertyMaxAge = -1;
    ArrayList<HttpCookie> cookies = ArrayList<HttpCookie>::New();
    st(HttpHeaderContentParser)::load(value,
                                        String::New("=;"), /*skip directive*/
                                        String::New(";"),  /*skip paramter*/
        [&mPropertySecure,
         &mPropertyHttpOnly,
         &mPropertyPath,
         &mPropertyDomain,
         &mPropertyExpires,
         &mPropertyMaxAge,
         &cookies](String directive,String parameter) {
        if (st(HttpCookie)::COOKIE_PROPERTY_SECURE->equalsIgnoreCase(directive)) {
            mPropertySecure = true;
        } else if (st(HttpCookie)::COOKIE_PROPERTY_HTTPONLY->equalsIgnoreCase(directive)) {
            mPropertyHttpOnly = true;
        } else if (st(HttpCookie)::COOKIE_PROPERTY_PATH->equalsIgnoreCase(directive)) {
            mPropertyPath = parameter;
        } else if (st(HttpCookie)::COOKIE_PROPERTY_DOMAIN->equalsIgnoreCase(directive)) {
            mPropertyDomain = parameter;
        } else if (st(HttpCookie)::COOKIE_PROPERTY_EXPIRES->equalsIgnoreCase(directive)) {
            mPropertyExpires = HttpDate::New(parameter);
        } else if (st(HttpCookie)::COOKIE_PROPERTY_MAX_AGE->equalsIgnoreCase(directive)) {
            mPropertyMaxAge = st(HttpHeaderContentParser)::parseSeconds(parameter, 
                                                                        st(Integer)::kMaxValue);
        } else {
            if(parameter == nullptr) {
                parameter = String::New("");
            }
            cookies->add(HttpCookie::New(directive, parameter));
        }
    });

    ForEveryOne(cookie,cookies) {
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
    }
    return cookies;
}

} // namespace obotcha
