#include <map>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HashMap.hpp"
#include "HttpHeader.hpp"

namespace obotcha {

String _HttpHeader::mHeaderList[] = {
    ":Authority",
    ":Method",
    ":Path",
    ":Scheme",
    ":Status",
    ":Protocol",
    "Accept",
    "Accept-Charset",
    "Accept-Datetime",
    "Accept-Encoding",
    "Accept-Language",
    "Accept-Ranges",
    "Access-Control-Allow-Credentials",
    "Access-Control-Allow-Headers",
    "Access-Control-Allow-Methods",
    "Access-Control-Allow-Origin",
    "Access-Control-Expose-Headers",
    "Access-Control-Max-Age",
    "Access-Control-Request-Headers",
    "Access-Control-Request-Method",
    "Age",
    "Allow",
    "Alt-Svc",
    "Authorization",
    "Cache-Control",
    "Connection",
    "Content-Disposition",
    "Content-Encoding",
    "Content-Language",
    "Content-Length",
    "Content-Location",
    "Content-MD5",
    "Content-Range",
    "Content-Type",
    "Cookie",
    "DNT",
    "Date",
    "ETag",
    "Expect",
    "Expires",
    "From",
    "Front-End-Https",
    "Host",
    "If-Match",
    "If-Modified-Since",
    "If-None-Match",
    "If-Range",
    "If-Unmodified-Since",
    "Keep-Alive",
    "Last-Modified",
    "Link",
    "Location",
    "Max-Forwards",
    "Origin",
    "P3P",
    "Pragma",
    "Proxy-Authenticate",
    "Proxy-Authorization",
    "Proxy-Connection",
    "Range",
    "Referer",
    "Refresh",
    "Retry-After",
    "Sec-WebSocket-Key",
    "Sec-WebSocket-Accept",
    "Server",
    "Set-Cookie",
    "Sec-Token-Binding",
    "Strict-Transport-Security",
    "TE",
    "Timestamp",
    "Trailer",
    "Transfer-Encoding",
    "Upgrade",
    "User-Agent",
    "VIP",
    "Vary",
    "Via",
    "WWW-Authenticate",
    "Warning",
    "X-Accel-Redirect",
    "X-Content-Security-Policy-Report-Only",
    "X-Content-Type-Options",
    "X-Forwarded-For",
    "X-Forwarded-Proto",
    "X-Frame-Options",
    "X-Powered-By",
    "X-Real-IP",
    "X-Requested-With",
    "X-Thrift-Protocol",
    "X-UA-Compatible",
    "X-Wap-Profile",
    "X-XSS-Protection",
    "Sec-WebSocket-Version",
    "Sec-WebSocket-Extensions",
};

//static method
String _HttpHeader::getHeaderString(int header) {
    return mHeaderList[header];
}

_HttpHeader::_HttpHeader() {
    mValues = createHashMap<Integer,String>();
    mCookies = createArrayList<HttpCookie>();
}

void _HttpHeader::setValue(int header,String value) {
    printf("setValue header is %d,value is %s \n",header,value->toChars());
    mValues->put(createInteger(header),value);
}

String _HttpHeader::getValue(int header) {
    printf("getValue header is %d \n",header);
    return mValues->get(createInteger(header));
}

void _HttpHeader::addCookie(HttpCookie c) {
    mCookies->add(c);
}

ArrayList<HttpCookie> _HttpHeader::getCookies() {
    return mCookies;
}

MapIterator<Integer,String> _HttpHeader::getIterator() {
    return mValues->getIterator();
}

String _HttpHeader::genHtml() {
    //conver header
    MapIterator<Integer,String> headerIte = mValues->getIterator();;
    String html = createString("");
    while(headerIte->hasValue()) {
        String headSting = st(HttpHeader)::getHeaderString(headerIte->getKey()->toValue());
        html = html->append(headSting)
                 ->append(": ")
                 ->append(headerIte->getValue())
                 ->append("\r\n");
        headerIte->next();
    }

    //ArrayList<HttpCookie> getCookies();
    int size = mCookies->size();
    for(int i=0;i<size;i++) {
        String cookieStr = mCookies->get(i)->genHtml();       
        String headSting = st(HttpHeader)::getHeaderString(Http_Header_Set_Cookie);
        
        html = html->append(headSting)
                   ->append(": ")
                   ->append(cookieStr)
                   ->append("\r\n");
    }

    return html;
}


}