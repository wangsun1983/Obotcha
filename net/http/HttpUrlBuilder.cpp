#include <map>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "HashMap.hpp"
#include "HttpCookie.hpp"
#include "HashMap.hpp"
#include "HttpUrlBuilder.hpp"

namespace obotcha {

_HttpUrlBuilder::_HttpUrlBuilder() {
    //mQueryParams = createHashMap<String,String>();
    mUrl = createHttpUrl();
    //mPort = -1;
}

_HttpUrlBuilder* _HttpUrlBuilder::appendHost(String host) {
    //mHost = host;
    mUrl->setHost(host);
    return this;
}

_HttpUrlBuilder * _HttpUrlBuilder::appendPort(int port) {
    //mPort = port;
    mUrl->setPort(port);
    return this;
}

_HttpUrlBuilder * _HttpUrlBuilder::appendPath(String path) {
    //mPath = path;
    mUrl->setPath(path);
    return this;
}

_HttpUrlBuilder * _HttpUrlBuilder::appendSchema(String schema) {
    //mSchema = schema;
    mUrl->setSchema(schema);
    return this;
}

_HttpUrlBuilder * _HttpUrlBuilder::appendQueryParam(String name,String value) {
    //mQueryParams->put(name,value);
    mUrl->addQuery(name,value);
    return this;
}

_HttpUrlBuilder * _HttpUrlBuilder::appendUser(String user) {
    //mUser = user;
    mUrl->setUser(user);
    return this;
}

_HttpUrlBuilder * _HttpUrlBuilder::appendPassword(String password) {
    //mPassword = password;
    mUrl->setPassword(password);
    return this;
}

HttpUrl _HttpUrlBuilder::genHttpUrl() {
    return mUrl;
}

}

