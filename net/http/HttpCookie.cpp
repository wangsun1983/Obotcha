#include "HttpCookie.hpp"
#include "Calendar.hpp"
#include "HttpProtocol.hpp"
#include "HttpHeaderContentParser.hpp"

namespace obotcha {

const String _HttpCookie::COOKIE_PROPERTY_SECURE = createString("Secure");

const String _HttpCookie::COOKIE_PROPERTY_HTTPONLY = createString("HttpOnly");

const String _HttpCookie::COOKIE_PROPERTY_PATH = createString("Path");

const String _HttpCookie::COOKIE_PROPERTY_DOMAIN = createString("Domain");

//May no use
const String _HttpCookie::COOKIE_PROPERTY_EXPIRES = createString("Expires");

const String _HttpCookie::COOKIE_PROPERTY_MAX_AGE = createString("Max-Age");

_HttpCookie::_HttpCookie() {
    mValues = createHashMap<String,String>();
    mPropertySecure = false;
    mPropertyHttpOnly = false;
    mPropertyExpiresMillseocnds = -1;
}

_HttpCookie::_HttpCookie(String value) {
    mValues = createHashMap<String,String>();
    mPropertySecure = false;
    mPropertyHttpOnly = false;
    mPropertyExpiresMillseocnds = -1;
    import(value);
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

void _HttpCookie::setPropertyExpires(HttpDate date) {
    mPropertyExpires = date;

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

HttpDate _HttpCookie::getPropertyExpires() {
    return mPropertyExpires;
}

int _HttpCookie::getPropertyMaxAge() {
    return mPropertyMaxAge;
}

void _HttpCookie::import(String value) {
    int pos = 0;
    while (pos < value->size()) {
        int tokenStart = pos;
        pos = st(HttpHeaderContentParser)::skipUntil(value, pos, createString("=,;"));
        String directive = value->subString(tokenStart, pos-tokenStart)->trim();
        String parameter = nullptr;

        if (pos == value->size() || value->charAt(pos) == ',' || value->charAt(pos) == ';') {
            pos++; // consume ',' or ';' (if necessary)
            parameter = nullptr;
        } else {
            pos++; // consume '='
            pos = st(HttpHeaderContentParser)::skipWhitespace(value, pos);
            // quoted string
            if (pos < value->size() && value->charAt(pos) == '\"') {
                pos++; // consume '"' open quote
                int parameterStart = pos;
                pos = st(HttpHeaderContentParser)::skipUntil(value, pos, createString("\""));
                parameter = value->subString(parameterStart, pos);
                pos++; // consume '"' close quote (if necessary)
                // unquoted string
            } else {
                int parameterStart = pos;
                if(directive->endsWithIgnoreCase(st(HttpCookie)::COOKIE_PROPERTY_EXPIRES)) {
                    pos = st(HttpHeaderContentParser)::skipUntil(value, pos, createString(";"));
                } else {
                    pos = st(HttpHeaderContentParser)::skipUntil(value, pos, createString(",;"));
                }
                parameter = value->subString(parameterStart, (pos-parameterStart))->trim();
                pos++;
            }
        }
        if (COOKIE_PROPERTY_SECURE->equalsIgnoreCase(directive)) {
            mPropertySecure = true;
        } else if (COOKIE_PROPERTY_HTTPONLY->equalsIgnoreCase(directive)) {
            mPropertyHttpOnly = true;
        } else if (COOKIE_PROPERTY_PATH->equalsIgnoreCase(directive)) {
            mPropertyPath = parameter;
        } else if (COOKIE_PROPERTY_DOMAIN->equalsIgnoreCase(directive)) {
            mPropertyDomain = parameter;
        } else if (COOKIE_PROPERTY_EXPIRES->equalsIgnoreCase(directive)) {
            mPropertyExpires = createHttpDate(parameter);
        } else if (COOKIE_PROPERTY_MAX_AGE->equalsIgnoreCase(directive)) {
            mPropertyMaxAge = st(HttpHeaderContentParser)::parseSeconds(parameter, st(Integer)::MAX_VALUE);
        } else {
            mValues->put(directive,parameter);
        }
    }
}

String _HttpCookie::toString(int type) {
    switch(type) {
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
    printf("%s \n",dumpvalue->toChars());
}

String _HttpCookie::genHttpResponseCookie() {
    //name
    String content = createString("Set-Cookie: ");
    MapIterator<String,String> iterator = mValues->getIterator();
    while(iterator->hasValue()) {
        String key = iterator->getKey();
        String value = iterator->getValue();
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

    if(mPropertyExpiresMillseocnds != -1) {
        Calendar c = createCalendar(mPropertyExpiresMillseocnds);
        DateTime date = c->getGmtDateTime();
        String time = date->toString(st(DateTime)::FormatHTTP);//st(DateTimeFormatter)::format(date,DateTimeFormatHTTP);

        content = content->append(COOKIE_PROPERTY_EXPIRES,"=",time,";");
    }

    return content;
}

String _HttpCookie::genHttpRequestCookie() {
    String content = createString("Cookie: ");
    MapIterator<String,String> iterator = mValues->getIterator();
    while(iterator->hasValue()) {
        String key = iterator->getKey();
        String value = iterator->getValue();
        content = content->append(key,"=",value,";"); //TODO:Cookie: name=value; name2=value2  
        iterator->next();
    }
    return content;
}


}
