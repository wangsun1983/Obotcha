#include <map>
#include <string.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HashMap.hpp"
#include "HttpHeader.hpp"

namespace obotcha {

const String Method = createString("method");
const String Path = createString("method");
const String Scheme = createString("schema");
const String Status = createString("status");
const String Protocol = createString("protocol");
const String Accept = createString("accept");
const String AcceptCharset= createString("accept-charset");
const String AcceptDatetime= createString("accept-datetime");
const String AcceptEncoding= createString("accept-encoding");
const String AcceptLanguage= createString("accept-language");
const String AcceptRanges= createString("accept-ranges");
const String AccessControlAllowCredentials= createString("access-control-allow-credentials");
const String AccessControlAllowHeaders= createString("access-control-allow-headers");
const String AccessControlAllowMethods= createString("access-control-allow-methods");
const String AccessControlAllowOrigin= createString("access-control-allow-origin");
const String AccessControlExposeHeaders= createString("access-control-expose-headers");
const String AccessControlMaxAge= createString("access-control-max-age");
const String AccessControlRequestHeaders= createString("access-control-request-headers");
const String AccessControlRequestMethod= createString("access-control-request-method");
const String Age= createString("age");
const String Allow= createString("allow");
const String AltSvc= createString("alt-svc");
const String Authorization= createString("authorization");
const String CacheControl= createString("cache-control");
const String Connection= createString("connection");
const String ContentDisposition= createString("content-disposition");
const String ContentEncoding= createString("content-encoding");
const String ContentLanguage= createString("content-language");
const String ContentLength= createString("content-length");
const String ContentLocation= createString("content-location");
const String ContentMD5= createString("content-md5");
const String ContentRange= createString("content-range");
const String ContentType= createString("content-type");
const String Cookie= createString("cookie");
const String DNT= createString("dnt");
const String Date= createString("date");
const String ETag= createString("etag");
const String Expect= createString("expect");
const String Expires= createString("expires");
const String From= createString("from");
const String FrontEndHttps= createString("front-end-https");
const String Host= createString("host");
const String IfMatch= createString("if-match");
const String IfModifiedSince= createString("if-modified-since");
const String IfNoneMatch= createString("if-none-match");
const String IfRange= createString("if-range");
const String IfUnmodifiedSince= createString("if-unmodified-since");
const String KeepAlive= createString("keep-alive");
const String LastModified= createString("last-modified");
const String Link= createString("link");
const String Location= createString("location");
const String MaxForwards= createString("max-forwards");
const String Origin= createString("origin");
const String P3P= createString("psp");
const String Pragma= createString("pragma");
const String ProxyAuthenticate= createString("proxy-authenticate");
const String ProxyAuthorization= createString("proxy-authorization");
const String ProxyConnection= createString("proxy-connection");
const String Range= createString("range");
const String Referer= createString("referer");
const String Refresh= createString("refresh");
const String RetryAfter= createString("retry-after");
const String SecWebSocketKey= createString("sec-websocket-key");
const String SecWebSocketAccept= createString("sec-websocket-accept");
const String Server= createString("server");
const String SetCookie= createString("set-cookie");
const String SecTokenBinding= createString("sec-token-binding");
const String StrictTransportSecurity= createString("strict-transport-security");
const String TE= createString("te");
const String Timestamp= createString("timestamp");
const String Trailer= createString("trailer");
const String TransferEncoding= createString("transfer-encoding");
const String Upgrade= createString("");
const String UserAgent= createString("user-agent");
const String VIP= createString("vip");
const String Vary= createString("vary");
const String Via= createString("via");
const String WWWAuthenticate= createString("www-authenticate");
const String Warning= createString("warning");
const String XAccelRedirect= createString("x-accel-redirect");
const String XContentSecurityPolicyReportOnly= createString("x-content-security-policy-report-only");
const String XContentTypeOptions= createString("x-content-type-options");
const String XForwardedFor= createString("x-forwarded-for");
const String XForwardedProto= createString("x-forwarded-proto");
const String XFrameOptions= createString("x-frame-options");
const String XPoweredBy= createString("x-powerd-by");
const String XRealIP= createString("x-real-ip");
const String XRequestedWith= createString("x-requested-with");
const String XThriftProtocol= createString("x-thrift-protocol");
const String XUACompatible= createString("x-ua-compatible");
const String XWapProfile= createString("x-wap-profile");
const String XXSSProtection= createString("x-xss-protection");
const String SecWebSocketVersion= createString("sec-websocket-version");
const String SecWebSocketExtensions= createString("sec-websocket-extensions");
const String SecWebSocketOrigin= createString("sec-websocket-origin");
const String SecWebSocketKey1= createString("sec-websocket-key1");
const String SecWebSocketKey2= createString("sec-websocket-key2");
const String SecWebSocketKey3= createString("sec-websocket-key3");
const String SecWebSocketProtocol= createString("sec-websocket-protocol");

_HttpHeader::_HttpHeader() {
mValues = createHashMap<String,String>();
    mCookies = createArrayList<HttpCookie>();
}

void _HttpHeader::setValue(String header,String value) {
    mValues->put(header,value);
}

String _HttpHeader::getValue(String header) {
    return mValues->get(header);
}

void _HttpHeader::clear() {
    mValues->clear();
}

int _HttpHeader::getMethod() {
    return mMethod;
}
    
void _HttpHeader::setMethod(int v) {
    mMethod = v;
}

void _HttpHeader::addCookie(HttpCookie c) {
    mCookies->add(c);
}

ArrayList<HttpCookie> _HttpHeader::getCookies() {
    return mCookies;
}

MapIterator<String,String> _HttpHeader::getIterator() {
    return mValues->getIterator();
}

String _HttpHeader::genHtml() {
    //conver header
    MapIterator<String,String> headerIte = mValues->getIterator();;
    String html = createString("");
    while(headerIte->hasValue()) {
        String headSting = headerIte->getKey();
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
        
        html = html->append(SetCookie)
                   ->append(": ")
                   ->append(cookieStr)
                   ->append("\r\n");
    }

    return html;
}

}