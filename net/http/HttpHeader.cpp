#include <map>
#include <string.h>
#include <thread>
#include <mutex>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ArrayList.hpp"
#include "HashMap.hpp"
#include "HttpContentType.hpp"
#include "HttpHeader.hpp"
#include "HttpText.hpp"
#include "String.hpp"
#include "HttpCookieParser.hpp"
#include "HttpProtocol.hpp"
#include "HttpMethod.hpp"
#include "HttpStatus.hpp"
#include "Log.hpp"
#include "IllegalArgumentException.hpp"

namespace obotcha {

HashMap<String,Integer> _HttpHeader::idMaps = createHashMap<String,Integer>();

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
const String _HttpHeader::Forwarded = createString("forwarded");
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
const String _HttpHeader::Digest = createString("digest");

// Transfer-Encoding type
const String _HttpHeader::TransferChunked = createString("chunked");

// Http connection
const String _HttpHeader::ConnectionClose = createString("close");

_HttpHeader::_HttpHeader() {
    {
        static std::once_flag flag;
        std::call_once(flag, [&]() {
            idMaps->put(Accept,createInteger(TypeAccept));
            idMaps->put(AcceptCharset,createInteger(TypeAcceptCharset));
            idMaps->put(AcceptPatch,createInteger(TypeAcceptPatch));
            idMaps->put(AcceptDatetime,createInteger(TypeAcceptDatetime));
            idMaps->put(AcceptEncoding,createInteger(TypeAcceptEncoding));
            idMaps->put(AcceptLanguage,createInteger(TypeAcceptLanguage));
            idMaps->put(AcceptRanges,createInteger(TypeAcceptRanges));
            idMaps->put(AccessControlAllowCredentials,createInteger(TypeAccessControlAllowCredentials));
            idMaps->put(AccessControlAllowHeaders,createInteger(TypeAccessControlAllowHeaders));
            idMaps->put(AccessControlAllowMethods,createInteger(TypeAccessControlAllowMethods));
            idMaps->put(AccessControlAllowOrigin,createInteger(TypeAccessControlAllowOrigin));
            idMaps->put(AccessControlExposeHeaders,createInteger(TypeAccessControlExposeHeaders));
            idMaps->put(AccessControlMaxAge,createInteger(TypeAccessControlMaxAge));
            idMaps->put(AccessControlRequestHeaders,createInteger(TypeAccessControlRequestHeaders));
            idMaps->put(AccessControlRequestMethod,createInteger(TypeAccessControlRequestMethod));
            idMaps->put(Age,createInteger(TypeAge));
            idMaps->put(Allow,createInteger(TypeAllow));
            idMaps->put(AltSvc,createInteger(TypeAltSvc));

            idMaps->put(Authorization,createInteger(TypeAuthorization));
            idMaps->put(CacheControl,createInteger(TypeCacheControl));
            idMaps->put(Connection,createInteger(TypeConnection));
            idMaps->put(ContentDisposition,createInteger(TypeContentDisposition));
            idMaps->put(ContentEncoding,createInteger(TypeContentEncoding));
            idMaps->put(ContentLanguage,createInteger(TypeContentLanguage));
            idMaps->put(ContentLength,createInteger(TypeContentLength));
            idMaps->put(ContentLocation,createInteger(TypeContentLocation));
            idMaps->put(ContentMD5,createInteger(TypeContentMD5));
            idMaps->put(ContentRange,createInteger(TypeContentRange));
            idMaps->put(ContentType,createInteger(TypeContentType));
            idMaps->put(Cookie,createInteger(TypeCookie));

            
            idMaps->put(DNT,createInteger(TypeDNT));
            idMaps->put(Date,createInteger(TypeDate));
            idMaps->put(ETag,createInteger(TypeETag));
            idMaps->put(Expect,createInteger(TypeExpect));
            idMaps->put(Expires,createInteger(TypeExpires));
            idMaps->put(From,createInteger(TypeFrom));
            idMaps->put(FrontEndHttps,createInteger(TypeFrontEndHttps));
            idMaps->put(Host,createInteger(TypeHost));
            idMaps->put(IfMatch,createInteger(TypeIfMatch));
            idMaps->put(IfModifiedSince,createInteger(TypeIfModifiedSince));
            idMaps->put(IfNoneMatch,createInteger(TypeIfNoneMatch));
            idMaps->put(IfRange,createInteger(TypeIfRange));
            idMaps->put(IfUnmodifiedSince,createInteger(TypeIfUnmodifiedSince));
            idMaps->put(KeepAlive,createInteger(TypeKeepAlive));
            idMaps->put(LastModified,createInteger(TypeLastModified));
            idMaps->put(Link,createInteger(TypeLink));
            idMaps->put(Location,createInteger(TypeLocation));
            idMaps->put(MaxForwards,createInteger(TypeMaxForwards));
            idMaps->put(Origin,createInteger(TypeOrigin));
            idMaps->put(P3P,createInteger(TypeP3P));
            idMaps->put(Pragma,createInteger(TypePragma));
            idMaps->put(ProxyAuthenticate,createInteger(TypeProxyAuthenticate));
            idMaps->put(ProxyAuthorization,createInteger(TypeProxyAuthorization));
            idMaps->put(ProxyConnection,createInteger(TypeProxyConnection));
            idMaps->put(Range,createInteger(TypeRange));
            idMaps->put(Referer,createInteger(TypeReferer));

            idMaps->put(Refresh,createInteger(TypeRefresh));
            idMaps->put(RetryAfter,createInteger(TypeRetryAfter));
            idMaps->put(SecWebSocketKey,createInteger(TypeSecWebSocketKey));
            idMaps->put(SecWebSocketAccept,createInteger(TypeSecWebSocketAccept));
            idMaps->put(Server,createInteger(TypeServer));
            idMaps->put(SetCookie,createInteger(TypeSetCookie));
            idMaps->put(SecTokenBinding,createInteger(TypeSecTokenBinding));
            idMaps->put(StrictTransportSecurity,createInteger(TypeStrictTransportSecurity));
            idMaps->put(TE,createInteger(TypeTE));
            idMaps->put(Timestamp,createInteger(TypeTimestamp));
            idMaps->put(Trailer,createInteger(TypeTrailer));
            idMaps->put(TransferEncoding,createInteger(TypeTransferEncoding));

            idMaps->put(Upgrade,createInteger(TypeUpgrade));
            idMaps->put(UserAgent,createInteger(TypeUserAgent));
            idMaps->put(VIP,createInteger(TypeVIP));
            idMaps->put(Vary,createInteger(TypeVary));
            idMaps->put(Via,createInteger(TypeVia));
            idMaps->put(WWWAuthenticate,createInteger(TypeWWWAuthenticate));
            idMaps->put(Warning,createInteger(TypeWarning));
            idMaps->put(XAccelRedirect,createInteger(TypeXAccelRedirect));
            idMaps->put(XContentSecurityPolicyReportOnly,createInteger(TypeXContentSecurityPolicyReportOnly));
            idMaps->put(XContentTypeOptions,createInteger(TypeXContentTypeOptions));
            idMaps->put(XForwardedFor,createInteger(TypeXForwardedFor));
            idMaps->put(XForwardedProto,createInteger(TypeXForwardedProto));
            idMaps->put(Forwarded,createInteger(TypeForwarded));
            idMaps->put(XFrameOptions,createInteger(TypeXFrameOptions));
            idMaps->put(XPoweredBy,createInteger(TypeXPoweredBy));
            idMaps->put(XRealIP,createInteger(TypeXRealIP));
            idMaps->put(XRequestedWith,createInteger(TypeXRequestedWith));
            idMaps->put(XThriftProtocol,createInteger(TypeXThriftProtocol));
            idMaps->put(XUACompatible,createInteger(TypeXUACompatible));
            idMaps->put(XWapProfile,createInteger(TypeXWapProfile));
            idMaps->put(XXSSProtection,createInteger(TypeXXSSProtection));
            idMaps->put(SecWebSocketVersion,createInteger(TypeSecWebSocketVersion));
            idMaps->put(SecWebSocketExtensions,createInteger(TypeSecWebSocketExtensions));
            idMaps->put(SecWebSocketOrigin,createInteger(TypeSecWebSocketOrigin));
            idMaps->put(SecWebSocketKey1,createInteger(TypeSecWebSocketKey1));
            idMaps->put(SecWebSocketKey2,createInteger(TypeSecWebSocketKey2));
            idMaps->put(SecWebSocketKey3,createInteger(TypeSecWebSocketKey3));
            idMaps->put(SecWebSocketProtocol,createInteger(TypeSecWebSocketProtocol));
            idMaps->put(Digest,createInteger(TypeDigest));
        });
    }
    
    mValues = createHashMap<String, String>();
    mCookies = createArrayList<HttpCookie>();
    mLinks = createArrayList<HttpHeaderLink>();

    reset();
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

    if(h->mLinks->size() != 0) {
        mLinks->add(h->mLinks);
    }

#define SET_VALUE(X) X = (h->X != nullptr)?h->X:nullptr;
    SET_VALUE(mAcceptCharSet);
    SET_VALUE(mAccept);
    SET_VALUE(mAcceptEncoding);
    SET_VALUE(mAcceptLanguage);
    SET_VALUE(mAcceptPatch);
    SET_VALUE(mAllowCredentials);
    SET_VALUE(mAllowHeaders);
    SET_VALUE(mAllowMethods);
    SET_VALUE(mAllowOrigin);
    SET_VALUE(mExposeHeaders);
    SET_VALUE(mMaxAge);
    SET_VALUE(mRequestHeaders);
    SET_VALUE(mRequestMethod);
    SET_VALUE(mAge);
    SET_VALUE(mAllow);
    SET_VALUE(mAuthorization);
    SET_VALUE(mCacheControl);
    SET_VALUE(mClearSiteData);
    SET_VALUE(mContentDisposition);
    SET_VALUE(mContentEncoding);
    SET_VALUE(mContentLanguage);
    SET_VALUE(mContentLength);
    SET_VALUE(mContentLocation);
    SET_VALUE(mContentType);
    SET_VALUE(mForwarded);
    SET_VALUE(mConnection);
    SET_VALUE(mHeaderDigest);
    SET_VALUE(mHost);
    SET_VALUE(mKeepAlive);
    SET_VALUE(mIfMatch);
    SET_VALUE(mIfNoneMatch);
    SET_VALUE(mRetryAfter);
    SET_VALUE(mUserAgent);
    SET_VALUE(mIfModifiedSince);
    SET_VALUE(mIfRange);
    SET_VALUE(mIfUnmodifiedSince);
    SET_VALUE(mProxyAuthenticate);
    SET_VALUE(mProxyAuthorization);
    SET_VALUE(mTransportSecurity);
    SET_VALUE(mVersion);
    SET_VALUE(mXFrameOptions);
#undef SET_VALUE
}

void _HttpHeader::reset() { 
    mValues->clear(); 
    mCookies->clear();
    mLinks->clear();
    mVersion = createHttpVersion();
    
    mAcceptCharSet = nullptr;
    mAccept = nullptr;
    mAcceptEncoding = nullptr;
    mAcceptLanguage = nullptr;
    mAcceptPatch = nullptr;
    mAllowCredentials = nullptr;
    mAllowHeaders = nullptr;
    mAllowMethods = nullptr;
    mAllowOrigin = nullptr;
    mExposeHeaders = nullptr;
    mMaxAge = nullptr;
    mRequestHeaders = nullptr;
    mRequestMethod = nullptr;
    mAge = nullptr;
    mAllow = nullptr;
    mAuthorization = nullptr;
    mCacheControl = nullptr;
    mClearSiteData = nullptr;
    mContentDisposition = nullptr;
    mContentEncoding = nullptr;
    mContentLanguage = nullptr;
    mContentLength = nullptr;
    mContentLocation = nullptr;
    mContentType = nullptr;
    mForwarded = nullptr;
    mConnection = nullptr;
    mHeaderDigest = nullptr;
    mHost = nullptr;
    mKeepAlive = nullptr;
    mIfMatch = nullptr;
    mIfNoneMatch = nullptr;
    mRetryAfter = nullptr;
    mUserAgent = nullptr;
    mIfModifiedSince = nullptr;
    mIfRange = nullptr;
    mIfUnmodifiedSince = nullptr;
    mProxyAuthenticate = nullptr;
    mProxyAuthorization = nullptr;
    mTransportSecurity = nullptr;
    mXFrameOptions = nullptr;

    mMethod = -1;
    mResponseReason = nullptr;
    mResponseStatus = st(HttpStatus)::Ok;

    mType = Type::Request;
}

void _HttpHeader::set(String key, String value) {
    //const char *p = key->toChars();
    Integer id = idMaps->get(key->toLowerCase());
    if(id != nullptr) {
        switch(id->toValue()) {
            case TypeAcceptCharset:{
                if(mAcceptCharSet == nullptr) {
                    mAcceptCharSet = createHttpAcceptCharSet();
                }
                mAcceptCharSet->import(value);
                return;
            }

            case TypeAccept:{
                if(mAccept == nullptr) {
                    mAccept = createHttpAccept();
                }
                mAccept->import(value);
                return;
            }

            case TypeAcceptEncoding:{
                if(mAcceptEncoding == nullptr) {
                    mAcceptEncoding = createHttpAcceptEncoding();
                }
                mAcceptEncoding->import(value);
                return;
            }

            case TypeAcceptLanguage: {
                if(mAcceptLanguage == nullptr) {
                    mAcceptLanguage = createHttpAcceptLanguage();
                }
                mAcceptLanguage->import(value);
                return;
            }

            case TypeTransferEncoding: {
                if(mTransferEncoding == nullptr) {
                    mTransferEncoding = createHttpTransferEncoding();
                }
                mTransferEncoding->import(value);
                return;
            }

            case TypeAcceptPatch: {
                if(mAcceptPatch == nullptr) {
                    mAcceptPatch = createHttpAcceptPatch();
                }
                mAcceptPatch->import(value);
                return;
            }

            case TypeAccessControlAllowCredentials: {
                if(mAllowCredentials == nullptr) {
                    mAllowCredentials = createHttpAccessControlAllowCredentials();
                }
                mAllowCredentials->import(value);
                return;
            }

            case TypeAccessControlAllowHeaders: {
                if(mAllowHeaders == nullptr) {
                    mAllowHeaders = createHttpAccessControlAllowHeaders();
                }
                mAllowHeaders->import(value);
                return;
            }

            case TypeAccessControlAllowMethods: {
                if(mAllowMethods == nullptr) {
                    mAllowMethods = createHttpAccessControlAllowMethods();
                }
                mAllowMethods->import(value);
                return;
            }

            case TypeAccessControlAllowOrigin: {
                if(mAllowOrigin == nullptr) {
                    mAllowOrigin = createHttpAccessControlAllowOrigin();
                }
                mAllowOrigin->import(value);
                return;
            }

            case TypeAccessControlExposeHeaders: {
                if(mExposeHeaders == nullptr) {
                    mExposeHeaders = createHttpAccessControlExposeHeaders();
                }
                mExposeHeaders->import(value);
                return;
            }
            
            case TypeAccessControlMaxAge: {
                if(mMaxAge == nullptr) {
                    mMaxAge = createHttpAccessControlMaxAge();
                }
                mMaxAge->import(value);
                return;
            }

            case TypeAccessControlRequestHeaders: {
                if(mRequestHeaders == nullptr) {
                    mRequestHeaders = createHttpAccessControlRequestHeaders();
                }
                mRequestHeaders->import(value);
                return;
            }

            case TypeAccessControlRequestMethod: {
                if(mRequestMethod == nullptr) {
                    mRequestMethod = createHttpAccessControlRequestMethod();
                }
                mRequestMethod->import(value);
                return;
            }

            case TypeAge: {
                if(mAge == nullptr) {
                    mAge = createHttpAge();
                }
                mAge->import(value);
                return;
            }

            case TypeAllow: {
                if(mAllow == nullptr) {
                    mAllow = createHttpAllow();
                }
                mAllow->import(value);
                return;
            }

            case TypeAuthorization: {
                if(mAuthorization == nullptr) {
                    mAuthorization = createHttpAuthorization();
                }
                mAuthorization->import(value);
                return;
            }
            
            case TypeCacheControl: {
                if(mCacheControl == nullptr) {
                    mCacheControl = createHttpCacheControl();
                }
                mCacheControl->import(value);
                return;
            }

            //TODO:ClearSiteData

            case TypeContentDisposition: {
                if(mContentDisposition == nullptr) {
                    mContentDisposition = createHttpContentDisposition();
                }
                mContentDisposition->import(value);
                return;
            }

            case TypeContentEncoding: {
                if(mContentEncoding == nullptr) {
                    mContentEncoding = createHttpContentEncoding();
                }
                mContentEncoding->import(value);
                return;
            }

            case TypeContentLanguage: {
                if(mContentLanguage == nullptr) {
                    mContentLanguage = createHttpContentLanguage();
                }
                mContentLanguage->import(value);
                return;
            }

            case TypeContentLength: {
                if(mContentLength == nullptr) {
                    mContentLength = createHttpContentLength();
                }
                mContentLength->import(value);
                return;
            }

            case TypeContentLocation: {
                if(mContentLocation == nullptr) {
                    mContentLocation = createHttpContentLocation();
                }
                mContentLocation->import(value);
                return;
            }

            case TypeContentType: {
                if(mContentType == nullptr) {
                    mContentType = createHttpContentType();
                }
                mContentType->import(value);
                return;
            }

            case TypeForwarded: {
                if(mForwarded == nullptr) {
                    mForwarded = createHttpForwarded();
                }
                mForwarded->import(value);
                return;
            }

            case TypeConnection: {
                if(mConnection == nullptr) {
                    mConnection = createHttpHeaderConnection();
                }
                mConnection->import(value);
                return;
            }

            case TypeDigest: {
                if(mHeaderDigest == nullptr) {
                    mHeaderDigest = createHttpHeaderDigest();
                }
                mHeaderDigest->import(value);
                return;
            }

            case TypeHost: {
                if(mHost == nullptr) {
                    mHost = createHttpHeaderHost();
                }
                mHost->import(value);
                return;
            }

            case TypeKeepAlive: {
                if(mKeepAlive == nullptr) {
                    mKeepAlive = createHttpHeaderKeepAlive();
                }
                mKeepAlive->import(value);
                return;
            }

            case TypeLink: {
                if(mLinks == nullptr) {
                    mLinks = createArrayList<HttpHeaderLink>();
                }

                HttpHeaderLink l = createHttpHeaderLink(value);
                mLinks->add(l);
            }

            case TypeIfMatch: {
                if(mIfMatch == nullptr) {
                    mIfMatch = createHttpHeaderMatch();
                }
                mIfMatch->import(value);
                return;
            }

            case TypeIfNoneMatch: {
                if(mIfNoneMatch == nullptr) {
                    mIfNoneMatch = createHttpHeaderMatch();
                }
                mIfNoneMatch->import(value);
                return;
            }

            case TypeRetryAfter: {
                if(mRetryAfter == nullptr) {
                    mRetryAfter = createHttpHeaderRetryAfter();
                }
                mRetryAfter->import(value);
                return;
            }

            case TypeUserAgent: {
                if(mUserAgent == nullptr) {
                    mUserAgent = createHttpHeaderUserAgent();
                }
                mUserAgent->import(value);
                return;
            }
            
            case TypeIfModifiedSince: {
                if(mIfModifiedSince == nullptr) {
                    mIfModifiedSince = createHttpIfModifiedSince();
                }
                mIfModifiedSince->import(value);
                return;
            }

            case TypeIfRange: {
                if(mIfRange == nullptr) {
                    mIfRange = createHttpIfRange();
                }
                mIfRange->import(value);
                return;
            }

            case TypeIfUnmodifiedSince: {
                if(mIfUnmodifiedSince == nullptr) {
                    mIfUnmodifiedSince = createHttpIfUnmodifiedSince();
                }
                mIfUnmodifiedSince->import(value);
                return;
            }

            case TypeProxyAuthenticate: {
                if(mProxyAuthenticate == nullptr) {
                    mProxyAuthenticate = createHttpProxyAuthenticate();
                }
                mProxyAuthenticate->import(value);
                return;
            }

            case TypeProxyAuthorization: {
                if(mProxyAuthorization == nullptr) {
                    mProxyAuthorization = createHttpProxyAuthorization();
                }
                mProxyAuthorization->import(value);
                return;
            }
            
            case TypeStrictTransportSecurity: {
                if(mTransportSecurity == nullptr) {
                    mTransportSecurity = createHttpStrictTransportSecurity();
                }
                mTransportSecurity->import(value);
                return;
            }

            case TypeXFrameOptions: {
                if(mXFrameOptions == nullptr) {
                    mXFrameOptions = createHttpXFrameOptions();
                }
                mXFrameOptions->import(value);
                return;
            }

            case TypeUpgrade: {
                if(mUpgrade == nullptr) {
                    mUpgrade = createHttpHeaderUpgrade();
                }
                mUpgrade->import(value);
                return;
            }
        }
    }

    mValues->put(key->toLowerCase(), value);
}

String _HttpHeader::get(String header) {
    Integer id = idMaps->get(header->toLowerCase());
    if(id != nullptr) {
        LOG(ERROR)<<"http header:" <<st(HttpHeader)::toString(id->toValue())->toChars()<<",should call get method directly";
    }

    return mValues->get(header->toLowerCase());
}

int _HttpHeader::size() { return mValues->size(); }

int _HttpHeader::getMethod() { return mMethod; }

void _HttpHeader::setMethod(int v) { mMethod = v; }

HttpUrl _HttpHeader::getUrl() { return mUrl; }

void _HttpHeader::setUrl(HttpUrl u) { mUrl = u; }

int _HttpHeader::getResponseStatus() { return mResponseStatus; }

void _HttpHeader::setResponseStatus(int s) { mResponseStatus = s; }

String _HttpHeader::getResponseReason() { return mResponseReason; }

void _HttpHeader::setResponseReason(String s) { mResponseReason = s; }

int _HttpHeader::getType() { return mType; }

void _HttpHeader::setType(int v) { mType = v; }

void _HttpHeader::addCookie(HttpCookie c) { mCookies->add(c); }

ArrayList<HttpCookie> _HttpHeader::getCookies() { return mCookies; }

//HttpAcceptCharSet
HttpAcceptCharSet _HttpHeader::getAcceptCharSet() {
    return mAcceptCharSet;
}

void _HttpHeader::setAcceptCharSet(HttpAcceptCharSet v) {
    mAcceptCharSet = v;
}

//HttpAccept
HttpAccept _HttpHeader::getAccept() {
    return mAccept;
}

void _HttpHeader::setAccept(HttpAccept s) {
    mAccept = s;
}

//HttpAcceptEncoding
HttpAcceptEncoding _HttpHeader::getAcceptEncoding() {
    return mAcceptEncoding;
}

void _HttpHeader::setAcceptEncoding(HttpAcceptEncoding s) {
    mAcceptEncoding = s;
}

//HttpAcceptLanguage
HttpAcceptLanguage _HttpHeader::getAcceptLanguage() {
    return mAcceptLanguage;
}

void _HttpHeader::setAcceptLanguage(HttpAcceptLanguage s) {
    mAcceptLanguage = s;
}

//HttpAcceptPatch
HttpAcceptPatch _HttpHeader::getAcceptPatch() {
    return mAcceptPatch;
}

void _HttpHeader::setAcceptPatch(HttpAcceptPatch s) {
    mAcceptPatch = s;
}

//HttpAccessControlAllowCredentials
HttpAccessControlAllowCredentials _HttpHeader::getAllowCredentials() {
    return mAllowCredentials;
}

void _HttpHeader::setAllowCredentials(HttpAccessControlAllowCredentials s) {
    mAllowCredentials = s;
}

//HttpAccessControlAllowHeaders
HttpAccessControlAllowHeaders _HttpHeader::getAllowHeaders() {
    return mAllowHeaders;
}

void _HttpHeader::setAllowHeaders(HttpAccessControlAllowHeaders s) {
    mAllowHeaders = s;
}

//HttpAccessControlAllowMethods
HttpAccessControlAllowMethods _HttpHeader::getAllowMethods() {
    return mAllowMethods;
}

void _HttpHeader::setAllowMethods(HttpAccessControlAllowMethods s) {
    mAllowMethods = s;
}

//HttpAccessControlAllowOrigin
HttpAccessControlAllowOrigin _HttpHeader::getAllowOrigin() {
    return mAllowOrigin;
}

void _HttpHeader::setAllowOrigin(HttpAccessControlAllowOrigin s) {
    mAllowOrigin = s;
}

//HttpAccessControlExposeHeaders
HttpAccessControlExposeHeaders _HttpHeader::getExposeHeaders() {
    return mExposeHeaders;
}

void _HttpHeader::setExposeHeaders(HttpAccessControlExposeHeaders s) {
    mExposeHeaders = s;
}

//HttpAccessControlMaxAge
HttpAccessControlMaxAge _HttpHeader::getMaxAge() {
    return mMaxAge;
}

void _HttpHeader::setMaxAge(HttpAccessControlMaxAge s) {
    mMaxAge = s;
}

//HttpAccessControlRequestHeaders
HttpAccessControlRequestHeaders _HttpHeader::getRequestHeaders() {
    return mRequestHeaders;
}

void _HttpHeader::setReqeuestHeaders(HttpAccessControlRequestHeaders s) {
    mRequestHeaders = s;
}

//HttpAccessControlRequestMethod
HttpAccessControlRequestMethod _HttpHeader::getRequestMethod() {
    return mRequestMethod;
}

void _HttpHeader::setRequestMethod(HttpAccessControlRequestMethod s) {
    mRequestMethod = s;
}

//HttpAge
HttpAge _HttpHeader::getAge() {
    return mAge;
}

void _HttpHeader::setAge(HttpAge s) {
    mAge = s;
}

//HttpAllow
HttpAllow _HttpHeader::getAllow() {
    return mAllow;
}

void _HttpHeader::setAllow(HttpAllow s) {
    mAllow = s;
}

//HttpAuthorization
HttpAuthorization _HttpHeader::getAuthorization() {
    return mAuthorization;
}

void _HttpHeader::setAuthorization(HttpAuthorization s) {
    mAuthorization = s;
}

//HttpCacheControl
HttpCacheControl _HttpHeader::getCacheControl() {
    return mCacheControl;
}

void _HttpHeader::setCacheControl(HttpCacheControl s) {
    mCacheControl = s;
}

//HttpClearSiteData
HttpClearSiteData _HttpHeader::getClearSiteData() {
    return mClearSiteData;
}

void _HttpHeader::setClearSiteData(HttpClearSiteData s) {
    mClearSiteData = s;
}

//HttpContentDisposition
HttpContentDisposition _HttpHeader::getContentDisposition() {
    return mContentDisposition;
}

void _HttpHeader::setContentDisposition(HttpContentDisposition s) {
    mContentDisposition = s;
}

//HttpContentEncoding
HttpContentEncoding _HttpHeader::getContentEncoding() {
    return mContentEncoding;
}

void _HttpHeader::setContentEncoding(HttpContentEncoding s) {
    mContentEncoding = s;
}

//HttpContentLanguage
HttpContentLanguage _HttpHeader::getContentLanguage() {
    return mContentLanguage;
}

void _HttpHeader::setContentLanguage(HttpContentLanguage s) {
    mContentLanguage = s;
}

//HttpContentLength
HttpContentLength _HttpHeader::getContentLength() {
    return mContentLength;
}

void _HttpHeader::setContentLength(HttpContentLength s) {
    mContentLength = s;
}

//HttpContentLocation
HttpContentLocation _HttpHeader::getContentLocation() {
    return mContentLocation;
}

void _HttpHeader::setContentLocation(HttpContentLocation s) {
    mContentLocation = s;
}

//HttpContentType
HttpContentType _HttpHeader::getContentType() {
    return mContentType;
}

void _HttpHeader::setContentType(HttpContentType s) {
    mContentType = s;
}

//HttpForwarded
HttpForwarded _HttpHeader::getForwarded() {
    return mForwarded;
}

void _HttpHeader::setForwarded(HttpForwarded s) {
    mForwarded = s;
}

//HttpHeaderConnection
HttpHeaderConnection _HttpHeader::getConnection() {
    return mConnection;
}

void _HttpHeader::setConnection(HttpHeaderConnection s) {
    mConnection = s;
}

//HttpHeaderDigest
HttpHeaderDigest _HttpHeader::getDigest() {
    return mHeaderDigest;
}

void _HttpHeader::setDigest(HttpHeaderDigest s) {
    mHeaderDigest = s;
}

//HttpHeaderHost
HttpHeaderHost _HttpHeader::getHost() {
    return mHost;
}

void _HttpHeader::setHost(HttpHeaderHost s) {
    mHost = s;
}

//HttpHeaderKeepAlive
HttpHeaderKeepAlive _HttpHeader::getKeepAlive() {
    return mKeepAlive;
}

void _HttpHeader::setKeepAlive(HttpHeaderKeepAlive s) {
    mKeepAlive = s;
}

//ArrayList<HttpHeaderLink>
ArrayList<HttpHeaderLink> _HttpHeader::getLinks() {
    return mLinks;
}

void _HttpHeader::setLinks(ArrayList<HttpHeaderLink> s) {
    mLinks = s;
}

void _HttpHeader::addLink(HttpHeaderLink s) {
    mLinks->add(s);
}

//IfMatch
HttpHeaderMatch _HttpHeader::getIfMatch() {
    return mIfMatch;
}

void _HttpHeader::setIfMatch(HttpHeaderMatch s) {
    mIfMatch = s;
}

//IfNoneMatch
HttpHeaderMatch _HttpHeader::getIfNoneMatch() {
    return mIfNoneMatch;
}

void _HttpHeader::setIfNoneMatch(HttpHeaderMatch s) {
    mIfNoneMatch = s;
}

//HttpHeaderRetryAfter
HttpHeaderRetryAfter _HttpHeader::getRetryAfter() {
    return mRetryAfter;
}

void _HttpHeader::setRetryAfter(HttpHeaderRetryAfter s) {
    mRetryAfter = s;
}

//HttpHeaderUserAgent
HttpHeaderUserAgent _HttpHeader::getUserAgent() {
    return mUserAgent;
}

void _HttpHeader::setUserAgent(HttpHeaderUserAgent s) {
    mUserAgent = s;
}

//HttpIfModifiedSince
HttpIfModifiedSince _HttpHeader::getIfModifiedSince() {
    return mIfModifiedSince;
}

void _HttpHeader::setIfModifiedSince(HttpIfModifiedSince s) {
    mIfModifiedSince = s;
}

//HttpIfRange
HttpIfRange _HttpHeader::getIfRange() {
    return mIfRange;
}

void _HttpHeader::setIfRange(HttpIfRange s) {
    mIfRange = s;
}

//HttpIfUnmodifiedSince
HttpIfUnmodifiedSince _HttpHeader::getIfUnmodifiedSince() {
    return mIfUnmodifiedSince;
}

void _HttpHeader::setIfUnmodifiedSince(HttpIfUnmodifiedSince s) {
    mIfUnmodifiedSince = s;
}

//HttpProxyAuthenticate
HttpProxyAuthenticate _HttpHeader::getProxyAuthenticate() {
    return mProxyAuthenticate;
}

void _HttpHeader::setProxyAuthenticate(HttpProxyAuthenticate s) {
    mProxyAuthenticate = s;
}

//HttpProxyAuthorization
HttpProxyAuthorization _HttpHeader::getProxyAuthorization() {
    return mProxyAuthorization;
}

void _HttpHeader::setProxyAuthorization(HttpProxyAuthorization s) {
    mProxyAuthorization = s;
}

//HttpStrictTransportSecurity
HttpStrictTransportSecurity _HttpHeader::getStrictTransportSecurity() {
    return mTransportSecurity;
}

void _HttpHeader::setStrictTransportSecurity(HttpStrictTransportSecurity s) {
    mTransportSecurity = s;
}

//HttpVersion
HttpVersion _HttpHeader::getVersion() {
    return mVersion;
}

void _HttpHeader::setVersion(HttpVersion s) {
    mVersion = s;
}

//HttpXFrameOptions
HttpXFrameOptions _HttpHeader::getXFrameOptions() {
    return mXFrameOptions;
}

void _HttpHeader::setXFrameOptions(HttpXFrameOptions s) {
    mXFrameOptions = s;
}

//HttpTransferEncoding
void _HttpHeader::setTransferEncoding(HttpTransferEncoding s) {
    mTransferEncoding = s;
}

//HttpheaderUpgrade
void _HttpHeader::setUpgrade(HttpHeaderUpgrade s) {
    mUpgrade = s;
}

HttpHeaderUpgrade _HttpHeader::getUpgrade() {
    return mUpgrade;
}

HttpTransferEncoding _HttpHeader::getTransferEncoding() {
    return mTransferEncoding;
}

MapIterator<String, String> _HttpHeader::getIterator() {
    return mValues->getIterator();
}

String _HttpHeader::toString(int type) {
    //create method method.......
    String header = nullptr;
    printf("Http to type is %d \n",type);
    switch(type) {
        case st(HttpProtocol)::HttpRequest: {
            header = st(HttpMethod)::toString(mMethod)->append(st(HttpText)::ContentSpace);
            if (mUrl != nullptr) {
                header = header->append(mUrl->toString());
            } else {
                header = header->append(createString("/"));
            }
            header = header->append(st(HttpText)::ContentSpace,mVersion->toString(),st(HttpText)::CRLF);
            break;
        }

        case st(HttpProtocol)::HttpResponse: {
            header = mVersion->toString()->append(st(HttpText)::ContentSpace,createString(mResponseStatus));
            if (mResponseReason != nullptr) {
                header = header->append(st(HttpText)::ContentSpace,mResponseReason,st(HttpText)::CRLF);
            } else {
                header = header->append(st(HttpText)::ContentSpace,st(HttpStatus)::toString(mResponseStatus),st(HttpText)::CRLF);
            }
            break;
        }

        default:
            Trigger(IllegalArgumentException,"no support");
        break;
    }
    
    // conver header
    MapIterator<String, String> headerIte = mValues->getIterator();

    while (headerIte->hasValue()) {
        String headString = headerIte->getKey();
        if (headString != nullptr && !headString->equalsIgnoreCase(Status)) {
            header = header->append(headString, ": ", headerIte->getValue(),
                                st(HttpText)::CRLF);
        }

        headerIte->next();
    }

    ListIterator<HttpCookie> iterator = mCookies->getIterator();
    while (iterator->hasValue()) {
        HttpCookie cookie = iterator->getValue();
        header = header->append(cookie->toString(type), st(HttpText)::CRLF);
        iterator->next();
    }

    ///////////
    if(mAcceptCharSet != nullptr) {
        header = header->append(st(HttpHeader)::AcceptCharset,": ",mAcceptCharSet->toString(),st(HttpText)::CRLF);
    }

    if(mAccept != nullptr) {
        header = header->append(st(HttpHeader)::Accept,": ",mAccept->toString(),st(HttpText)::CRLF);
    }

    if(mAcceptEncoding != nullptr) {
        header = header->append(st(HttpHeader)::AcceptEncoding,": ",mAcceptEncoding->toString(),st(HttpText)::CRLF);
    }

    if(mAcceptLanguage != nullptr) {
        header = header->append(st(HttpHeader)::AcceptLanguage,": ",mAcceptLanguage->toString(),st(HttpText)::CRLF);    
    }

    if(mAcceptPatch != nullptr) {
        header = header->append(st(HttpHeader)::AcceptPatch,": ",mAcceptPatch->toString(),st(HttpText)::CRLF);        
    }

    if(mAllowCredentials != nullptr) {
        header = header->append(st(HttpHeader)::AccessControlAllowCredentials,": ",mAllowCredentials->toString(),st(HttpText)::CRLF);        
    }

    if(mAllowHeaders != nullptr) {
        header = header->append(st(HttpHeader)::AccessControlAllowHeaders,": ",mAllowHeaders->toString(),st(HttpText)::CRLF);            
    }

    if(mAllowMethods != nullptr) {
        header = header->append(st(HttpHeader)::AccessControlAllowMethods,": ",mAllowMethods->toString(),st(HttpText)::CRLF);            
    }

    if(mAllowOrigin != nullptr) {
        header = header->append(st(HttpHeader)::AccessControlAllowOrigin,": ",mAllowOrigin->toString(),st(HttpText)::CRLF);            
    }

    if(mExposeHeaders != nullptr) {
        header = header->append(st(HttpHeader)::AccessControlExposeHeaders,": ",mExposeHeaders->toString(),st(HttpText)::CRLF);            
    }

    if(mMaxAge != nullptr) {
        header = header->append(st(HttpHeader)::AccessControlMaxAge,": ",mMaxAge->toString(),st(HttpText)::CRLF);            
    }

    if(mRequestHeaders != nullptr) {
        header = header->append(st(HttpHeader)::AccessControlRequestHeaders,": ",mRequestHeaders->toString(),st(HttpText)::CRLF);            
    }

    if(mRequestMethod != nullptr) {
        header = header->append(st(HttpHeader)::AccessControlRequestMethod,": ",mRequestMethod->toString(),st(HttpText)::CRLF);            
    }

    if(mAge != nullptr) {
        header = header->append(st(HttpHeader)::Age,": ",mAge->toString(),st(HttpText)::CRLF);            
    }

    if(mAllow != nullptr) {
        header = header->append(st(HttpHeader)::Allow,": ",mAge->toString(),st(HttpText)::CRLF);
    }

    if(mAuthorization != nullptr) {
        header = header->append(st(HttpHeader)::Authorization,": ",mAuthorization->toString(),st(HttpText)::CRLF);
    }

    if(mCacheControl != nullptr) {
        header = header->append(st(HttpHeader)::CacheControl,": ",mCacheControl->toString(mType),st(HttpText)::CRLF);
    }

    //TODO
    //if(mClearSiteData != nullptr) {
    //    header = header->append(st(HttpHeader)::Clear,": ",mClearSiteData->toString(),st(HttpText)::CRLF);
    //}

    if(mContentDisposition != nullptr) {
        header = header->append(st(HttpHeader)::ContentDisposition,": ",mContentDisposition->toString(),st(HttpText)::CRLF);
    }
    
    if(mContentEncoding != nullptr) {
        header = header->append(st(HttpHeader)::ContentEncoding,": ",mContentEncoding->toString(),st(HttpText)::CRLF);
    }

    if(mTransferEncoding != nullptr) {
        header = header->append(st(HttpHeader)::TransferEncoding,": ",mTransferEncoding->toString(),st(HttpText)::CRLF);
    }
    
    if(mContentLanguage != nullptr) {
        header = header->append(st(HttpHeader)::ContentLanguage,": ",mContentLanguage->toString(),st(HttpText)::CRLF);
    }

    if(mContentLength != nullptr) {
        header = header->append(st(HttpHeader)::ContentLength,": ",mContentLength->toString(),st(HttpText)::CRLF);
    }

    if(mContentLocation != nullptr) {
        header = header->append(st(HttpHeader)::ContentLocation,": ",mContentLocation->toString(),st(HttpText)::CRLF);    
    }

    if(mContentType != nullptr) {
        header = header->append(st(HttpHeader)::ContentType,": ",mContentType->toString(),st(HttpText)::CRLF);    
    }

    if(mForwarded != nullptr) {
        header = header->append(st(HttpHeader)::Forwarded,": ",mForwarded->toString(),st(HttpText)::CRLF);    
    }

    if(mConnection != nullptr) {
        header = header->append(st(HttpHeader)::Connection,": ",mConnection->toString(),st(HttpText)::CRLF);    
    }

    if(mHeaderDigest != nullptr) {
        header = header->append(st(HttpHeader)::Digest,": ",mHeaderDigest->toString(),st(HttpText)::CRLF);    
    }

    if(mHost != nullptr) {
        header = header->append(st(HttpHeader)::Host,": ",mHost->toString(),st(HttpText)::CRLF);    
    }

    if(mKeepAlive != nullptr) {
        header = header->append(st(HttpHeader)::KeepAlive,": ",mKeepAlive->toString(),st(HttpText)::CRLF);    
    }

    if(mIfMatch != nullptr) {
        header = header->append(st(HttpHeader)::IfMatch,": ",mIfMatch->toString(),st(HttpText)::CRLF);    
    }

    if(mIfNoneMatch != nullptr) {
        header = header->append(st(HttpHeader)::IfNoneMatch,": ",mIfNoneMatch->toString(),st(HttpText)::CRLF);    
    }

    if(mRetryAfter != nullptr) {
        header = header->append(st(HttpHeader)::RetryAfter,": ",mRetryAfter->toString(),st(HttpText)::CRLF);    
    }

    if(mUserAgent != nullptr) {
        header = header->append(st(HttpHeader)::UserAgent,": ",mUserAgent->toString(),st(HttpText)::CRLF);    
    }

    if(mIfModifiedSince != nullptr) {
        header = header->append(st(HttpHeader)::IfModifiedSince,": ",mIfModifiedSince->toString(),st(HttpText)::CRLF);    
    }

    if(mIfRange != nullptr) {
        header = header->append(st(HttpHeader)::IfRange,": ",mIfRange->toString(),st(HttpText)::CRLF);
    }

    if(mIfUnmodifiedSince != nullptr) {
        header = header->append(st(HttpHeader)::IfUnmodifiedSince,": ",mIfUnmodifiedSince->toString(),st(HttpText)::CRLF);
    }

    if(mProxyAuthenticate != nullptr) {
        header = header->append(st(HttpHeader)::ProxyAuthenticate,": ",mProxyAuthenticate->toString(),st(HttpText)::CRLF);
    }

    if(mProxyAuthorization != nullptr) {
        header = header->append(st(HttpHeader)::ProxyAuthorization,": ",mProxyAuthorization->toString(),st(HttpText)::CRLF);
    }

    if(mTransportSecurity != nullptr) {
        header = header->append(st(HttpHeader)::StrictTransportSecurity,": ",mTransportSecurity->toString(),st(HttpText)::CRLF);    
    }

    if(mXFrameOptions != nullptr) {
        header = header->append(st(HttpHeader)::XFrameOptions,": ",mXFrameOptions->toString(),st(HttpText)::CRLF);    
    }

    if(mUpgrade != nullptr) {
        header = header->append(st(HttpHeader)::Upgrade,": ",mUpgrade->toString(),st(HttpText)::CRLF);    
    }

    if(mLinks != nullptr && mLinks->size() != 0) {
        auto linkIterator = mLinks->getIterator();
        while(linkIterator->hasValue()) {
            header = header->append(st(HttpHeader)::Link,": ",linkIterator->getValue()->toString(),st(HttpText)::CRLF);
            linkIterator->next();
        }
    }

    if (header->size() == 0) {
        return header;
    }

    return header->subString(0, header->size() - 2);
}

} // namespace obotcha
