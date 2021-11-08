#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ArrayList.hpp"
#include "KeyValuePair.hpp"
#include "HttpConnection.hpp"
#include "HttpUrl.hpp"
#include "String.hpp"

namespace obotcha {

_HttpUrl::_HttpUrl() {
    mPort = -1;
    mScheme = nullptr;
    mHostName = nullptr;
    mPath = nullptr;
    mFragment = nullptr;
    mUser = nullptr;
    mPassword = nullptr;
    mRawUrl = nullptr;
    mRawQuery = nullptr;
}

_HttpUrl::_HttpUrl(String v):_HttpUrl() {
    import(v);
}

int _HttpUrl::skipLeadingAsciiWhitespace(String input, int pos, int limit) {
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

int _HttpUrl::skipTrailingAsciiWhitespace(String input, int pos, int limit) {
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

int _HttpUrl::schemeDelimiterOffset(String input, int pos, int limit) {
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
int _HttpUrl::slashCount(String input, int pos, int limit) {
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

int _HttpUrl::portColonOffset(String input, int pos, int limit) {
    for (int i = pos; i < limit; i++) {
        switch (input->charAt(i)) {
            case '[':
            while (++i < limit) {
                if (input->charAt(i) == ']') break;
            }
            break;
            case ':':
            return i;
        }
    }
    return limit; // No colon.
}

int _HttpUrl::delimiterOffset(String input, int pos, int limit, String delimiters) {
    for (int i = pos; i < limit; i++) {
        if (delimiters->indexOf(input->charAt(i)) != -1) return i;
    }
    return limit;
}

void _HttpUrl::import(String input) {
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
            mScheme = createString("https");
            pos += createString("https:")->size();
        } else if (input->regionMatches(pos, "http:", 0, 5)) {
            mScheme = createString("http");
            pos += createString("http:")->size();
        } else if (input->regionMatches(pos, "ws:", 0, 3)) {
            mScheme = createString("ws");
            pos += createString("ws:")->size();
        }
    }
    // Authority.
    bool hasUsername = false;
    bool hasPassword = false;
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
        while (true) {
            int componentDelimiterOffset = delimiterOffset(input, pos, limit, "@/\\?#");
            int c = componentDelimiterOffset != limit
                ? input->charAt(componentDelimiterOffset)
                : -1;
            switch (c) {
                case '@':
                    // User info precedes.
                    if (!hasPassword) {
                        int passwordColonOffset = delimiterOffset(
                            input, pos, componentDelimiterOffset, ":");
                        this->mUser = input->subString(pos,passwordColonOffset-pos);
                        if (passwordColonOffset != componentDelimiterOffset) {
                            this->mPassword = input->subString(passwordColonOffset + 1,componentDelimiterOffset - passwordColonOffset - 1);
                        }
                        hasUsername = true;
                    } else {
                        //this.encodedPassword = this.encodedPassword + "%40" + canonicalize(input, pos,
                        //    componentDelimiterOffset, PASSWORD_ENCODE_SET, true, false, false, true);
                        this->mPassword = input->subString(pos,componentDelimiterOffset - pos);
                    }
                    pos = componentDelimiterOffset + 1;
                    break;

                case -1:
                case '/':
                case '\\':
                case '?':
                case '#':
                    // Host info precedes.
                    int portColonPos = portColonOffset(input, pos, componentDelimiterOffset);
                    if (portColonPos + 1 < componentDelimiterOffset) {
                        this->mHostName = input->subString(pos, portColonPos - pos);
                        this->mPort = input->subString(portColonPos + 1, componentDelimiterOffset - portColonPos - 1)->toBasicInt();
                    } else {
                        mHostName = input->subString(pos,componentDelimiterOffset-pos);
                    }
                    //if (mHostName == nullptr) return; // Invalid host.
                    pos = componentDelimiterOffset;
                    //break authority;
                    jumpLoop = true;
                    break;
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

    
    // Resolve the relative path.
    int pathDelimiterOffset = delimiterOffset(input, pos, limit, "?#");

    //path does net '/',remove it 
    mPath = input->subString(pos + 1,pathDelimiterOffset - pos - 1);
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

void _HttpUrl::setScheme(String data) { 
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

String _HttpUrl::getUser() { 
    return mUser; 
}

void _HttpUrl::setPassword(String data) { mPassword = data; }

String _HttpUrl::getPassword() { return mPassword; }

String _HttpUrl::getRawUrl() { return mRawUrl; }

void _HttpUrl::setRawUrl(String u) { mRawUrl = u; }

String _HttpUrl::getRawQuery() { return mRawQuery; }

void _HttpUrl::setRawQuery(String q) { mRawQuery = q; }

String _HttpUrl::getScheme() { return mScheme; }

String _HttpUrl::getHost() { return mHostName; }

int _HttpUrl::getPort() { return mPort; }

String _HttpUrl::getPath() { return mPath; }

HttpUrlEncodedValue _HttpUrl::getQuery() { return mQuery; }

String _HttpUrl::getFragment() { return mFragment; }

String _HttpUrl::toString() {
    //if (mScheme == nullptr || mHostName == nullptr) {
    //    return nullptr;
    //}
    String url = createString("");

    if(mScheme != nullptr) {
        url = url->append(mScheme)->append("://");
    }

    if (mUser != nullptr) {
        if (mPassword != nullptr) {
            url =
                url->append(mUser)->append(":")->append(mPassword)->append("@");
        } else {
            url = url->append(mUser)->append("@");
        }
    }

    if(mHostName != nullptr) {
        url = url->append(mHostName);
    }
    
    if (mPort != -1) {
        url = url->append(":")->append(createString(mPort));
    }

    if (mPath != nullptr) {
        url = url->append("/")->append(mPath);
    }

    if(this->mQuery != nullptr) {
        url = url->append("?",mQuery->toString());
    }

    if(this->mFragment != nullptr) {
        url = url->append("#",mFragment);
    }
    return url;
}

sp<_HttpConnection> _HttpUrl::openConnection(HttpOption o) {
    return createHttpConnection(AutoClone(this), o, false, nullptr);
}

void _HttpUrl::dump() {
    if (getScheme() != nullptr) {
        printf("schema is %s \n", getScheme()->toChars());
    } else {
        printf("schema is NULL \n");
    }

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
