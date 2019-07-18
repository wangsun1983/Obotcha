#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HashMap.hpp"
#include "HttpUrl.hpp"

namespace obotcha {

_HttpQuery::_HttpQuery(String name,String value) {
    mName = name;
    mValue = value;
}

String _HttpQuery::getName() {
  return mName;
}

String _HttpQuery::getValue() {
  return mValue;
}

_HttpUrl::_HttpUrl() {
    mQuery = createArrayList<HttpQuery>();
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
    HttpQuery query = createHttpQuery(name,value);
    mQuery->add(query);
}

void _HttpUrl::setQuery(ArrayList<HttpQuery> query) {
    mQuery = query;
}

void _HttpUrl::setFragment(String data) {
    mFragment = data;
}

void _HttpUrl::setUserInfo(String data) {
    mUserInfo = data;
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

ArrayList<HttpQuery> _HttpUrl::getQuery() {
    return mQuery;
}

String _HttpUrl::getFragment() {
    return mFragment;
}

String _HttpUrl::getUserInfo() {
    return mUserInfo;
}

}
