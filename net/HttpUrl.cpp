#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HashMap.hpp"
#include "HttpUrl.hpp"

namespace obotcha {

_HttpUrl::_HttpUrl() {
    mQuery = createHashMap<String,String>();
    mPort = -1;
}

void _HttpUrl::setSchema(String data) {
    mSchema = data;
}

void _HttpUrl::setHost(String data) {
    mHostName = data;
}

void _HttpUrl::setPort(int data) {
    mPort = data;
}

void _HttpUrl::setPath(String data) {
    mPath = data;
}

void _HttpUrl::addQuery(String name,String value) {
    mQuery->put(name,value);
}


void _HttpUrl::setFragment(String data) {
    mFragment = data;
}

void _HttpUrl::setUser(String data) {
    mUser = data;
}

String _HttpUrl::getUser() {
    return mUser;
}

void _HttpUrl::setPassword(String data) {
    mPassword = data;
}

String _HttpUrl::getPassword() {
    return mPassword;
}

String _HttpUrl::getSchema() {
    return mSchema;
}
    
String _HttpUrl::getHost() {
    return mHostName;
}

int _HttpUrl::getPort() {
    return mPort;
}

String _HttpUrl::getPath() {
    return mPath;
}

HashMap<String,String> _HttpUrl::getQuery() {
    return mQuery;
}

String _HttpUrl::getFragment() {
    return mFragment;
}

String _HttpUrl::toString() {
    if(mSchema == nullptr || mHostName == nullptr) {
        return nullptr;
    }

    String url = createString("")->append(mSchema)
                ->append("://");
    
    if(mUser != nullptr) {
        if(mPassword != nullptr) {
            url = url->append(mUser)
                     ->append(":")
                     ->append(mPassword)
                     ->append("@");
        } else {
            url = url->append(mUser)
                     ->append("@");
        }
    }

    url = url->append(mHostName);

    if(mPort != -1) {
        url = url->append(":")
                 ->append(createString(mPort));
    }

    if(mPath != nullptr) {
        url = url->append("/")
                 ->append(mPath);
    }

    String query = toQueryString();
    if(query != nullptr) {
        url = url->append(query);
    }
}

String _HttpUrl::toQueryString() {
    if(mQuery->size() == 0) {
        return nullptr;
    }

    String url = createString("");
    if(mQuery->size() != 0) {
        url = url->append("?");
        bool isFirst = true;
        MapIterator<String,String> iterator = mQuery->getIterator();
        if(iterator->hasValue()) {
            String key = iterator->getKey();
            String value = iterator->getValue();
            iterator->next();
            if(isFirst) {
                url->append(key)
                   ->append("=")
                   ->append(value);
                isFirst = false;
            } else {
                url->append("&")
                   ->append(key)
                   ->append("=")
                   ->append(value);
            }
        }
    }

    return url;
}

}