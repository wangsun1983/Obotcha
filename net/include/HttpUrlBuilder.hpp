#ifndef __OBOTCHA_HTTP_URL_BUILDER_HPP__
#define __OBOTCHA_HTTP_URL_BUILDER_HPP__

#include <map>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "HashMap.hpp"
#include "HttpCookie.hpp"
#include "HashMap.hpp"
#include "HttpUrl.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpUrlBuilder) {

public:
    _HttpUrlBuilder();
    _HttpUrlBuilder* appendHost(String);
    _HttpUrlBuilder* appendPort(int port);
    _HttpUrlBuilder* appendPath(String);
    _HttpUrlBuilder* appendSchema(String);
    _HttpUrlBuilder* appendQueryParam(String name,String value);
    _HttpUrlBuilder* appendUser(String);
    _HttpUrlBuilder* appendPassword(String);

    HttpUrl genHttpUrl();

private:
/*
    HashMap<String,String> mQueryParams;
    String mHost;
    int mPort;
    String mPath;
    String mSchema;
    String mUser;
    String mPassword;
    */
    HttpUrl mUrl;
};

}
#endif
