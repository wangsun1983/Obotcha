#include <map>
#include <string.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ArrayList.hpp"
#include "HashMap.hpp"
#include "HttpContentType.hpp"
#include "HttpHeader.hpp"
#include "HttpText.hpp"
#include "String.hpp"
#include "HttpCookieParser.hpp"

namespace obotcha {

const String _HttpHeader::Method = createString(":method");
const String _HttpHeader::Path = createString(":path");
const String _HttpHeader::Scheme = createString(":schema");
const String _HttpHeader::Status = createString(":status");
const String _HttpHeader::Protocol = createString(":protocol");
const String _HttpHeader::Accept = createString("accept");
const String _HttpHeader::AcceptPatch = createString("accept-patch");
const String _HttpHeader::AcceptCharset = createString("accept-charset");
const String _HttpHeader::AcceptDatetime = createString("accept-datetime");
const String _HttpHeader::AcceptEncoding = createString("accept-encoding");
const String _HttpHeader::AcceptLanguage = createString("accept-language");
const String _HttpHeader::AcceptRanges = createString("accept-ranges");
const String _HttpHeader::AccessControlAllowCredentials =
    createString("access-control-allow-credentials");
const String _HttpHeader::AccessControlAllowHeaders =
    createString("access-control-allow-headers");
const String _HttpHeader::AccessControlAllowMethods =
    createString("access-control-allow-methods");
const String _HttpHeader::AccessControlAllowOrigin =
    createString("access-control-allow-origin");
const String _HttpHeader::AccessControlExposeHeaders =
    createString("access-control-expose-headers");
const String _HttpHeader::AccessControlMaxAge =
    createString("access-control-max-age");
const String _HttpHeader::AccessControlRequestHeaders =
    createString("access-control-request-headers");
const String _HttpHeader::AccessControlRequestMethod =
    createString("access-control-request-method");
const String _HttpHeader::Age = createString("age");
const String _HttpHeader::Allow = createString("allow");
const String _HttpHeader::AltSvc = createString("alt-svc");
const String _HttpHeader::Authorization = createString("authorization");
const String _HttpHeader::CacheControl = createString("cache-control");
const String _HttpHeader::Connection = createString("connection");
const String _HttpHeader::ContentDisposition =
    createString("content-disposition");
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
const String _HttpHeader::IfUnmodifiedSince =
    createString("if-unmodified-since");
const String _HttpHeader::KeepAlive = createString("keep-alive");
const String _HttpHeader::LastModified = createString("last-modified");
const String _HttpHeader::Link = createString("link");
const String _HttpHeader::Location = createString("location");
const String _HttpHeader::MaxForwards = createString("max-forwards");
const String _HttpHeader::Origin = createString("origin");
const String _HttpHeader::P3P = createString("psp");
const String _HttpHeader::Pragma = createString("pragma");
const String _HttpHeader::ProxyAuthenticate =
    createString("proxy-authenticate");
const String _HttpHeader::ProxyAuthorization =
    createString("proxy-authorization");
const String _HttpHeader::ProxyConnection = createString("proxy-connection");
const String _HttpHeader::Range = createString("range");
const String _HttpHeader::Referer = createString("referer");
const String _HttpHeader::Refresh = createString("refresh");
const String _HttpHeader::RetryAfter = createString("retry-after");
const String _HttpHeader::SecWebSocketKey = createString("sec-websocket-key");
const String _HttpHeader::SecWebSocketAccept =
    createString("sec-websocket-accept");
const String _HttpHeader::Server = createString("server");
const String _HttpHeader::SetCookie = createString("set-cookie");
const String _HttpHeader::SecTokenBinding = createString("sec-token-binding");
const String _HttpHeader::StrictTransportSecurity =
    createString("strict-transport-security");
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
const String _HttpHeader::XContentSecurityPolicyReportOnly =
    createString("x-content-security-policy-report-only");
const String _HttpHeader::XContentTypeOptions =
    createString("x-content-type-options");
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
const String _HttpHeader::SecWebSocketVersion =
    createString("sec-websocket-version");
const String _HttpHeader::SecWebSocketExtensions =
    createString("sec-websocket-extensions");
const String _HttpHeader::SecWebSocketOrigin =
    createString("sec-websocket-origin");
const String _HttpHeader::SecWebSocketKey1 = createString("sec-websocket-key1");
const String _HttpHeader::SecWebSocketKey2 = createString("sec-websocket-key2");
const String _HttpHeader::SecWebSocketKey3 = createString("sec-websocket-key3");
const String _HttpHeader::SecWebSocketProtocol =
    createString("sec-websocket-protocol");

// Transfer-Encoding type
const String _HttpHeader::TransferChunked = createString("chunked");

// Http connection
const String _HttpHeader::ConnectionClose = createString("close");

_HttpHeader::_HttpHeader() {
    mValues = createHashMap<String, String>();
    mCookies = createArrayList<HttpCookie>();
    mVersion = createHttpVersion();
    mCacheControl = nullptr;
    mMethod = -1;
    mResponseReason = nullptr;
    mContentLength = -1;
    mIsConnected = true;
    mType = Type::Request;
    mLink = nullptr;
}

void _HttpHeader::addHttpHeader(sp<_HttpHeader> h) {
    h->mValues->foreach ([this](String key, String value) {
        set(key, value);
        return Global::Continue;
    });

    h->mCookies->foreach ([this](HttpCookie cookie) {
        this->mCookies->add(cookie);
        return Global::Continue;
    });

    //http cache control?
    if(h->mCacheControl != nullptr) {
        mCacheControl = h->mCacheControl;
    }

    if(h->mLink != nullptr) {
        mLink = h->mLink;
    }
}

void _HttpHeader::reset() { 
    mValues->clear(); 
    mCookies->clear();
    mVersion = createHttpVersion();
    mCacheControl = nullptr;
    mMethod = -1;
    mResponseReason = nullptr;
    mContentLength = -1;
    mIsConnected = true;
    mType = Type::Request;
    mLink = nullptr;
}

void _HttpHeader::set(String key, String value) {
    const char *p = key->toChars();
    switch (p[0]) {
        case 'a': {
            if(key->equals(st(HttpHeader)::AcceptEncoding)) {
                if(mAcceptEncoding == nullptr) {
                    mAcceptEncoding = createHttpAcceptEncoding();
                }
                mAcceptEncoding->import(value);
            } else if(key->equals(st(HttpHeader)::AcceptLanguage)) {
                if(mAcceptLanguage == nullptr) {
                    mAcceptLanguage = createHttpAcceptLanguage();
                }
                mAcceptLanguage->import(value);
            } else if(key->equals(st(HttpHeader)::AcceptCharset)) {
                if(mAcceptCharSet == nullptr) {
                    mAcceptCharSet = createHttpAcceptCharSet();
                }
                mAcceptCharSet->import(value);
            } else if(key->equals(st(HttpHeader)::AcceptPatch)) {
                if(mAcceptPatch == nullptr) {
                    mAcceptPatch = createHttpAcceptPatch();
                }
                mAcceptPatch->import(value);
            } else if(key->equals(st(HttpHeader)::Accept)) {
                if(mAccept == nullptr) {
                    mAccept = createHttpAccept();
                }
                mAccept->import(value);
            }
            break;
        }
        
        case 'c': {
            if (key->equals(st(HttpHeader)::Cookie)) {
                ArrayList<HttpCookie> cookies = st(HttpCookieParser)::parse(value);
                auto iterator = cookies->getIterator();
                while (iterator->hasValue()) {
                    addCookie(iterator->getValue());
                    iterator->next();
                }
                return;
            } else if (key->equals(st(HttpHeader)::CacheControl)) {
                auto cacheControl = getCacheControl();
                if(cacheControl == nullptr) {
                    cacheControl = createHttpCacheControl();
                    setCacheControl(cacheControl);
                }
                cacheControl->import(value);
                return;
            } else if (key->equals(st(HttpHeader)::ContentType)) {
                //setContentType(value);
                mContentType = createHttpContentType(value);
                return;
            } else if (key->equals(st(HttpHeader)::ContentLength)) {
                setContentLength(value->trimAll()->toBasicInt());
                return;
            } else if (key->equals(st(HttpHeader)::Connection)) {
                if (st(HttpHeader)::ConnectionClose->equals(value->trimAll())) {
                    setConnected(false);
                    return;
                }
            }
            break;
        }

        case 's': {
            if (key->equals(st(HttpHeader)::SetCookie)) {
                ArrayList<HttpCookie> cookies = st(HttpCookieParser)::parse(value);
                auto iterator = cookies->getIterator();
                while (iterator->hasValue()) {
                    addCookie(iterator->getValue());
                    iterator->next();
                }
                return;
            }
        }

        case 'l': {
            if (key->equals(st(HttpHeader)::Link)) {
                HttpHeaderLink link = createHttpHeaderLink(value);
                setLink(link);
                return;
            }
        }
    }

    mValues->put(key->toLowerCase(), value);
}

String _HttpHeader::get(String header) {
    //TODO
    return mValues->get(header->toLowerCase());
}

void _HttpHeader::clear() { mValues->clear(); }

int _HttpHeader::size() { return mValues->size(); }

int _HttpHeader::getMethod() { return mMethod; }

void _HttpHeader::setMethod(int v) { mMethod = v; }

HttpUrl _HttpHeader::getUrl() { return mUrl; }

void _HttpHeader::setUrl(HttpUrl u) { mUrl = u; }

HttpVersion _HttpHeader::getVersion() { return mVersion; }

void _HttpHeader::setVersion(HttpVersion v) { mVersion = v; }

int _HttpHeader::getResponseStatus() { return mResponseStatus; }

void _HttpHeader::setResponseStatus(int s) { mResponseStatus = s; }

String _HttpHeader::getResponseReason() { return mResponseReason; }

void _HttpHeader::setResponseReason(String s) { mResponseReason = s; }

int _HttpHeader::getContentLength() { return mContentLength; }

void _HttpHeader::setContentLength(int c) { mContentLength = c; }

bool _HttpHeader::isConnected() { return mIsConnected; }

void _HttpHeader::setConnected(bool v) { mIsConnected = v; }

int _HttpHeader::getType() { return mType; }

void _HttpHeader::setType(int v) { mType = v; }

void _HttpHeader::addCookie(HttpCookie c) { mCookies->add(c); }

ArrayList<HttpCookie> _HttpHeader::getCookies() { return mCookies; }

HttpCacheControl _HttpHeader::getCacheControl() { return mCacheControl; }

//void _HttpHeader::updateCacheControl() {
//    mCacheControl = createHttpCacheControl(AutoClone(this));
//}

void _HttpHeader::setCacheControl(HttpCacheControl c) { mCacheControl = c; }

//void _HttpHeader::setContentType(String value) {
//    mContentType = createHttpContentType(value);
//    mValues->put(st(HttpHeader)::ContentType, value);
//}

void _HttpHeader::setContentType(HttpContentType contenttype) {
    mContentType = contenttype;
}

HttpContentType _HttpHeader::getContentType() { return mContentType; }

void _HttpHeader::setLink(HttpHeaderLink l) {
    mLink = l;
}

HttpHeaderLink _HttpHeader::getLink() {
    return mLink;
}

void _HttpHeader::setAcceptEncoding(HttpAcceptEncoding s) {
    mAcceptEncoding = s;
}

HttpAcceptEncoding _HttpHeader::getAcceptEncoding() {
    return mAcceptEncoding;
}

void _HttpHeader::setAcceptLanguage(HttpAcceptLanguage l) {
    mAcceptLanguage = l;
}

HttpAcceptLanguage _HttpHeader::getAcceptLanguage() {
    return mAcceptLanguage;
}

void _HttpHeader::setAcceptCharSet(HttpAcceptCharSet s) {
    mAcceptCharSet = s;
}

HttpAcceptCharSet _HttpHeader::getAcceptCharSet() {
    return mAcceptCharSet;
}

MapIterator<String, String> _HttpHeader::getIterator() {
    return mValues->getIterator();
}

String _HttpHeader::toString(int type) {
    // conver header
    MapIterator<String, String> headerIte = mValues->getIterator();

    String html = createString("");
    while (headerIte->hasValue()) {
        String headString = headerIte->getKey();
        if (headString != nullptr && !headString->equalsIgnoreCase(Status)) {
            html = html->append(headString, ": ", headerIte->getValue(),
                                st(HttpText)::CRLF);
        }

        headerIte->next();
    }

    ListIterator<HttpCookie> iterator = mCookies->getIterator();
    while (iterator->hasValue()) {
        HttpCookie cookie = iterator->getValue();
        html = html->append(cookie->toString(type), st(HttpText)::CRLF);
        iterator->next();
    }

    if(mCacheControl != nullptr) {
        html->append(mCacheControl->toString(type));
    }
    
    if (html->size() == 0) {
        return html;
    }

    return html->subString(0, html->size() - 2);
}

} // namespace obotcha
