#ifndef __OBOTCHA_HTTP_URL_HPP__
#define __OBOTCHA_HTTP_URL_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"
#include "HttpUrlEncodedValue.hpp"
#include "InetAddress.hpp"
#include "HttpOption.hpp"

namespace obotcha {
//<scheme>://<user>:<password>@<host>:<port>/<path>;<params>?<query>#<frag>
class _HttpConnection;

DECLARE_CLASS(HttpUrl) {
public:
    _HttpUrl() = default;
    explicit _HttpUrl(String);

    void load(String);
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

    String toString() override;

    ArrayList<InetAddress> getInetAddress();
    sp<_HttpConnection> openConnection(HttpOption o = nullptr);
    void dump();
    
private:
    int skipLeadingAsciiWhitespace(String input, int pos, int limit) const;
    int skipTrailingAsciiWhitespace(String input, int pos, int limit) const;
    int schemeDelimiterOffset(String input, int pos, int limit) const;
    int slashCount(String input, int pos, int limit) const;
    int portColonOffset(String input, int pos, int limit) const;
    int delimiterOffset(String input, int pos, int limit, String delimiters) const;

    int mScheme = -1;
    String mHostName = nullptr;
    int mPort = -1;
    String mPath = nullptr;
    HttpUrlEncodedValue mQuery;
    String mFragment = nullptr;
    String mUser = nullptr;
    String mPassword = nullptr;
    String mRawUrl = nullptr;
    String mRawQuery = nullptr;
};
}

#endif
