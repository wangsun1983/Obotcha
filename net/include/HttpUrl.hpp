#ifndef __HTTP_URL_HPP__
#define __HTTP_URL_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HashMap.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpQuery){
public:
    _HttpQuery(String,String);
    String getName();
    String getValue();
private:
    String mName;
    String mValue;
};

DECLARE_SIMPLE_CLASS(HttpUrl) {
public:
    _HttpUrl();

    void setSchema(String);
    void setHost(String);
    void setPort(int);
    void setPath(String);
    void addQuery(String,String);
    void setQuery(ArrayList<HttpQuery>);
    void setFragment(String);
    void setUserInfo(String);

    String getSchema();
    String getHost();
    int getPort();
    String getPath();
    ArrayList<HttpQuery> getQuery();
    String getFragment();
    String getUserInfo();
    
private:
    String mSchema;
    String mHostName;
    int mPort;
    String mPath;
    ArrayList<HttpQuery> mQuery;
    String mFragment;
    String mUserInfo;
};
}

#endif
