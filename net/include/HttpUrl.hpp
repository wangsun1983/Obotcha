#ifndef __OBOTCHA_HTTP_URL_HPP__
#define __OBOTCHA_HTTP_URL_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "Pair.hpp"
#include "HttpOption.hpp"
#include "HttpUrlEncodedValue.hpp"

namespace obotcha {

//<scheme>://<user>:<password>@<host>:<port>/<path>;<params>?<query>#<frag>
class _HttpConnection;

DECLARE_CLASS(HttpUrl) {
public:
    _HttpUrl();
    _HttpUrl(String);

    void import(String);
    void setScheme(int);
    void setHost(String);
    void setPort(int);
    void setPath(String);
    void addQuery(String,String);
    void setFragment(String);
    void setUser(String);
    void setPassword(String);
    String getRawUrl();
    void setRawUrl(String);
    String getRawQuery();
    void setRawQuery(String);

    int getScheme();
    String getHost();
    int getPort();
    String getPath();
    HttpUrlEncodedValue getQuery();
    String getFragment();
    String getUser();
    String getPassword();

    String toString();

    ArrayList<InetAddress> getInetAddress();

    sp<_HttpConnection> openConnection(HttpOption o = nullptr);

    void dump();
    

private:
    int skipLeadingAsciiWhitespace(String input, int pos, int limit);
    int skipTrailingAsciiWhitespace(String input, int pos, int limit);
    int schemeDelimiterOffset(String input, int pos, int limit);
    int slashCount(String input, int pos, int limit);
    int portColonOffset(String input, int pos, int limit);
    int delimiterOffset(String input, int pos, int limit, String delimiters);

    int mScheme;
    String mHostName;
    int mPort;
    String mPath;
    HttpUrlEncodedValue mQuery;
    String mFragment;
    String mUser;
    String mPassword;
    String mRawUrl;
    String mRawQuery;
};
}

#endif
