#include <map>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ArrayList.hpp"
#include "HashMap.hpp"
#include "HttpCookie.hpp"
#include "HttpUrlBuilder.hpp"
#include "String.hpp"

namespace obotcha {

_HttpUrlBuilder::_HttpUrlBuilder() { mUrl = createHttpUrl(); }

_HttpUrlBuilder *_HttpUrlBuilder::appendHost(String host) {
    mUrl->setHost(host);
    return this;
}

_HttpUrlBuilder *_HttpUrlBuilder::appendPort(int port) {
    mUrl->setPort(port);
    return this;
}

_HttpUrlBuilder *_HttpUrlBuilder::appendPath(String path) {
    mUrl->setPath(path);
    return this;
}

_HttpUrlBuilder *_HttpUrlBuilder::appendSchema(String schema) {
    mUrl->setSchema(schema);
    return this;
}

_HttpUrlBuilder *_HttpUrlBuilder::appendQueryParam(String name, String value) {
    mUrl->addQuery(name, value);
    return this;
}

_HttpUrlBuilder *_HttpUrlBuilder::appendUser(String user) {
    mUrl->setUser(user);
    return this;
}

_HttpUrlBuilder *_HttpUrlBuilder::appendPassword(String password) {
    mUrl->setPassword(password);
    return this;
}

HttpUrl _HttpUrlBuilder::genHttpUrl() { return mUrl; }

} // namespace obotcha
