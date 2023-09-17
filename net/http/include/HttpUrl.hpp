#ifndef __OBOTCHA_HTTP_URL_HPP__
#define __OBOTCHA_HTTP_URL_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"
#include "HttpUrlEncodedValue.hpp"
#include "InetAddress.hpp"
#include "HttpOption.hpp"
#include "Http.hpp"

namespace obotcha {
//<scheme>://<user>:<password>@<host>:<port>/<path>;<params>?<query>#<frag>
class _HttpConnection;

DECLARE_CLASS(HttpUrl) {
public:
    _HttpUrl() = default;
    explicit _HttpUrl(String);

    void load(String);
    void setScheme(st(Net)::Protocol);
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

    st(Net)::Protocol getScheme() const;
    String getHost() const;
    int getPort() const;
    String getPath() const;
    HttpUrlEncodedValue getQuery() const;
    String getFragment() const;
    String getUser() const;
    String getPassword() const;

    String toString() override;

    ArrayList<InetAddress> getInetAddress();
    sp<_HttpConnection> openConnection(HttpOption o = nullptr);
    void dump();
    
private:
    size_t skipLeadingAsciiWhitespace(String input, size_t pos, size_t limit) const;
    size_t skipTrailingAsciiWhitespace(String input, size_t pos, size_t limit) const;
    size_t schemeDelimiterOffset(String input, size_t pos, size_t limit) const;
    size_t slashCount(String input, size_t pos, size_t limit) const;
    size_t portColonOffset(String input, size_t pos, size_t limit) const;
    size_t delimiterOffset(String input, size_t pos, size_t limit, String delimiters) const;

    st(Net)::Protocol mScheme = st(Net)::Protocol::UnKnown;
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
