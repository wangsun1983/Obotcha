#ifndef __OBOTCHA_HTTP_URL_HPP__
#define __OBOTCHA_HTTP_URL_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "HashMap.hpp"

namespace obotcha {

//<scheme>://<user>:<password>@<host>:<port>/<path>;<params>?<query>#<frag>

DECLARE_SIMPLE_CLASS(HttpUrl) {
public:
    _HttpUrl();
    enum SchemaType {
        Http = 0,
        Https,
    };

    void setSchema(String);
    void setHost(String);
    void setPort(int);
    void setPath(String);
    void addQuery(String,String);
    void setFragment(String);
    void setUser(String);
    void setPassword(String);

    String getSchema();
    String getHost();
    int getPort();
    String getPath();
    HashMap<String,String> getQuery();
    String getFragment();
    String getUser();
    String getPassword();

    String toString();
    String toQueryString();

    void dump();
    
private:
    String mSchema;
    String mHostName;
    int mPort;
    String mPath;
    HashMap<String,String> mQuery;
    String mFragment;
    String mUser;
    String mPassword;
};
}

#endif
