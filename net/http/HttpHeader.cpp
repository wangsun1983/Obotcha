#include <map>
#include <string.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HashMap.hpp"
#include "HttpHeader.hpp"
#include "HttpText.hpp"
#include "HttpContentType.hpp"

namespace obotcha {

const String _HttpHeader::Method = createString(":method");
const String _HttpHeader::Path = createString(":path");
const String _HttpHeader::Scheme = createString(":schema");
const String _HttpHeader::Status = createString(":status");
const String _HttpHeader::Protocol = createString(":protocol");
const String _HttpHeader::Accept = createString("accept");
const String _HttpHeader::AcceptCharset = createString("accept-charset");
const String _HttpHeader::AcceptDatetime = createString("accept-datetime");
const String _HttpHeader::AcceptEncoding = createString("accept-encoding");
const String _HttpHeader::AcceptLanguage = createString("accept-language");
const String _HttpHeader::AcceptRanges = createString("accept-ranges");
const String _HttpHeader::AccessControlAllowCredentials = createString("access-control-allow-credentials");
const String _HttpHeader::AccessControlAllowHeaders = createString("access-control-allow-headers");
const String _HttpHeader::AccessControlAllowMethods = createString("access-control-allow-methods");
const String _HttpHeader::AccessControlAllowOrigin = createString("access-control-allow-origin");
const String _HttpHeader::AccessControlExposeHeaders = createString("access-control-expose-headers");
const String _HttpHeader::AccessControlMaxAge = createString("access-control-max-age");
const String _HttpHeader::AccessControlRequestHeaders = createString("access-control-request-headers");
const String _HttpHeader::AccessControlRequestMethod = createString("access-control-request-method");
const String _HttpHeader::Age = createString("age");
const String _HttpHeader::Allow = createString("allow");
const String _HttpHeader::AltSvc = createString("alt-svc");
const String _HttpHeader::Authorization = createString("authorization");
const String _HttpHeader::CacheControl = createString("cache-control");
const String _HttpHeader::Connection = createString("connection");
const String _HttpHeader::ContentDisposition = createString("content-disposition");
const String _HttpHeader::ContentEncoding = createString("content-encoding");
const String _HttpHeader::ContentLanguage = createString("content-language");
const String _HttpHeader::ContentLength = createString("content-length");
const String _HttpHeader::ContentLocation = createString("content-location");
const String _HttpHeader::ContentMD5 = createString("content-md5");
const String _HttpHeader::ContentRange = createString("content-range");
const String _HttpHeader::ContentType = createString("content-type");
const String _HttpHeader::Cookie = createString("cookie");
const String _HttpHeader::DNT = createString("dnt");
const String _HttpHeader::Date = createString("date");
const String _HttpHeader::ETag = createString("etag");
const String _HttpHeader::Expect = createString("expect");
const String _HttpHeader::Expires = createString("expires");
const String _HttpHeader::From = createString("from");
const String _HttpHeader::FrontEndHttps = createString("front-end-https");
const String _HttpHeader::Host = createString("host");
const String _HttpHeader::IfMatch = createString("if-match");
const String _HttpHeader::IfModifiedSince = createString("if-modified-since");
const String _HttpHeader::IfNoneMatch = createString("if-none-match");
const String _HttpHeader::IfRange = createString("if-range");
const String _HttpHeader::IfUnmodifiedSince = createString("if-unmodified-since");
const String _HttpHeader::KeepAlive = createString("keep-alive");
const String _HttpHeader::LastModified = createString("last-modified");
const String _HttpHeader::Link = createString("link");
const String _HttpHeader::Location = createString("location");
const String _HttpHeader::MaxForwards = createString("max-forwards");
const String _HttpHeader::Origin = createString("origin");
const String _HttpHeader::P3P = createString("psp");
const String _HttpHeader::Pragma = createString("pragma");
const String _HttpHeader::ProxyAuthenticate = createString("proxy-authenticate");
const String _HttpHeader::ProxyAuthorization = createString("proxy-authorization");
const String _HttpHeader::ProxyConnection = createString("proxy-connection");
const String _HttpHeader::Range = createString("range");
const String _HttpHeader::Referer = createString("referer");
const String _HttpHeader::Refresh = createString("refresh");
const String _HttpHeader::RetryAfter = createString("retry-after");
const String _HttpHeader::SecWebSocketKey = createString("sec-websocket-key");
const String _HttpHeader::SecWebSocketAccept = createString("sec-websocket-accept");
const String _HttpHeader::Server = createString("server");
const String _HttpHeader::SetCookie = createString("set-cookie");
const String _HttpHeader::SecTokenBinding = createString("sec-token-binding");
const String _HttpHeader::StrictTransportSecurity = createString("strict-transport-security");
const String _HttpHeader::TE = createString("te");
const String _HttpHeader::Timestamp = createString("timestamp");
const String _HttpHeader::Trailer = createString("trailer");
const String _HttpHeader::TransferEncoding = createString("transfer-encoding");
const String _HttpHeader::Upgrade = createString("upgrade");
const String _HttpHeader::UserAgent = createString("user-agent");
const String _HttpHeader::VIP = createString("vip");
const String _HttpHeader::Vary = createString("vary");
const String _HttpHeader::Via = createString("via");
const String _HttpHeader::WWWAuthenticate = createString("www-authenticate");
const String _HttpHeader::Warning = createString("warning");
const String _HttpHeader::XAccelRedirect = createString("x-accel-redirect");
const String _HttpHeader::XContentSecurityPolicyReportOnly = createString("x-content-security-policy-report-only");
const String _HttpHeader::XContentTypeOptions = createString("x-content-type-options");
const String _HttpHeader::XForwardedFor = createString("x-forwarded-for");
const String _HttpHeader::XForwardedProto = createString("x-forwarded-proto");
const String _HttpHeader::XFrameOptions = createString("x-frame-options");
const String _HttpHeader::XPoweredBy = createString("x-powerd-by");
const String _HttpHeader::XRealIP = createString("x-real-ip");
const String _HttpHeader::XRequestedWith = createString("x-requested-with");
const String _HttpHeader::XThriftProtocol = createString("x-thrift-protocol");
const String _HttpHeader::XUACompatible = createString("x-ua-compatible");
const String _HttpHeader::XWapProfile = createString("x-wap-profile");
const String _HttpHeader::XXSSProtection = createString("x-xss-protection");
const String _HttpHeader::SecWebSocketVersion = createString("sec-websocket-version");
const String _HttpHeader::SecWebSocketExtensions = createString("sec-websocket-extensions");
const String _HttpHeader::SecWebSocketOrigin = createString("sec-websocket-origin");
const String _HttpHeader::SecWebSocketKey1 = createString("sec-websocket-key1");
const String _HttpHeader::SecWebSocketKey2 = createString("sec-websocket-key2");
const String _HttpHeader::SecWebSocketKey3 = createString("sec-websocket-key3");
const String _HttpHeader::SecWebSocketProtocol = createString("sec-websocket-protocol");

//Transfer-Encoding type
const String _HttpHeader::TransferChunked = createString("chunked");

_HttpHeader::_HttpHeader() {
    mValues  = createHashMap<String,String>();
    mCookies = createArrayList<HttpCookie>();
    mCacheControl = nullptr;
    mMethod = -1;
}

void _HttpHeader::reset() {
    mValues->clear();
}

void _HttpHeader::setValue(String header,String value) {
    mValues->put(header->toLowerCase(),value);
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

HttpCacheControl _HttpHeader::getCacheControl() {
    return mCacheControl;
}

void _HttpHeader::setCacheControl(HttpCacheControl c) {
    mCacheControl = c;
}

void _HttpHeader::setContentType(String value) {
    mContentType =  createHttpContentType(value);
    mValues->put(st(HttpHeader)::ContentType,value);
}

void _HttpHeader::setContentType(HttpContentType contenttype) {
    mContentType = contenttype;
}

HttpContentType _HttpHeader::getContentType() {
    return mContentType;
}

MapIterator<String,String> _HttpHeader::getIterator() {
    return mValues->getIterator();
}

String _HttpHeader::toString(int type) {
    //conver header
    MapIterator<String,String> headerIte = mValues->getIterator();;
    String html = createString("");
    while(headerIte->hasValue()) {
        String headString = headerIte->getKey();
        if(headString != nullptr && !headString->equalsIgnoreCase(Status)) {
            html = html->append(headString,": ",headerIte->getValue(),st(HttpText)::CRLF);
        }
        
        headerIte->next();
    }

    ListIterator<HttpCookie> iterator = mCookies->getIterator();
    while(iterator->hasValue()) {
        HttpCookie cookie = iterator->getValue();
        html = html->append(cookie->toString(type),st(HttpText)::CRLF);
        iterator->next();
    }

    if(html->size() == 0) {
        return nullptr;
    }

    return html->subString(0,html->size() - 2);
}

}