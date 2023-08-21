#include "Object.hpp"
#include "StrongPointer.hpp"

#include <arpa/inet.h>
#include <netdb.h>

#include "ArrayList.hpp"
#include "Pair.hpp"
#include "HttpConnection.hpp"
#include "HttpUrl.hpp"
#include "String.hpp"

#include "Inet4Address.hpp"
#include "Inet6Address.hpp"
#include "StringBuffer.hpp"
#include "InfiniteLoop.hpp"

namespace obotcha {

_HttpUrl::_HttpUrl(String v) {
    load(v);
}

int _HttpUrl::skipLeadingAsciiWhitespace(String input, int pos, int limit) const {
    for (int i = pos; i < limit; i++) {
        switch (input->charAt(i)) {
            case '\t':
            case '\n':
            case '\f':
            case '\r':
            case ' ':
            continue;
            default:
            return i;
        }
    }
    return limit;
}

int _HttpUrl::skipTrailingAsciiWhitespace(String input, int pos, int limit) const {
    for (int i = limit - 1; i >= pos; i--) {
        switch (input->charAt(i)) {
            case '\t':
            case '\n':
            case '\f':
            case '\r':
            case ' ':
            continue;
            default:
            return i + 1;
        }
    }
    return pos;
}

int _HttpUrl::schemeDelimiterOffset(String input, int pos, int limit) const {
    if (limit - pos < 2) return -1;

    char c0 = input->charAt(pos);
    if ((c0 < 'a' || c0 > 'z') && (c0 < 'A' || c0 > 'Z')) return -1; // Not a scheme start char.

    for (int i = pos + 1; i < limit; i++) {
        char c = input->charAt(i);

        if ((c >= 'a' && c <= 'z')
            || (c >= 'A' && c <= 'Z')
            || (c >= '0' && c <= '9')
            || c == '+'
            || c == '-'
            || c == '.') {
            continue; // Scheme character. Keep going.
        } else if (c == ':') {
            return i; // Scheme prefix!
        } else {
            return -1; // Non-scheme character before the first ':'.
        }
    }

    return -1; // No ':'; doesn't start with a scheme.
}

/** Returns the number of '/' and '\' slashes in {@code input}, starting at {@code pos}. */
int _HttpUrl::slashCount(String input, int pos, int limit) const {
    int slcount = 0;
    while (pos < limit) {
        char c = input->charAt(pos);
        if (c == '\\' || c == '/') {
            slcount++;
            pos++;
        } else {
            break;
        }
    }
    return slcount;
}

int _HttpUrl::portColonOffset(String input, int pos, int limit) const {
    for (int i = pos; i < limit; i++) {
        switch (input->charAt(i)) {
            case '[':
                while (++i < limit) {
                    if (input->charAt(i) == ']') break;
            } break;

            case ':':
              return i;
            
            default:
              //do nothing
            break;
        }
    }
    return limit; // No colon.
}

int _HttpUrl::delimiterOffset(String input, int pos, int limit, String delimiters) const {
    for (int i = pos; i < limit; i++) {
        if (delimiters->indexOf(input->charAt(i)) != -1) return i;
    }
    return limit;
}

void _HttpUrl::load(String input) {
    mRawUrl = input;
    //path is like *,/,do not parse!!!
    if(input->size() == 1) {
        mPath = input;
        return;
    }

    int pos = skipLeadingAsciiWhitespace(input, 0, input->size());
    int limit = skipTrailingAsciiWhitespace(input, pos, input->size());
    // Scheme.
    int schemeOffset = schemeDelimiterOffset(input, pos, limit);
    if (schemeOffset != -1) {
        if (input->regionMatches(pos, "https:", 0, 6)) {
            mScheme = st(Net)::Protocol::Https;
            mPort = st(Net)::DefaultHttpsPort;
            pos += createString("https:")->size();
        } else if (input->regionMatches(pos, "http:", 0, 5)) {
            mScheme = st(Net)::Protocol::Http;
            mPort = st(Net)::DefaultHttpPort;
            pos += createString("http:")->size();
        } else if (input->regionMatches(pos, "ws:", 0, 3)) {
            mScheme = st(Net)::Protocol::Ws;
            mPort = st(Net)::DefaultHttpPort;
            pos += createString("ws:")->size();
        } else if (input->regionMatches(pos, "tcp:", 0, 4)) {
            mScheme = st(Net)::Protocol::Tcp;
            mPort = -1;
            pos += createString("tcp:")->size();
        }
    }
    // Authority.
    int slcount = slashCount(input, pos, limit);
    
    if (slcount >= 2 || slcount == 0) {
        // Read an authority if either:
        //  * The input starts with 2 or more slashes. These follow the scheme if it exists.
        //  * The input scheme exists and is different from the base URL's scheme.
        //
        // The structure of an authority is:
        //   username:password@host:port
        //
        // Username, password and port are optional.
        //   [username[:password]@]host[:port]
        bool jumpLoop = false;
        pos += slcount;
        InfiniteLoop {
            int componentDelimiterOffset = delimiterOffset(input, pos, limit, "@/\\?#");
            int c = componentDelimiterOffset != limit
                ? input->charAt(componentDelimiterOffset)
                : -1;
            switch (c) {
                case '@':{
                    // User info precedes.
                    int passwordColonOffset = delimiterOffset(
                        input, pos, componentDelimiterOffset, ":");
                    mUser = input->subString(pos,passwordColonOffset-pos);
                    if (passwordColonOffset != componentDelimiterOffset) {
                        mPassword = input->subString(passwordColonOffset + 1,componentDelimiterOffset - passwordColonOffset - 1);
                    }
                    pos = componentDelimiterOffset + 1;
                }
                break;

                case -1:
                case '/':
                case '\\':
                case '?':
                case '#': {
                    // Host info precedes.
                    int portColonPos = portColonOffset(input, pos, componentDelimiterOffset);
                    if (portColonPos + 1 < componentDelimiterOffset) {
                        //maybe hostname is null,like ":4040"
                        try {
                            this->mHostName = input->subString(pos, portColonPos - pos);
                        } catch(...) {}
                        this->mPort = input->subString(portColonPos + 1, componentDelimiterOffset - portColonPos - 1)->toBasicInt();
                    } else {
                        //maybe hostname is null,like ""
                        try {
                            mHostName = input->subString(pos,componentDelimiterOffset-pos);
                        } catch(...) {}
                    }
                    //if (mHostName == nullptr) return; // Invalid host.
                    pos = componentDelimiterOffset;
                    //break authority;
                    jumpLoop = true;
                    break;
                }
            }

            if(jumpLoop) {
               break;
            }
        }
    } else {
        // This is a relative link. Copy over all authority components. Also maybe the path & query.
        //TODO
        //if (pos == limit || input->charAt(pos) == '#') {
        //    encodedQuery(base.encodedQuery());
        //}
    }
    
    if(pos >= input->size()) {
        return;
    }

    // Resolve the relative path.
    int pathDelimiterOffset = delimiterOffset(input, pos, limit, "?#");

    //path does net '/',remove it
    if(pos < pathDelimiterOffset - 1) {
        mPath = input->subString(pos + 1,pathDelimiterOffset - pos - 1);
    }

    pos = pathDelimiterOffset;
    // Query.
    if (pos < limit && input->charAt(pos) == '?') {
        int queryDelimiterOffset = delimiterOffset(input, pos, limit, "#");
        String query = input->subString(pos + 1,queryDelimiterOffset - pos - 1);
        this->mRawQuery =query;
        this->mQuery = createHttpUrlEncodedValue(query);
        pos = queryDelimiterOffset;
    }

    // Fragment.
    if (pos < limit && input->charAt(pos) == '#') {
        mFragment = input->subString(pos + 1, limit-pos-1);
    }
}

void _HttpUrl::setScheme(st(Net)::Protocol data) { 
    mScheme = data; 
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

void _HttpUrl::addQuery(String name, String value) { 
    if(mQuery != nullptr) {
        mQuery = createHttpUrlEncodedValue();
    }
    mQuery->set(name, value); 
}

void _HttpUrl::setFragment(String data) { 
    mFragment = data; 
}

void _HttpUrl::setUser(String data) { 
    mUser = data; 
}

String _HttpUrl::getUser() const { 
    return mUser; 
}

void _HttpUrl::setPassword(String data) { 
    mPassword = data; 
}

String _HttpUrl::getPassword() const { 
    return mPassword; 
}

String _HttpUrl::getRawUrl() { 
    return mRawUrl; 
}

void _HttpUrl::setRawUrl(String u) { 
    mRawUrl = u; 
}

String _HttpUrl::getRawQuery() { 
    return mRawQuery; 
}

void _HttpUrl::setRawQuery(String q) { 
    mRawQuery = q; 
}

st(Net)::Protocol _HttpUrl::getScheme() const { 
    return mScheme; 
}

String _HttpUrl::getHost() const { 
    return mHostName; 
}

int _HttpUrl::getPort() const { 
    return mPort; 
}

String _HttpUrl::getPath() const { 
    return mPath;
}

HttpUrlEncodedValue _HttpUrl::getQuery() const { 
    return mQuery; 
}

String _HttpUrl::getFragment() const { 
    return mFragment;
}

String _HttpUrl::toString() {
    StringBuffer url = createStringBuffer();
    String portStr = nullptr;

    switch(mScheme) {
        case st(Net)::Protocol::Http:
            url->append(createString("http"))->append("://");
            if(mPort != st(Net)::DefaultHttpPort) {
                portStr = createString(":")->append(createString(mPort));
            }
        break;

        case st(Net)::Protocol::Https:
            url->append(createString("https"))->append("://");
            if(mPort != st(Net)::DefaultHttpsPort) {
                portStr = createString(":")->append(createString(mPort));
            }
        break;

        case st(Net)::Protocol::Ws:
            url->append(createString("ws"))->append("://");
            if(mPort != st(Net)::DefaultHttpPort) {
                portStr = createString(":")->append(createString(mPort));
            }
        break;

        case st(Net)::Protocol::Tcp:
            url->append(createString("tcp"))->append("://");
            if(mPort != st(Net)::DefaultHttpPort) {
                portStr = createString(":")->append(createString(mPort));
            }
        break;

        //support for :su:abc@localhost:1234/test.cgi?a=b&c=d#fffsss
        default:
            if(mPort != -1) {
                portStr = createString(":")->append(createString(mPort));
            }
        break;
    }
    
    if (mUser != nullptr) {
        url->append(mUser);
        if (mPassword != nullptr) {
            url->append(":",mPassword,"@");
        } else {
            url->append("@");
        }
    }

    if(mHostName != nullptr) {
        url->append(mHostName);
    }
    
    //if (mPort != -1) {
    if(portStr != nullptr) {
        url->append(portStr);
    }

    if(mPath != nullptr) {
        url->append("/",mPath);
    }

    if(this->mQuery != nullptr) {
        url->append("?",mQuery->toString());
    }

    if(this->mFragment != nullptr) {
        url->append("#",mFragment);
    }
    return url->toString();
}

ArrayList<InetAddress> _HttpUrl::getInetAddress() {
    ArrayList<InetAddress> hosts = createArrayList<InetAddress>();
    char buff[1024*4];
    struct hostent host;
    struct hostent *result = nullptr;
    int err;
    auto res = gethostbyname_r(getHost()->toChars(),&host,buff,sizeof(buff),&result,&err);
    if (res != 0 || result == nullptr) {
        return nullptr;
    }

    char **pptr = result->h_addr_list;
    char str[64] = {0};
    for (; *pptr != nullptr; pptr++) {
        inet_ntop(result->h_addrtype, *pptr, str, sizeof(str));
        InetAddress address = nullptr;
        if (result->h_addrtype == AF_INET) {
            address = createInet4Address(createString(str), mPort);
        } else if (result->h_addrtype == AF_INET6) {
            address = createInet6Address(createString(str), mPort);
        }
        hosts->add(address);
    }

    return hosts;
}

sp<_HttpConnection> _HttpUrl::openConnection(HttpOption o) {
    return createHttpConnection(AutoClone(this), o);
}

void _HttpUrl::dump() {
    printf("schema is %d \n", mScheme);
    
    if (getHost() != nullptr) {
        printf("host is %s \n", getHost()->toChars());
    } else {
        printf("host is NULL \n");
    }

    printf("port is %d \n", getPort());

    if (getPath() != nullptr) {
        printf("path is %s \n", getPath()->toChars());
    } else {
        printf("path is NULL \n");
    }

    if (getFragment() != nullptr) {
        printf("fragment is %s \n", getFragment()->toChars());
    } else {
        printf("fragment is NULL \n");
    }

    if (getUser() != nullptr) {
        printf("user is %s \n", getUser()->toChars());
    } else {
        printf("user is NULL \n");
    }

    if (getPassword() != nullptr) {
        printf("password is %s \n", getPassword()->toChars());
    } else {
        printf("password is NULL \n");
    }

    if (mQuery != nullptr) {
       printf("query is %s \n",mQuery->toString()->toChars());
    } else {
        printf("query is NULL \n");
    }
}

} // namespace obotcha
