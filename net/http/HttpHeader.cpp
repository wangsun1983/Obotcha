#include <map>
#include <string.h>
#include <thread>
#include <mutex>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ArrayList.hpp"
#include "HashMap.hpp"
#include "HttpHeaderContentType.hpp"
#include "HttpHeader.hpp"
#include "HttpPacket.hpp"
#include "HttpText.hpp"
#include "String.hpp"
#include "HttpCookieParser.hpp"
#include "HttpMethod.hpp"
#include "HttpStatus.hpp"
#include "Log.hpp"
#include "IllegalArgumentException.hpp"
#include "StringBuffer.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

HashMap<String,Integer> _HttpHeader::idMaps = createHashMap<String,Integer>();
ArrayList<String> _HttpHeader::names = createArrayList<String>();

const String _HttpHeader::Method = createString(":method");
const String _HttpHeader::Path = createString(":path");
const String _HttpHeader::Scheme = createString(":schema");
const String _HttpHeader::Status = createString(":status");
const String _HttpHeader::Protocol = createString(":protocol");
const String _HttpHeader::Accept = createString("accept");
const String _HttpHeader::AcceptCh = createString("accept-ch");
const String _HttpHeader::AcceptPatch = createString("accept-patch");
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
const String _HttpHeader::ContentSecurityPolicyReportOnly = createString("content-security-policy-report-only");
const String _HttpHeader::ContentSecurityPolicy = createString("content-security-policy");
const String _HttpHeader::ContentType = createString("content-type");
const String _HttpHeader::Cookie = createString("cookie");
const String _HttpHeader::CrossOriginEmbederPolicy = createString("cross-origin-embedder-policy");
const String _HttpHeader::CrossOriginOpenerPolicy = createString("cross-origin-opener-policy");;
const String _HttpHeader::CrossOriginResourcePolicy = createString("cross-origin-resource-policy");;
const String _HttpHeader::DNT = createString("dnt");
const String _HttpHeader::Date = createString("date");
const String _HttpHeader::ETag = createString("etag");
const String _HttpHeader::Expect = createString("expect");
const String _HttpHeader::ExpectCT = createString("expect-ct");
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
const String _HttpHeader::RefererPolicy = createString("referrer-policy");
const String _HttpHeader::Refresh = createString("refresh");
const String _HttpHeader::RetryAfter = createString("retry-after");
const String _HttpHeader::SecWebSocketKey = createString("sec-websocket-key");
const String _HttpHeader::SecWebSocketAccept = createString("sec-websocket-accept");
const String _HttpHeader::SaveData = createString("save-data");
const String _HttpHeader::Server = createString("server");
const String _HttpHeader::SetCookie = createString("set-cookie");
const String _HttpHeader::SecTokenBinding = createString("sec-token-binding");
const String _HttpHeader::SecFetchDest = createString("sec-fetch-dest");
const String _HttpHeader::SecFetchMode = createString("sec-fetch-mode");
const String _HttpHeader::SecFetchSite = createString("sec-fetch-site");
const String _HttpHeader::SecFetchUser = createString("sec-fetch-user");
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
const String _HttpHeader::Forwarded = createString("forwarded");
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
const String _HttpHeader::ServerTiming = createString("server-timing");
const String _HttpHeader::SourceMap = createString("sourcemap");
const String _HttpHeader::Digest = createString("digest");

// Transfer-Encoding type
const String _HttpHeader::TransferChunked = createString("chunked");

// Http connection
const String _HttpHeader::ConnectionClose = createString("close");

// Http2 authority
const String _HttpHeader::Authority = createString(":authority");

_HttpHeader::_HttpHeader(int protocol) {
    {
        static std::once_flag flag;
        std::call_once(flag, [&]() {
            idMaps->put(Method,createInteger(TypeMethod));
            idMaps->put(Path,createInteger(TypePath));
            idMaps->put(Scheme,createInteger(TypeScheme));
            idMaps->put(Status,createInteger(TypeStatus));
            idMaps->put(Protocol,createInteger(TypeProtocol));

            idMaps->put(Accept,createInteger(TypeAccept));
            idMaps->put(AcceptCharset,createInteger(TypeAcceptCharset));
            idMaps->put(AcceptCh,createInteger(TypeAcceptCh));
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
            idMaps->put(ContentSecurityPolicyReportOnly,createInteger(TypeContentSecurityPolicyReportOnly));
            idMaps->put(ContentSecurityPolicy,createInteger(TypeContentSecurityPolicy));
            idMaps->put(ContentType,createInteger(TypeContentType));
            idMaps->put(Cookie,createInteger(TypeCookie));
            idMaps->put(CrossOriginEmbederPolicy,createInteger(TypeCrossOriginEmbedderPolicy));
            idMaps->put(CrossOriginOpenerPolicy,createInteger(TypeCrossOriginOpenerPolicy));
            idMaps->put(CrossOriginResourcePolicy,createInteger(TypeCrossOriginResourcePolicy));
            
            idMaps->put(DNT,createInteger(TypeDNT));
            idMaps->put(Date,createInteger(TypeDate));
            idMaps->put(ETag,createInteger(TypeETag));
            idMaps->put(Expect,createInteger(TypeExpect));
            idMaps->put(ExpectCT,createInteger(TypeExpectCT));
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
            idMaps->put(RefererPolicy,createInteger(TypeRefererPolicy));

            idMaps->put(Refresh,createInteger(TypeRefresh));
            idMaps->put(RetryAfter,createInteger(TypeRetryAfter));
            idMaps->put(SecWebSocketKey,createInteger(TypeSecWebSocketKey));
            idMaps->put(SecWebSocketAccept,createInteger(TypeSecWebSocketAccept));
            idMaps->put(Server,createInteger(TypeServer));
            idMaps->put(SetCookie,createInteger(TypeSetCookie));
            idMaps->put(SecTokenBinding,createInteger(TypeSecTokenBinding));
            idMaps->put(SecFetchDest,createInteger(TypeSecFetchDest));
            idMaps->put(SecFetchMode,createInteger(TypeSecFetchMode));
            idMaps->put(SecFetchSite,createInteger(TypeSecFetchSite));
            idMaps->put(SecFetchUser,createInteger(TypeSecFetchUser));

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
            idMaps->put(SaveData,createInteger(TypeSaveData));
            idMaps->put(SecWebSocketKey1,createInteger(TypeSecWebSocketKey1));
            idMaps->put(SecWebSocketKey2,createInteger(TypeSecWebSocketKey2));
            idMaps->put(SecWebSocketKey3,createInteger(TypeSecWebSocketKey3));
            idMaps->put(SecWebSocketProtocol,createInteger(TypeSecWebSocketProtocol));
            idMaps->put(ServerTiming,createInteger(TypeServerTiming));
            idMaps->put(SourceMap,createInteger(TypeSourceMap));
            idMaps->put(Digest,createInteger(TypeDigest));
            idMaps->put(Authority,createInteger(TypeAuthority));

            //add names
            names->add(Method);
            names->add(Path);
            names->add(Scheme);
            names->add(Status);
            names->add(Protocol);
            names->add(Accept);
            names->add(AcceptCh);
            names->add(AcceptCharset);
            names->add(AcceptPatch);
            names->add(AcceptDatetime);
            names->add(AcceptEncoding);
            names->add(AcceptLanguage);
            names->add(AcceptRanges);
            names->add(AccessControlAllowCredentials);
            names->add(AccessControlAllowHeaders);
            names->add(AccessControlAllowMethods);
            names->add(AccessControlAllowOrigin);
            names->add(AccessControlExposeHeaders);
            names->add(AccessControlMaxAge);
            names->add(AccessControlRequestHeaders);
            names->add(AccessControlRequestMethod);
            names->add(Age);
            names->add(Allow);
            names->add(AltSvc);
            names->add(Authorization);
            names->add(CacheControl);
            names->add(Connection);
            names->add(ContentDisposition);
            names->add(ContentEncoding);
            names->add(ContentLanguage);
            names->add(ContentLength);
            names->add(ContentLocation);
            names->add(ContentMD5);
            names->add(ContentRange);
            names->add(ContentSecurityPolicyReportOnly);
            names->add(ContentSecurityPolicy);
            names->add(ContentType);
            names->add(Cookie);
            names->add(CrossOriginEmbederPolicy);
            names->add(CrossOriginOpenerPolicy);
            names->add(CrossOriginResourcePolicy);
            names->add(DNT);
            names->add(Date);
            names->add(ETag);
            names->add(Expect);
            names->add(ExpectCT);
            names->add(Expires);
            names->add(From);
            names->add(FrontEndHttps);
            names->add(Host);
            names->add(IfMatch);
            names->add(IfModifiedSince);
            names->add(IfNoneMatch);
            names->add(IfRange);
            names->add(IfUnmodifiedSince);
            names->add(KeepAlive);
            names->add(LastModified);
            names->add(Link);
            names->add(Location);
            names->add(MaxForwards);
            names->add(Origin);
            names->add(P3P);
            names->add(Pragma);
            names->add(ProxyAuthenticate);
            names->add(ProxyAuthorization);
            names->add(ProxyConnection);
            names->add(Range);
            names->add(Referer);
            names->add(RefererPolicy);
            names->add(Refresh);
            names->add(RetryAfter);
            names->add(SaveData);
            names->add(SecWebSocketKey);
            names->add(SecWebSocketAccept);
            names->add(Server);
            names->add(SetCookie);
            names->add(SecTokenBinding);
            names->add(SecFetchDest);
            names->add(SecFetchMode);
            names->add(SecFetchSite);
            names->add(SecFetchUser);
            names->add(StrictTransportSecurity);
            names->add(TE);
            names->add(Timestamp);
            names->add(Trailer);
            names->add(TransferEncoding);
            names->add(Upgrade);
            names->add(UserAgent);
            names->add(VIP);
            names->add(Vary);
            names->add(Via);
            names->add(WWWAuthenticate);
            names->add(Warning);
            names->add(XAccelRedirect);
            names->add(XContentSecurityPolicyReportOnly);
            names->add(XContentTypeOptions);
            names->add(XForwardedFor);
            names->add(XForwardedProto);
            names->add(Forwarded);
            names->add(XFrameOptions);
            names->add(XPoweredBy);
            names->add(XRealIP);
            names->add(XRequestedWith);
            names->add(XThriftProtocol);
            names->add(XUACompatible);
            names->add(XWapProfile);
            names->add(XXSSProtection);
            names->add(SecWebSocketVersion);
            names->add(SecWebSocketExtensions);
            names->add(SecWebSocketOrigin);
            names->add(SecWebSocketKey1);
            names->add(SecWebSocketKey2);
            names->add(SecWebSocketKey3);
            names->add(SecWebSocketProtocol);
            names->add(ServerTiming);
            names->add(SourceMap);
            names->add(Digest);
            names->add(Authority);
        });
    }
    
    mProtocol = protocol;
    mValues = createHashMap<String, String>();
    mCookies = createArrayList<HttpCookie>();
    mLinks = createArrayList<HttpHeaderLink>();

    reset();
}

void _HttpHeader::addHttpHeader(sp<_HttpHeader> h) {
    ForEveryOne(pairValue,h->mValues) {
        set(pairValue->getKey(),pairValue->getValue());
    }

    ForEveryOne(pairCookie,h->mCookies) {
        mCookies->add(pairCookie);
    }

    if(h->mLinks->size() != 0) {
        mLinks->add(h->mLinks);
    }

#define SET_VALUE(X) X = (h->X != nullptr)?h->X:nullptr;
    SET_VALUE(mAcceptCharSet);
    SET_VALUE(mAcceptCh);
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
    SET_VALUE(mTransferEncoding);
    SET_VALUE(mUpgrade);
    SET_VALUE(mWebSocketAccept);
    SET_VALUE(mWebSocketKey);
    SET_VALUE(mWebSocketProtocol);
    SET_VALUE(mWebSocketKey1);
    SET_VALUE(mWebSocketKey2);
    SET_VALUE(mWebSocketKey3);
    SET_VALUE(mWebSocketVersion);
    SET_VALUE(mWebSocketExtensions);
    SET_VALUE(mWebSocketOrigin);
    SET_VALUE(mOrigin);
    SET_VALUE(mPragma);
    SET_VALUE(mAcceptRanges);
    SET_VALUE(mAltSvc);
    SET_VALUE(mContentRange);
    SET_VALUE(mSecurityPolicy);
    SET_VALUE(mSecurityPolicyReportOnly);

    SET_VALUE(mCrossOriginEmbedderPolicy);
    SET_VALUE(mCrossOriginOpenerPolicy);
    SET_VALUE(mCrossOriginResourcePolicy);
    SET_VALUE(mDate);
    SET_VALUE(mExpect);
    SET_VALUE(mExpectCT);
    SET_VALUE(mExpires);
    SET_VALUE(mFrom);
    SET_VALUE(mRange);
    SET_VALUE(mReferer);
    SET_VALUE(mRefererPolicy);
    SET_VALUE(mVary);
    SET_VALUE(mVia);
    SET_VALUE(mHeaderServer);
    SET_VALUE(mWarning);
    SET_VALUE(mDnt);
    SET_VALUE(mSaveData);
    SET_VALUE(mFetchDest);
    SET_VALUE(mFetchMode);
    SET_VALUE(mFetchSite);
    SET_VALUE(mFetchUser);
    SET_VALUE(mServerTiming);
    SET_VALUE(mSourceMap);
    SET_VALUE(mAuthority);
#undef SET_VALUE
}

void _HttpHeader::reset() { 
    mValues->clear(); 
    mCookies->clear();
    mLinks->clear();
    mVersion = createHttpHeaderVersion();
    
    mAcceptCharSet = nullptr;
    mAccept = nullptr;
    mAcceptCh = nullptr;
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

    mTransferEncoding = nullptr;
    mUpgrade = nullptr;
    mWebSocketAccept = nullptr;
    mWebSocketKey = nullptr;
    mWebSocketProtocol = nullptr;
    mWebSocketKey1 = nullptr;
    mWebSocketKey2 = nullptr;
    mWebSocketKey3 = nullptr;
    mWebSocketVersion = nullptr;
    mWebSocketExtensions = nullptr;
    mWebSocketOrigin = nullptr;
    mOrigin = nullptr;
    mPragma = nullptr;
    mAcceptRanges = nullptr;
    mAltSvc = nullptr;
    mContentRange = nullptr;
    mSecurityPolicy = nullptr;
    mSecurityPolicyReportOnly = nullptr;

    mCrossOriginEmbedderPolicy = nullptr;
    mCrossOriginOpenerPolicy = nullptr;
    mCrossOriginResourcePolicy = nullptr;

    mDate = nullptr;
    mExpect = nullptr;
    mExpectCT = nullptr;
    mExpires = nullptr;
    mFrom = nullptr;
    mRange = nullptr;
    mReferer = nullptr;
    mRefererPolicy = nullptr;
    mVary = nullptr;
    mVia = nullptr;
    mHeaderServer = nullptr;
    mWarning = nullptr;

    mDnt = nullptr;
    mSaveData = nullptr;
    mFetchDest = nullptr;
    mFetchMode = nullptr;
    mFetchSite = nullptr;
    mFetchUser = nullptr;
    mServerTiming = nullptr;
    mSourceMap = nullptr;

    mAuthority = nullptr;

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
            case TypeAuthority: {
                mAuthority = value;
                return;
            }

            case TypePath: {
                mUrl = createHttpUrl();
                mUrl->import(value);
                return;
            }

            case TypeMethod: {
                mMethod = st(HttpMethod)::toId(value);
                return;
            }

            case TypeScheme: {
                //TODO
                return;
            }

            case TypeStatus: {
                mResponseStatus = value->toBasicInt();
                return;
            }

            case TypeProtocol: {
                //TODO
                return;
            }
            
            case TypeAcceptCharset:{
                if(mAcceptCharSet == nullptr) {
                    mAcceptCharSet = createHttpHeaderAcceptCharSet();
                }
                mAcceptCharSet->import(value);
                return;
            }

            case TypeAcceptCh: {
                if(mAcceptCh == nullptr) {
                    mAcceptCh = createHttpHeaderAcceptCh();
                }
                mAcceptCh->import(value);
                return;
            }

            case TypeAccept:{
                if(mAccept == nullptr) {
                    mAccept = createHttpHeaderAccept();
                }
                mAccept->import(value);
                return;
            }

            case TypeAcceptEncoding:{
                if(mAcceptEncoding == nullptr) {
                    mAcceptEncoding = createHttpHeaderAcceptEncoding();
                }
                mAcceptEncoding->import(value);
                return;
            }

            case TypeAcceptLanguage: {
                if(mAcceptLanguage == nullptr) {
                    mAcceptLanguage = createHttpHeaderAcceptLanguage();
                }
                mAcceptLanguage->import(value);
                return;
            }

            case TypeTransferEncoding: {
                if(mTransferEncoding == nullptr) {
                    mTransferEncoding = createHttpHeaderTransferEncoding();
                }
                mTransferEncoding->import(value);
                return;
            }

            case TypeAcceptPatch: {
                if(mAcceptPatch == nullptr) {
                    mAcceptPatch = createHttpHeaderAcceptPatch();
                }
                mAcceptPatch->import(value);
                return;
            }

            case TypeAccessControlAllowCredentials: {
                if(mAllowCredentials == nullptr) {
                    mAllowCredentials = createHttpHeaderAccessControlAllowCredentials();
                }
                mAllowCredentials->import(value);
                return;
            }

            case TypeAccessControlAllowHeaders: {
                if(mAllowHeaders == nullptr) {
                    mAllowHeaders = createHttpHeaderAccessControlAllowHeaders();
                }
                mAllowHeaders->import(value);
                return;
            }

            case TypeAccessControlAllowMethods: {
                if(mAllowMethods == nullptr) {
                    mAllowMethods = createHttpHeaderAccessControlAllowMethods();
                }
                mAllowMethods->import(value);
                return;
            }

            case TypeAccessControlAllowOrigin: {
                if(mAllowOrigin == nullptr) {
                    mAllowOrigin = createHttpHeaderAccessControlAllowOrigin();
                }
                mAllowOrigin->import(value);
                return;
            }

            case TypeAccessControlExposeHeaders: {
                if(mExposeHeaders == nullptr) {
                    mExposeHeaders = createHttpHeaderAccessControlExposeHeaders();
                }
                mExposeHeaders->import(value);
                return;
            }
            
            case TypeAccessControlMaxAge: {
                if(mMaxAge == nullptr) {
                    mMaxAge = createHttpHeaderAccessControlMaxAge();
                }
                mMaxAge->import(value);
                return;
            }

            case TypeAccessControlRequestHeaders: {
                if(mRequestHeaders == nullptr) {
                    mRequestHeaders = createHttpHeaderAccessControlRequestHeaders();
                }
                mRequestHeaders->import(value);
                return;
            }

            case TypeAccessControlRequestMethod: {
                if(mRequestMethod == nullptr) {
                    mRequestMethod = createHttpHeaderAccessControlRequestMethod();
                }
                mRequestMethod->import(value);
                return;
            }

            case TypeAge: {
                if(mAge == nullptr) {
                    mAge = createHttpHeaderAge();
                }
                mAge->import(value);
                return;
            }

            case TypeAllow: {
                if(mAllow == nullptr) {
                    mAllow = createHttpHeaderAllow();
                }
                mAllow->import(value);
                return;
            }

            case TypeAuthorization: {
                if(mAuthorization == nullptr) {
                    mAuthorization = createHttpHeaderAuthorization();
                }
                mAuthorization->import(value);
                return;
            }
            
            case TypeCacheControl: {
                if(mCacheControl == nullptr) {
                    mCacheControl = createHttpHeaderCacheControl();
                }
                mCacheControl->import(value);
                return;
            }

            //TODO:ClearSiteData

            case TypeContentDisposition: {
                if(mContentDisposition == nullptr) {
                    mContentDisposition = createHttpHeaderContentDisposition();
                }
                mContentDisposition->import(value);
                return;
            }

            case TypeContentEncoding: {
                if(mContentEncoding == nullptr) {
                    mContentEncoding = createHttpHeaderContentEncoding();
                }
                mContentEncoding->import(value);
                return;
            }

            case TypeContentLanguage: {
                if(mContentLanguage == nullptr) {
                    mContentLanguage = createHttpHeaderContentLanguage();
                }
                mContentLanguage->import(value);
                return;
            }

            case TypeContentLength: {
                if(mContentLength == nullptr) {
                    mContentLength = createHttpHeaderContentLength();
                }
                mContentLength->import(value);
                return;
            }

            case TypeContentLocation: {
                if(mContentLocation == nullptr) {
                    mContentLocation = createHttpHeaderContentLocation();
                }
                mContentLocation->import(value);
                return;
            }

            case TypeContentType: {
                if(mContentType == nullptr) {
                    mContentType = createHttpHeaderContentType();
                }
                mContentType->import(value);
                return;
            }

            case TypeForwarded: {
                if(mForwarded == nullptr) {
                    mForwarded = createHttpHeaderForwarded();
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
                    mIfModifiedSince = createHttpHeaderIfModifiedSince();
                }
                mIfModifiedSince->import(value);
                return;
            }

            case TypeIfRange: {
                if(mIfRange == nullptr) {
                    mIfRange = createHttpHeaderIfRange();
                }
                mIfRange->import(value);
                return;
            }

            case TypeIfUnmodifiedSince: {
                if(mIfUnmodifiedSince == nullptr) {
                    mIfUnmodifiedSince = createHttpHeaderIfUnmodifiedSince();
                }
                mIfUnmodifiedSince->import(value);
                return;
            }

            case TypeProxyAuthenticate: {
                if(mProxyAuthenticate == nullptr) {
                    mProxyAuthenticate = createHttpHeaderProxyAuthenticate();
                }
                mProxyAuthenticate->import(value);
                return;
            }

            case TypeProxyAuthorization: {
                if(mProxyAuthorization == nullptr) {
                    mProxyAuthorization = createHttpHeaderProxyAuthorization();
                }
                mProxyAuthorization->import(value);
                return;
            }
            
            case TypeStrictTransportSecurity: {
                if(mTransportSecurity == nullptr) {
                    mTransportSecurity = createHttpHeaderStrictTransportSecurity();
                }
                mTransportSecurity->import(value);
                return;
            }

            case TypeXFrameOptions: {
                if(mXFrameOptions == nullptr) {
                    mXFrameOptions = createHttpHeaderXFrameOptions();
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

            case TypeCookie:
            case TypeSetCookie: {
                auto c = createHttpCookieParser()->parse(value);
                if(mCookies == nullptr) {
                    mCookies = c;
                } else {
                    mCookies->add(c);
                }
                return;
            }

            case TypeSecWebSocketAccept: {
                if(mWebSocketAccept == nullptr) {
                    mWebSocketAccept = createHttpHeaderSecWebSocketAccept();
                }
                mWebSocketAccept->import(value);
                return;
            }

            case TypeSecWebSocketKey: {
                if(mWebSocketKey == nullptr) {
                    mWebSocketKey = createHttpHeaderSecWebSocketKey();
                }
                mWebSocketKey->import(value);
                return;
            }

            case TypeSecWebSocketVersion: {
                if(mWebSocketVersion == nullptr) {
                    mWebSocketVersion = createHttpHeaderSecWebSocketVersion();
                }
                mWebSocketVersion->import(value);
                return;
            }

            case TypeSecWebSocketExtensions: {
                if(mWebSocketExtensions == nullptr) {
                    mWebSocketExtensions = createHttpHeaderSecWebSocketExtensions();
                }
                mWebSocketExtensions->import(value);
                return;
            }

            case TypeSecWebSocketOrigin: {
                if(mWebSocketOrigin == nullptr) {
                    mWebSocketOrigin = createHttpHeaderSecWebSocketOrigin();
                }
                mWebSocketOrigin->import(value);
                return;
            }

            case TypeSecWebSocketKey1: {
                if(mWebSocketKey1 == nullptr) {
                    mWebSocketKey1 = createHttpHeaderSecWebSocketKey();
                }
                mWebSocketKey1->import(value);
                return;
            }

            case TypeSecWebSocketKey2: {
                if(mWebSocketKey2 == nullptr) {
                    mWebSocketKey2 = createHttpHeaderSecWebSocketKey();
                }
                mWebSocketKey2->import(value);
                return;
            }

            case TypeSecWebSocketKey3: {
                if(mWebSocketKey3 == nullptr) {
                    mWebSocketKey3 = createHttpHeaderSecWebSocketKey();
                }
                mWebSocketKey3->import(value);
                return;
            }

            case TypeSecWebSocketProtocol: {
                if(mWebSocketProtocol == nullptr) {
                    mWebSocketProtocol = createHttpHeaderSecWebSocketProtocol();
                }
                mWebSocketProtocol->import(value);
                return;
            }

            case TypeOrigin: {
                if(mOrigin == nullptr) {
                    mOrigin = createHttpHeaderOrigin();
                }
                mOrigin->import(value);
                return;
            }

            case TypePragma: {
                if(mPragma == nullptr) {
                    mPragma = createHttpHeaderPragma();
                }
                mPragma->import(value);
                return;
            }

            case TypeAcceptRanges: {
                if(mAcceptRanges == nullptr) {
                    mAcceptRanges = createHttpHeaderAcceptRanges();
                }
                mAcceptRanges->import(value);
                return;
            }

            case TypeAltSvc: {
                if(mAltSvc == nullptr) {
                    mAltSvc = createHttpHeaderAltSvc();
                }
                mAltSvc->import(value);
                return;
            }

            case TypeContentRange: {
                if(mContentRange == nullptr) {
                    mContentRange = createHttpHeaderContentRange();
                }
                mContentRange->import(value);
                return;
            }

            case TypeContentSecurityPolicy: {
                if(mSecurityPolicy == nullptr) {
                    mSecurityPolicy = createHttpHeaderContentSecurityPolicy();
                }
                mSecurityPolicy->import(value);
                return;
            }

            case TypeContentSecurityPolicyReportOnly: {
                if(mSecurityPolicyReportOnly == nullptr) {
                    mSecurityPolicyReportOnly = createHttpHeaderContentSecurityPolicy();
                }
                mSecurityPolicyReportOnly->import(value);
                return;
            }

            case TypeCrossOriginEmbedderPolicy: {
                if(mCrossOriginEmbedderPolicy == nullptr) {
                    mCrossOriginEmbedderPolicy = createHttpHeaderCrossOriginEmbedderPolicy();
                }
                mCrossOriginEmbedderPolicy->import(value);
                return;
            }

            case TypeCrossOriginOpenerPolicy: {
                if(mCrossOriginOpenerPolicy == nullptr) {
                    mCrossOriginOpenerPolicy = createHttpHeaderCrossOriginOpenerPolicy();
                }
                mCrossOriginOpenerPolicy->import(value);
                return;
            }

            case TypeCrossOriginResourcePolicy: {
                if(mCrossOriginResourcePolicy == nullptr) {
                    mCrossOriginResourcePolicy = createHttpHeaderCrossOriginResourcePolicy();
                }
                mCrossOriginResourcePolicy->import(value);
                return;
            }

            case TypeDate: {
                if(mDate == nullptr) {
                    mDate = createHttpHeaderDate();
                }
                mDate->import(value);
                return;
            }

            case TypeExpect: {
                if(mExpect == nullptr) {
                    mExpect = createHttpHeaderExpect();
                }
                mExpect->import(value);
                return;
            }

            case TypeExpectCT: {
                if(mExpectCT == nullptr) {
                    mExpectCT = createHttpHeaderExpectCT();
                }
                mExpectCT->import(value);
                return;
            }

            case TypeExpires: {
                if(mExpires == nullptr) {
                    mExpires = createHttpHeaderExpires();
                }
                mExpires->import(value);
                return;
            }

            case TypeFrom: {
                if(mFrom == nullptr) {
                    mFrom = createHttpHeaderFrom();
                }
                mFrom->import(value);
                return;
            }

            case TypeRange: {
                if(mRange == nullptr) {
                    mRange = createHttpHeaderRange();
                }
                mRange->import(value);
                return;
            }

            case TypeReferer: {
                if(mReferer == nullptr) {
                    mReferer = createHttpHeaderReferer();
                }
                mReferer->import(value);
                return;
            }

            case TypeRefererPolicy: {
                if(mRefererPolicy == nullptr) {
                    mRefererPolicy = createHttpHeaderReferrerPolicy();
                }
                mRefererPolicy->import(value);
                return;
            }

            case TypeVary: {
                if(mVary == nullptr) {
                    mVary = createHttpHeaderVary();
                }
                mVary->import(value);
                return;
            }

            case TypeVia: {
                if(mVia == nullptr) {
                    mVia = createHttpHeaderVia();
                }
                mVia->import(value);
                return;
            }

            case TypeServer: {
                if(mHeaderServer == nullptr) {
                    mHeaderServer = createHttpHeaderServer();
                }
                mHeaderServer->import(value);
                return;
            }

            case TypeWarning: {
                if(mWarning == nullptr) {
                    mWarning = createHttpHeaderWarning();
                }
                mWarning->import(value);
                return;
            }

            case TypeDNT: {
                if(mDnt == nullptr) {
                    mDnt = createHttpHeaderDnt();
                }
                mDnt->import(value);
                return;
            }

            case TypeSaveData: {
                if(mSaveData == nullptr) {
                    mSaveData = createHttpHeaderSaveData();
                }
                mSaveData->import(value);
                return;
            }

            case TypeSecFetchDest: {
                if(mFetchDest == nullptr) {
                    mFetchDest = createHttpHeaderSecFetchDest();
                }
                mFetchDest->import(value);
                return;
            }

            case TypeSecFetchMode: {
                if(mFetchMode == nullptr) {
                    mFetchMode = createHttpHeaderSecFetchMode();
                }
                mFetchMode->import(value);
                return;
            }

            case TypeSecFetchSite: {
                if(mFetchSite == nullptr) {
                    mFetchSite = createHttpHeaderSecFetchSite();
                }
                mFetchSite->import(value);
                return;
            }

            case TypeSecFetchUser: {
                if(mFetchUser == nullptr) {
                    mFetchUser = createHttpHeaderSecFetchUser();
                }
                mFetchUser->import(value);
                return;
            }

            case TypeServerTiming: {
                if(mServerTiming == nullptr) {
                    mServerTiming = createHttpHeaderServerTiming();
                }
                mServerTiming->import(value);
                return;
            }

            case TypeSourceMap: {
                if(mSourceMap == nullptr) {
                    mSourceMap = createHttpHeaderSourceMap();
                }
                mSourceMap->import(value);
                return;
            }
        }
    }

    mValues->put(key->toLowerCase(), value);
}

String _HttpHeader::get(String header) {
    Integer id = idMaps->get(header->toLowerCase());
    if(id != nullptr) {
        LOG(ERROR)<<"http header:" <<names->get(id->toValue())->toChars()<<",should call get method directly";        
        switch(id->toValue()) {
            case TypeAcceptCharset:{
                if(mAcceptCharSet != nullptr) {
                    return mAcceptCharSet->toString();
                }
                break;
            }

            case TypeAccept:{
                if(mAccept != nullptr) {
                    return mAccept->toString();
                }
                break;
            }

            case TypeAcceptCh:{
                if(mAcceptCh != nullptr) {
                    return mAcceptCh->toString();
                }
                break;
            }

            case TypeAcceptEncoding:{
                if(mAcceptEncoding != nullptr) {
                    return mAcceptEncoding->toString();
                }
                break;
            }

            case TypeAcceptLanguage: {
                if(mAcceptLanguage != nullptr) {
                    return mAcceptLanguage->toString();
                }
                break;
            }

            case TypeTransferEncoding: {
                if(mTransferEncoding != nullptr) {
                    return mTransferEncoding->toString();
                }
                break;
            }

            case TypeAcceptPatch: {
                if(mAcceptPatch != nullptr) {
                    return mAcceptPatch->toString();
                }
                break;
            }

            case TypeAccessControlAllowCredentials: {
                if(mAllowCredentials != nullptr) {
                    return mAllowCredentials->toString();
                }
                break;
            }

            case TypeAccessControlAllowHeaders: {
                if(mAllowHeaders != nullptr) {
                    return mAllowHeaders->toString();
                }
                break;
            }

            case TypeAccessControlAllowMethods: {
                if(mAllowMethods != nullptr) {
                    return mAllowMethods->toString();
                }
                break;
            }

            case TypeAccessControlAllowOrigin: {
                if(mAllowOrigin != nullptr) {
                    return mAllowOrigin->toString();
                }
                break;
            }

            case TypeAccessControlExposeHeaders: {
                if(mExposeHeaders != nullptr) {
                    return mExposeHeaders->toString();
                }
                break;
            }
            
            case TypeAccessControlMaxAge: {
                if(mMaxAge != nullptr) {
                    return mMaxAge->toString();
                }
                break;
            }

            case TypeAccessControlRequestHeaders: {
                if(mRequestHeaders != nullptr) {
                    return mRequestHeaders->toString();
                }
                break;
            }

            case TypeAccessControlRequestMethod: {
                if(mRequestMethod != nullptr) {
                    return mRequestMethod->toString();
                }
                break;
            }

            case TypeAge: {
                if(mAge != nullptr) {
                    return mAge->toString();
                }
                break;
            }

            case TypeAllow: {
                if(mAllow != nullptr) {
                    return mAllow->toString();
                }
                break;
            }

            case TypeAuthorization: {
                if(mAuthorization != nullptr) {
                    return mAuthorization->toString();
                }
                break;
            }
            
            case TypeCacheControl: {
                if(mCacheControl != nullptr) {
                    if(mResponseReason != nullptr) {
                        return mCacheControl->toString(st(HttpPacket)::Response);
                    } else {
                        return mCacheControl->toString(st(HttpPacket)::Request);
                    }
                }
                break;
            }

            //TODO:ClearSiteData

            case TypeContentDisposition: {
                if(mContentDisposition != nullptr) {
                    return mContentDisposition->toString();
                }
                break;
            }

            case TypeContentEncoding: {
                if(mContentEncoding != nullptr) {
                    return mContentEncoding->toString();
                }
                break;
            }

            case TypeContentLanguage: {
                if(mContentLanguage != nullptr) {
                    return mContentLanguage->toString();
                }
                break;
            }

            case TypeContentLength: {
                if(mContentLength != nullptr) {
                    return mContentLength->toString();
                }
                break;
            }

            case TypeContentLocation: {
                if(mContentLocation != nullptr) {
                    return mContentLocation->toString();
                }
                break;
            }

            case TypeContentType: {
                if(mContentType != nullptr) {
                    return mContentType->toString();
                }
                break;
            }

            case TypeForwarded: {
                if(mForwarded != nullptr) {
                    return mForwarded->toString();
                }
                break;
            }

            case TypeConnection: {
                if(mConnection != nullptr) {
                    return mConnection->toString();
                }
                break;
            }

            case TypeDigest: {
                if(mHeaderDigest != nullptr) {
                    return mHeaderDigest->toString();
                }
                break;
            }

            case TypeHost: {
                if(mHost != nullptr) {
                    return mHost->toString();
                }
                break;
            }

            case TypeKeepAlive: {
                if(mKeepAlive != nullptr) {
                    return mKeepAlive->toString();
                }
                break;
            }

            case TypeLink: {
                LOG(ERROR)<<"not support get function fro link";
                break;
            }

            case TypeIfMatch: {
                if(mIfMatch != nullptr) {
                    return mIfMatch->toString();
                }
                break;
            }

            case TypeIfNoneMatch: {
                if(mIfNoneMatch != nullptr) {
                    return mIfNoneMatch->toString();
                }
                break;
            }

            case TypeRetryAfter: {
                if(mRetryAfter != nullptr) {
                    return mRetryAfter->toString();
                }
                break;
            }

            case TypeUserAgent: {
                if(mUserAgent != nullptr) {
                    return mUserAgent->toString();
                }
                break;
            }
            
            case TypeIfModifiedSince: {
                if(mIfModifiedSince != nullptr) {
                    return mIfModifiedSince->toString();
                }
                break;
            }

            case TypeIfRange: {
                if(mIfRange != nullptr) {
                    return mIfRange->toString();
                }
                break;
            }

            case TypeIfUnmodifiedSince: {
                if(mIfUnmodifiedSince != nullptr) {
                    return mIfUnmodifiedSince->toString();
                }
                break;
            }

            case TypeProxyAuthenticate: {
                if(mProxyAuthenticate != nullptr) {
                    return mProxyAuthenticate->toString();
                }
                break;
            }

            case TypeProxyAuthorization: {
                if(mProxyAuthorization != nullptr) {
                    return mProxyAuthorization->toString();
                }
                break;
            }
            
            case TypeStrictTransportSecurity: {
                if(mTransportSecurity != nullptr) {
                    return mTransportSecurity->toString();
                }
                break;
            }

            case TypeXFrameOptions: {
                if(mXFrameOptions != nullptr) {
                    return mXFrameOptions->toString();
                }
                break;
            }

            case TypeUpgrade: {
                if(mUpgrade != nullptr) {
                    return mUpgrade->toString();
                }
                break;
            }

            case TypeCookie:
            case TypeSetCookie: {
                //TODO
                break;
            }

            case TypeSecWebSocketAccept: {
                if(mWebSocketAccept != nullptr) {
                    return mWebSocketAccept->toString();
                }
                break;
            }

            case TypeSecWebSocketKey: {
                if(mWebSocketKey != nullptr) {
                    return mWebSocketKey->toString();
                }
                break;
            }

            case TypeSecWebSocketVersion: {
                if(mWebSocketVersion != nullptr) {
                    return mWebSocketVersion->toString();
                }
                break;
            }

            case TypeSecWebSocketExtensions: {
                if(mWebSocketExtensions != nullptr) {
                    return mWebSocketExtensions->toString();
                }
                break;
            }

            case TypeSecWebSocketOrigin: {
                if(mWebSocketOrigin != nullptr) {
                    return mWebSocketOrigin->toString();
                }
                break;
            }

            case TypeSecWebSocketKey1: {
                if(mWebSocketKey1 != nullptr) {
                    return mWebSocketKey1->toString();
                }
                break;
            }

            case TypeSecWebSocketKey2: {
                if(mWebSocketKey2 != nullptr) {
                    return mWebSocketKey2->toString();
                }
                break;
            }

            case TypeSecWebSocketKey3: {
                if(mWebSocketKey3 != nullptr) {
                    return mWebSocketKey3->toString();
                }
                break;
            }

            case TypeSecWebSocketProtocol: {
                if(mWebSocketProtocol != nullptr) {
                    return mWebSocketProtocol->toString();
                }
                break;
            }

            case TypeOrigin: {
                if(mOrigin != nullptr) {
                    return mOrigin->toString();
                }
                break;
            }

            case TypePragma: {
                if(mPragma != nullptr) {
                    return mPragma->toString();
                }
                break;
            }

            case TypeAcceptRanges: {
                if(mAcceptRanges != nullptr) {
                    return mAcceptRanges->toString();
                }
                break;
            }

            case TypeAltSvc: {
                if(mAltSvc != nullptr) {
                    return mAltSvc->toString();
                }
                break; 
            }

            case TypeContentRange: {
                if(mContentRange != nullptr) {
                    return mContentRange->toString();
                }
                break; 
            }

            case TypeContentSecurityPolicy: {
                if(mSecurityPolicy != nullptr) {
                    return mSecurityPolicy->toString();
                }
                break;
            }

            case TypeContentSecurityPolicyReportOnly: {
                if(mSecurityPolicyReportOnly != nullptr) {
                    return mSecurityPolicyReportOnly->toString();
                }
                break;
            }

            case TypeCrossOriginEmbedderPolicy: {
                if(mCrossOriginEmbedderPolicy != nullptr) {
                    return mCrossOriginEmbedderPolicy->toString();
                }
                break;
            }

            case TypeCrossOriginOpenerPolicy: {
                if(mCrossOriginOpenerPolicy != nullptr) {
                    return mCrossOriginOpenerPolicy->toString();
                }
                break;
            }

            case TypeCrossOriginResourcePolicy: {
                if(mCrossOriginResourcePolicy != nullptr) {
                    return mCrossOriginResourcePolicy->toString();
                }
                break;
            }

            case TypeDate: {
                if(mDate != nullptr) {
                    return mDate->toString();
                }
                break;
            }

            case TypeExpect: {
                if(mExpect != nullptr) {
                    return mExpect->toString();
                }
                break;
            }

            case TypeExpectCT: {
                if(mExpectCT != nullptr) {
                    return mExpectCT->toString();
                }
                break;
            }

            case TypeExpires: {
                if(mExpires != nullptr) {
                    return mExpires->toString();
                }
                break;
            }

            case TypeFrom: {
                if(mFrom != nullptr) {
                    return mFrom->toString();
                }
                break;
            }

            case TypeRange: {
                if(mRange != nullptr) {
                    return mRange->toString();
                }
                break;
            }

            case TypeReferer: {
                if(mReferer != nullptr) {
                    return mReferer->toString();
                }
                break;
            }

            case TypeRefererPolicy: {
                if(mRefererPolicy != nullptr) {
                    return mRefererPolicy->toString();
                }
                break;
            }

            case TypeVary: {
                if(mVary != nullptr) {
                    return mVary->toString();
                }
                break;
            }

            case TypeVia: {
                if(mVia != nullptr) {
                    return mVia->toString();
                }
                break;
            }

            case TypeServer: {
                if(mHeaderServer != nullptr) {
                    return mHeaderServer->toString();
                }
                break;
            }

            case TypeWarning: {
                if(mWarning != nullptr) {
                    return mWarning->toString();
                }
                break;
            }

            case TypeDNT: {
                if(mDnt != nullptr) {
                    return mDnt->toString();
                }
                break;
            }

            case TypeSaveData: {
                if(mSaveData != nullptr) {
                    return mSaveData->toString();
                }
                break;
            }

            case TypeSecFetchDest: {
                if(mFetchDest != nullptr) {
                    return mFetchDest->toString();
                }
                break;
            }

            case TypeSecFetchMode: {
                if(mFetchMode != nullptr) {
                    return mFetchMode->toString();
                }
                break;
            }

            case TypeSecFetchSite: {
                if(mFetchSite != nullptr) {
                    return mFetchSite->toString();
                }
                break;
            }

            case TypeSecFetchUser: {
                if(mFetchUser != nullptr) {
                    return mFetchUser->toString();
                }
                break;
            }

            case TypeServerTiming: {
                if(mServerTiming != nullptr) {
                    return mServerTiming->toString();
                }
                break;
            }

            case TypeSourceMap: {
                if(mSourceMap != nullptr) {
                    return mSourceMap->toString();
                }
                break;
            }
        }
    }

    return mValues->get(header->toLowerCase());
}

int _HttpHeader::size() { 
    return mValues->size(); 
}

int _HttpHeader::getMethod() { 
    return mMethod; 
}

void _HttpHeader::setMethod(int v) { 
    mMethod = v; 
}

HttpUrl _HttpHeader::getUrl() { 
    return mUrl; 
}

void _HttpHeader::setUrl(HttpUrl u) { 
    mUrl = u; 
}

int _HttpHeader::getResponseStatus() { 
    return mResponseStatus; 
}

void _HttpHeader::setResponseStatus(int s) { 
    mResponseStatus = s;
}

String _HttpHeader::getResponseReason() { 
    return mResponseReason; 
}

void _HttpHeader::setResponseReason(String s) { 
    mResponseReason = s; 
}

String _HttpHeader::getAuthority() {
    return mAuthority;
}

void _HttpHeader::setAuthority(String s) {
    mAuthority = s;
}

int _HttpHeader::getType() { 
    return mType; 
}

void _HttpHeader::setType(int v) { 
    mType = v; 
}

int _HttpHeader::getProtocol() {
    return mProtocol;
}

void _HttpHeader::setProtocol(int protocol) {
    mProtocol = protocol;
}

void _HttpHeader::addCookie(HttpCookie c) { 
    mCookies->add(c); 
}

ArrayList<HttpCookie> _HttpHeader::getCookies() { 
    return mCookies; 
}

//HttpHeaderAcceptCharSet
HttpHeaderAcceptCharSet _HttpHeader::getAcceptCharSet() {
    return mAcceptCharSet;
}

void _HttpHeader::setAcceptCharSet(HttpHeaderAcceptCharSet v) {
    mAcceptCharSet = v;
}

//HttpHeaderAccept
HttpHeaderAccept _HttpHeader::getAccept() {
    return mAccept;
}

void _HttpHeader::setAccept(HttpHeaderAccept s) {
    mAccept = s;
}

//HttpHeaderAcceptEncoding
HttpHeaderAcceptEncoding _HttpHeader::getAcceptEncoding() {
    return mAcceptEncoding;
}

void _HttpHeader::setAcceptEncoding(HttpHeaderAcceptEncoding s) {
    mAcceptEncoding = s;
}

//HttpHeaderAcceptLanguage
HttpHeaderAcceptLanguage _HttpHeader::getAcceptLanguage() {
    return mAcceptLanguage;
}

void _HttpHeader::setAcceptLanguage(HttpHeaderAcceptLanguage s) {
    mAcceptLanguage = s;
}

//HttpHeaderAcceptPatch
HttpHeaderAcceptPatch _HttpHeader::getAcceptPatch() {
    return mAcceptPatch;
}

void _HttpHeader::setAcceptPatch(HttpHeaderAcceptPatch s) {
    mAcceptPatch = s;
}

//HttpHeaderAccessControlAllowCredentials
HttpHeaderAccessControlAllowCredentials _HttpHeader::getAllowCredentials() {
    return mAllowCredentials;
}

void _HttpHeader::setAllowCredentials(HttpHeaderAccessControlAllowCredentials s) {
    mAllowCredentials = s;
}

//HttpHeaderAccessControlAllowHeaders
HttpHeaderAccessControlAllowHeaders _HttpHeader::getAllowHeaders() {
    return mAllowHeaders;
}

void _HttpHeader::setAllowHeaders(HttpHeaderAccessControlAllowHeaders s) {
    mAllowHeaders = s;
}

//HttpHeaderAccessControlAllowMethods
HttpHeaderAccessControlAllowMethods _HttpHeader::getAllowMethods() {
    return mAllowMethods;
}

void _HttpHeader::setAllowMethods(HttpHeaderAccessControlAllowMethods s) {
    mAllowMethods = s;
}

//HttpHeaderAccessControlAllowOrigin
HttpHeaderAccessControlAllowOrigin _HttpHeader::getAllowOrigin() {
    return mAllowOrigin;
}

void _HttpHeader::setAllowOrigin(HttpHeaderAccessControlAllowOrigin s) {
    mAllowOrigin = s;
}

//HttpHeaderAccessControlExposeHeaders
HttpHeaderAccessControlExposeHeaders _HttpHeader::getExposeHeaders() {
    return mExposeHeaders;
}

void _HttpHeader::setExposeHeaders(HttpHeaderAccessControlExposeHeaders s) {
    mExposeHeaders = s;
}

//HttpHeaderAccessControlMaxAge
HttpHeaderAccessControlMaxAge _HttpHeader::getMaxAge() {
    return mMaxAge;
}

void _HttpHeader::setMaxAge(HttpHeaderAccessControlMaxAge s) {
    mMaxAge = s;
}

//HttpHeaderAccessControlRequestHeaders
HttpHeaderAccessControlRequestHeaders _HttpHeader::getRequestHeaders() {
    return mRequestHeaders;
}

void _HttpHeader::setReqeuestHeaders(HttpHeaderAccessControlRequestHeaders s) {
    mRequestHeaders = s;
}

//HttpHeaderAccessControlRequestMethod
HttpHeaderAccessControlRequestMethod _HttpHeader::getRequestMethod() {
    return mRequestMethod;
}

void _HttpHeader::setRequestMethod(HttpHeaderAccessControlRequestMethod s) {
    mRequestMethod = s;
}

//HttpHeaderAge
HttpHeaderAge _HttpHeader::getAge() {
    return mAge;
}

void _HttpHeader::setAge(HttpHeaderAge s) {
    mAge = s;
}

//HttpHeaderAllow
HttpHeaderAllow _HttpHeader::getAllow() {
    return mAllow;
}

void _HttpHeader::setAllow(HttpHeaderAllow s) {
    mAllow = s;
}

//HttpHeaderAuthorization
HttpHeaderAuthorization _HttpHeader::getAuthorization() {
    return mAuthorization;
}

void _HttpHeader::setAuthorization(HttpHeaderAuthorization s) {
    mAuthorization = s;
}

//HttpHeaderCacheControl
HttpHeaderCacheControl _HttpHeader::getCacheControl() {
    return mCacheControl;
}

void _HttpHeader::setCacheControl(HttpHeaderCacheControl s) {
    mCacheControl = s;
}

//HttpHeaderClearSiteData
HttpHeaderClearSiteData _HttpHeader::getClearSiteData() {
    return mClearSiteData;
}

void _HttpHeader::setClearSiteData(HttpHeaderClearSiteData s) {
    mClearSiteData = s;
}

//HttpHeaderContentDisposition
HttpHeaderContentDisposition _HttpHeader::getContentDisposition() {
    return mContentDisposition;
}

void _HttpHeader::setContentDisposition(HttpHeaderContentDisposition s) {
    mContentDisposition = s;
}

//HttpHeaderContentEncoding
HttpHeaderContentEncoding _HttpHeader::getContentEncoding() {
    return mContentEncoding;
}

void _HttpHeader::setContentEncoding(HttpHeaderContentEncoding s) {
    mContentEncoding = s;
}

//HttpHeaderContentLanguage
HttpHeaderContentLanguage _HttpHeader::getContentLanguage() {
    return mContentLanguage;
}

void _HttpHeader::setContentLanguage(HttpHeaderContentLanguage s) {
    mContentLanguage = s;
}

//HttpHeaderContentLength
HttpHeaderContentLength _HttpHeader::getContentLength() {
    return mContentLength;
}

void _HttpHeader::setContentLength(HttpHeaderContentLength s) {
    mContentLength = s;
}

//HttpHeaderContentLocation
HttpHeaderContentLocation _HttpHeader::getContentLocation() {
    return mContentLocation;
}

void _HttpHeader::setContentLocation(HttpHeaderContentLocation s) {
    mContentLocation = s;
}

//HttpHeaderContentType
HttpHeaderContentType _HttpHeader::getContentType() {
    return mContentType;
}

void _HttpHeader::setContentType(HttpHeaderContentType s) {
    mContentType = s;
}

//HttpHeaderForwarded
HttpHeaderForwarded _HttpHeader::getForwarded() {
    return mForwarded;
}

void _HttpHeader::setForwarded(HttpHeaderForwarded s) {
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

//HttpHeaderIfModifiedSince
HttpHeaderIfModifiedSince _HttpHeader::getIfModifiedSince() {
    return mIfModifiedSince;
}

void _HttpHeader::setIfModifiedSince(HttpHeaderIfModifiedSince s) {
    mIfModifiedSince = s;
}

//HttpHeaderIfRange
HttpHeaderIfRange _HttpHeader::getIfRange() {
    return mIfRange;
}

void _HttpHeader::setIfRange(HttpHeaderIfRange s) {
    mIfRange = s;
}

//HttpHeaderIfUnmodifiedSince
HttpHeaderIfUnmodifiedSince _HttpHeader::getIfUnmodifiedSince() {
    return mIfUnmodifiedSince;
}

void _HttpHeader::setIfUnmodifiedSince(HttpHeaderIfUnmodifiedSince s) {
    mIfUnmodifiedSince = s;
}

//HttpHeaderProxyAuthenticate
HttpHeaderProxyAuthenticate _HttpHeader::getProxyAuthenticate() {
    return mProxyAuthenticate;
}

void _HttpHeader::setProxyAuthenticate(HttpHeaderProxyAuthenticate s) {
    mProxyAuthenticate = s;
}

//HttpHeaderProxyAuthorization
HttpHeaderProxyAuthorization _HttpHeader::getProxyAuthorization() {
    return mProxyAuthorization;
}

void _HttpHeader::setProxyAuthorization(HttpHeaderProxyAuthorization s) {
    mProxyAuthorization = s;
}

//HttpHeaderStrictTransportSecurity
HttpHeaderStrictTransportSecurity _HttpHeader::getStrictTransportSecurity() {
    return mTransportSecurity;
}

void _HttpHeader::setStrictTransportSecurity(HttpHeaderStrictTransportSecurity s) {
    mTransportSecurity = s;
}

//HttpHeaderVersion
HttpHeaderVersion _HttpHeader::getVersion() {
    return mVersion;
}

void _HttpHeader::setVersion(HttpHeaderVersion s) {
    mVersion = s;
}

//HttpHeaderXFrameOptions
HttpHeaderXFrameOptions _HttpHeader::getXFrameOptions() {
    return mXFrameOptions;
}

void _HttpHeader::setXFrameOptions(HttpHeaderXFrameOptions s) {
    mXFrameOptions = s;
}

//HttpHeaderTransferEncoding
void _HttpHeader::setTransferEncoding(HttpHeaderTransferEncoding s) {
    mTransferEncoding = s;
}

//HttpheaderUpgrade
void _HttpHeader::setUpgrade(HttpHeaderUpgrade s) {
    mUpgrade = s;
}

HttpHeaderUpgrade _HttpHeader::getUpgrade() {
    return mUpgrade;
}

 //HttpHeaderSecWebSocketAccept
void _HttpHeader::setWebSocketAccept(HttpHeaderSecWebSocketAccept s) {
    mWebSocketAccept = s;
}

HttpHeaderSecWebSocketAccept _HttpHeader::getWebSocketAccept() {
    return mWebSocketAccept;
}

//HttpHeaderSecWebSocketKey 
void _HttpHeader::setWebSocketKey(HttpHeaderSecWebSocketKey s) {
    mWebSocketKey = s;
}

HttpHeaderSecWebSocketKey _HttpHeader::getWebSocketKey() {
    return mWebSocketKey;
}

//HttpHeaderSecWebSocketProtocol 
void _HttpHeader::setWebSocketProtocol(HttpHeaderSecWebSocketProtocol s) {
    mWebSocketProtocol = s;
}

HttpHeaderSecWebSocketProtocol _HttpHeader::getWebSocketProtocol() {
    return mWebSocketProtocol;
}

//HttpHeaderSecWebSocketKey1
void _HttpHeader::setWebSocketKey1(HttpHeaderSecWebSocketKey s) {
    mWebSocketKey1 = s;
}

HttpHeaderSecWebSocketKey _HttpHeader::getWebSocketKey1() {
    return mWebSocketKey1;
}

//HttpHeaderSecWebSocketKey2
void _HttpHeader::setWebSocketKey2(HttpHeaderSecWebSocketKey s) {
    mWebSocketKey2 = s;
}

HttpHeaderSecWebSocketKey _HttpHeader::getWebSocketKey2() {
    return mWebSocketKey2;
}

//HttpHeaderSecWebSocketKey3
void _HttpHeader::setWebSocketKey3(HttpHeaderSecWebSocketKey s) {
    mWebSocketKey3 = s;
}

HttpHeaderSecWebSocketKey _HttpHeader::getWebSocketKey3() {
    return mWebSocketKey3;
}

//HttpHeaderSecWebSocketVersion
void _HttpHeader::setWebSocketVersion(HttpHeaderSecWebSocketVersion s) {
    mWebSocketVersion = s;
}

HttpHeaderSecWebSocketVersion _HttpHeader::getWebSocketVersion() {
    return mWebSocketVersion;
}

//HttpHeaderSecWebSocketExtensions
void _HttpHeader::setWebSocketExtensions(HttpHeaderSecWebSocketExtensions s) {
    mWebSocketExtensions = s;
}

HttpHeaderSecWebSocketExtensions _HttpHeader::getWebSocketExtensions() {
    return mWebSocketExtensions;
}

//HttpHeaderSecWebSocketOrigin
void _HttpHeader::setWebSocketOrigin(HttpHeaderSecWebSocketOrigin s) {
    mWebSocketOrigin = s;
}

HttpHeaderSecWebSocketOrigin _HttpHeader::getWebSocketOrigin() {
    return mWebSocketOrigin;
}

//HttpHeaderOrigin
void _HttpHeader::setOrigin(HttpHeaderOrigin s) {
    mOrigin = s;
}

HttpHeaderOrigin _HttpHeader::getOrigin() {
    return mOrigin;
}

//HttpHeaderPragma
void _HttpHeader::setPragma(HttpHeaderPragma s) {
    mPragma = s;
}

HttpHeaderPragma _HttpHeader::getPragma() {
    return mPragma;
}

//HttpHeaderAcceptRanges
void _HttpHeader::setHttpHeaderAcceptRanges(HttpHeaderAcceptRanges s) {
    mAcceptRanges = s;
}

HttpHeaderAcceptRanges _HttpHeader::getAcceptRanges() {
    return mAcceptRanges;
}

//HttpHeaderAltSvc
void _HttpHeader::setAltSvc(HttpHeaderAltSvc s) {
    mAltSvc = s;
}

HttpHeaderAltSvc _HttpHeader::getAltSvc() {
    return mAltSvc;
}

//HttpHeaderContentRange
void _HttpHeader::setContentRange(HttpHeaderContentRange s) {
    mContentRange = s;
}

HttpHeaderContentRange _HttpHeader::getContentRange() {
    return mContentRange;
}

//HttpHeaderContentSecurityPolicy
void _HttpHeader::setSecurityPolicy(HttpHeaderContentSecurityPolicy s) {
    mSecurityPolicy = s;
}
HttpHeaderContentSecurityPolicy _HttpHeader::getSecurityPolicy() {
    return mSecurityPolicy;
}

void _HttpHeader::setSecurityPolicyReportOnly(HttpHeaderContentSecurityPolicy s) {
    mSecurityPolicyReportOnly = s;
}

HttpHeaderContentSecurityPolicy _HttpHeader::getSecurityPolicyReportOnly() {
    return mSecurityPolicyReportOnly;
}

//HttpHeaderCrossOriginEmbedderPolicy
HttpHeaderCrossOriginEmbedderPolicy _HttpHeader::getCrossOriginEmbedderPolicy() {
    return mCrossOriginEmbedderPolicy;
}

void _HttpHeader::setCrossOriginEmbedderPolicy(HttpHeaderCrossOriginEmbedderPolicy s) {
    mCrossOriginEmbedderPolicy = s;
}

HttpHeaderCrossOriginOpenerPolicy _HttpHeader::getCrossOriginOpenerPolicy() {
    return mCrossOriginOpenerPolicy;
}

void _HttpHeader::setCrossOriginOpenerPolicy(HttpHeaderCrossOriginOpenerPolicy s) {
    mCrossOriginOpenerPolicy = s;
}

HttpHeaderCrossOriginResourcePolicy _HttpHeader::getCrossOriginResourcePolicy() {
    return mCrossOriginResourcePolicy;
}

void _HttpHeader::setCrossOriginResourcePolicy(HttpHeaderCrossOriginResourcePolicy s) {
    mCrossOriginResourcePolicy = s;
}

HttpHeaderDate _HttpHeader::getDate() {
    return mDate;
}

void _HttpHeader::setData(HttpHeaderDate s) {
    mDate = s;
}

HttpHeaderExpect _HttpHeader::getExpect() {
    return mExpect;
}

void _HttpHeader::setExpect(HttpHeaderExpect s) {
    mExpect = s;
}

HttpHeaderExpectCT _HttpHeader::getExpectCT() {
    return mExpectCT;
}

void _HttpHeader::setExpectCT(HttpHeaderExpectCT s) {
    mExpectCT = s;
}

HttpHeaderExpires _HttpHeader::getExpires() {
    return mExpires;
}

void _HttpHeader::setExpires(HttpHeaderExpires s) {
    mExpires = s;
}

HttpHeaderFrom _HttpHeader::getFrom() {
    return mFrom;
}

void _HttpHeader::setFrom(HttpHeaderFrom s) {
    mFrom = s;
}

HttpHeaderRange _HttpHeader::getRange() {
    return mRange;
}

void _HttpHeader::setRange(HttpHeaderRange s) {
    mRange = s;
}

HttpHeaderReferer _HttpHeader::getReferer() {
    return mReferer;
}

void _HttpHeader::setReferer(HttpHeaderReferer s) {
    mReferer = s;
}

HttpHeaderReferrerPolicy _HttpHeader::getRefererPolicy() {
    return mRefererPolicy;
}

void _HttpHeader::setRefererPolicy(HttpHeaderReferrerPolicy s) {
    mRefererPolicy = s;
}

HttpHeaderVary _HttpHeader::getVary() {
    return mVary;
}

void _HttpHeader::setVary(HttpHeaderVary s) {
    mVary = s;
}

HttpHeaderVia _HttpHeader::getVia() {
    return mVia;
}

void _HttpHeader::setVia(HttpHeaderVia s) {
    mVia = s;
}

HttpHeaderServer _HttpHeader::getServer() {
    return mHeaderServer;
}

void _HttpHeader::setServer(HttpHeaderServer s) {
    mHeaderServer = s;
}

HttpHeaderWarning _HttpHeader::getWarning() {
    return mWarning;
}

void _HttpHeader::setWarning(HttpHeaderWarning s) {
    mWarning = s;
}

HttpHeaderAcceptCh _HttpHeader::getAcceptCh() {
    return mAcceptCh;
}

void _HttpHeader::setAcceptCh(HttpHeaderAcceptCh s) {
    mAcceptCh = s;
}

HttpHeaderDnt _HttpHeader::getDnt() {
    return mDnt;
}

void _HttpHeader::setDnt(HttpHeaderDnt s) {
    mDnt = s;
}

HttpHeaderSaveData _HttpHeader::getSaveData() {
    return mSaveData;
}

void _HttpHeader::setSaveData(HttpHeaderSaveData s) {
    mSaveData = s;
}

HttpHeaderSecFetchDest _HttpHeader::getSecFetchDest() {
    return mFetchDest;
}

void _HttpHeader::setSecFetchData(HttpHeaderSecFetchDest s) {
    mFetchDest = s;
}

HttpHeaderSecFetchMode _HttpHeader::getSecFetchMode() {
    return mFetchMode;
}

void _HttpHeader::setSecFetchMode(HttpHeaderSecFetchMode s) {
    mFetchMode = s;
}

HttpHeaderSecFetchSite _HttpHeader::getSecFetchSite() {
    return mFetchSite;
}

void _HttpHeader::setSecFetchSite(HttpHeaderSecFetchSite s) {
    mFetchSite = s;
}

HttpHeaderSecFetchUser _HttpHeader::getSecFetchUser() {
    return mFetchUser;
}

void _HttpHeader::setSecFetchUser(HttpHeaderSecFetchUser s) {
    mFetchUser = s;
}

HttpHeaderSourceMap _HttpHeader::getSourceMap() {
    return mSourceMap;
}

void _HttpHeader::setSourceMap(HttpHeaderSourceMap s) {
    mSourceMap = s;
}

//
HttpHeaderTransferEncoding _HttpHeader::getTransferEncoding() {
    return mTransferEncoding;
}

ListIterator<Pair<String,String>> _HttpHeader::getIterator() {
    //try to get all data
    //HashMap<String,String> values = createHashMap<String,String>();
    ArrayList<Pair<String,String>> values = createArrayList<Pair<String,String>>();

#define SET_HEAD_VALUE(X,Y) \
    values->add(createPair<String,String>(X,Y))

    //pseudo header field should set before regular
    if(mProtocol == st(NetProtocol)::Http_H2 
    || mProtocol == st(NetProtocol)::Http_H2C) {
        if(mType == Type::Response) {
            SET_HEAD_VALUE(st(HttpHeader)::Status,createString(mResponseStatus));
        }
    }

    if(mAcceptCharSet != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::AcceptCharset,mAcceptCharSet->toString());
    }

    if(mAccept != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::Accept,mAccept->toString());
    }

    if(mAcceptCh != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::AcceptCh,mAcceptCh->toString());
    }

    if(mAcceptEncoding != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::AcceptEncoding,mAcceptEncoding->toString());
    }

    if(mAcceptLanguage != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::AcceptLanguage,mAcceptLanguage->toString());
    }

    if(mAcceptPatch != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::AcceptPatch,mAcceptPatch->toString());
    }

    if(mAllowCredentials != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::AccessControlAllowCredentials,mAllowCredentials->toString());
    }

    if(mAllowHeaders != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::AccessControlAllowHeaders,mAllowHeaders->toString());
    }

    if(mAllowMethods != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::AccessControlAllowMethods,mAllowMethods->toString());
    }

    if(mAllowOrigin != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::AccessControlAllowOrigin,mAllowOrigin->toString());
    }

    if(mExposeHeaders != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::AccessControlExposeHeaders,mExposeHeaders->toString());
    }

    if(mMaxAge != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::AccessControlMaxAge,mMaxAge->toString());
    }

    if(mRequestHeaders != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::AccessControlRequestHeaders,mRequestHeaders->toString());
    }

    if(mRequestMethod != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::AccessControlRequestMethod,mRequestMethod->toString());
    }

    if(mAge != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::Age,mAge->toString());           
    }

    if(mAllow != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::Allow,mAllow->toString());  
    }

    if(mAuthorization != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::Authorization,mAuthorization->toString());  
    }

    if(mCacheControl != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::CacheControl,mCacheControl->toString(mType));
    }

    //TODO
    //if(mClearSiteData != nullptr) {
    //    header = header->append(st(HttpHeader)::Clear,": ",mClearSiteData->toString(),st(HttpText)::CRLF);
    //}

    if(mContentDisposition != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::ContentDisposition,mContentDisposition->toString());
    }
    
    if(mContentEncoding != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::ContentEncoding,mContentEncoding->toString());
    }

    if(mTransferEncoding != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::TransferEncoding,mTransferEncoding->toString());
    }
    
    if(mContentLanguage != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::ContentLanguage,mContentLanguage->toString());
    }

    if(mContentLength != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::ContentLength,mContentLength->toString());
    }

    if(mContentLocation != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::ContentLocation,mContentLocation->toString());
    }

    if(mContentType != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::ContentType,mContentType->toString());
    }

    if(mForwarded != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::Forwarded,mForwarded->toString());
    }

    if(mConnection != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::Connection,mConnection->toString());
    }

    if(mHeaderDigest != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::Digest,mHeaderDigest->toString());  
    }

    if(mHost != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::Host,mHost->toString());
    }

    if(mKeepAlive != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::KeepAlive,mKeepAlive->toString());
    }

    if(mIfMatch != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::IfMatch,mIfMatch->toString());
    }

    if(mIfNoneMatch != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::IfNoneMatch,mIfNoneMatch->toString());
    }

    if(mRetryAfter != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::RetryAfter,mRetryAfter->toString());
    }

    if(mUserAgent != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::UserAgent,mUserAgent->toString());
    }

    if(mIfModifiedSince != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::IfModifiedSince,mIfModifiedSince->toString());
    }

    if(mIfRange != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::IfRange,mIfRange->toString());
    }

    if(mIfUnmodifiedSince != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::IfUnmodifiedSince,mIfUnmodifiedSince->toString());
    }

    if(mProxyAuthenticate != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::ProxyAuthenticate,mProxyAuthenticate->toString());
    }

    if(mProxyAuthorization != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::ProxyAuthorization,mProxyAuthorization->toString());
    }

    if(mTransportSecurity != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::StrictTransportSecurity,mTransportSecurity->toString());
    }

    if(mXFrameOptions != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::XFrameOptions,mXFrameOptions->toString());
    }

    if(mUpgrade != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::Upgrade,mUpgrade->toString());    
    }

    /*
    TODO!!!!
    if(mLinks != nullptr && mLinks->size() != 0) {
        auto linkIterator = mLinks->getIterator();
        while(linkIterator->hasValue()) {
            header->append(st(HttpHeader)::Link,": ",linkIterator->getValue()->toString(),st(HttpText)::CRLF);
            linkIterator->next();
        }
    }*/

    if(mWebSocketAccept != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::SecWebSocketAccept,mWebSocketAccept->toString());  
    }

    if(mWebSocketKey != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::SecWebSocketKey,mWebSocketKey->toString());
    }

    if(mWebSocketProtocol != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::SecWebSocketProtocol,mWebSocketProtocol->toString());
    }

    if(mWebSocketKey1 != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::SecWebSocketKey1,mWebSocketKey1->toString());
    }

    if(mWebSocketKey2 != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::SecWebSocketKey2,mWebSocketKey2->toString());
    }

    if(mWebSocketKey3 != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::SecWebSocketKey3,mWebSocketKey3->toString());
    }

    if(mWebSocketVersion != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::SecWebSocketVersion,mWebSocketVersion->toString());
    }

    if(mWebSocketExtensions != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::SecWebSocketExtensions,mWebSocketExtensions->toString());
    }

    if(mWebSocketOrigin != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::SecWebSocketOrigin,mWebSocketOrigin->toString());
    }

    if(mOrigin != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::Origin,mOrigin->toString());
    }

    if(mPragma != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::Pragma,mPragma->toString());
    }

    if(mAcceptRanges != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::AcceptRanges,mAcceptRanges->toString());
    }

    if(mAltSvc != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::AltSvc,mAltSvc->toString());
    }

    if(mContentRange != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::ContentRange,mContentRange->toString());
    }

    if(mSecurityPolicy != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::ContentSecurityPolicy,mSecurityPolicy->toString());
    }

    if(mSecurityPolicyReportOnly != nullptr) {
        SET_HEAD_VALUE(st(HttpHeader)::ContentSecurityPolicyReportOnly,mSecurityPolicyReportOnly->toString());
    }

    //values->append(mValues);
    MapIterator<String,String> mapIterator = mValues->getIterator();
    while(mapIterator->hasValue()) {
        SET_HEAD_VALUE(mapIterator->getKey(),mapIterator->getValue());
        mapIterator->next();
    }
#undef SET_HEAD_VALUE

    return values->getIterator();
}

int _HttpHeader::findId(String s) {
    Integer v = idMaps->get(s->toLowerCase());
    if(v != nullptr) {
        return v->toValue();
    }

    return -1;
}

String _HttpHeader::findString(int id) {
    return names->get(id);
}

String _HttpHeader::toString(int type) {
    //create method method.......
    StringBuffer header = createStringBuffer();

    switch(type) {
        case st(HttpPacket)::Request: {
            header->append(st(HttpMethod)::toString(mMethod),st(HttpText)::ContentSpace);
            if (mUrl != nullptr) {
                header->append(createString("/")->append(mUrl->getPath()));
            } else {
                header->append(createString("/"));
            }
            header->append(st(HttpText)::ContentSpace,mVersion->toString(),st(HttpText)::CRLF);
            break;
        }

        case st(HttpPacket)::Response: {
            header->append(mVersion->toString(),st(HttpText)::ContentSpace,createString(mResponseStatus));
            if (mResponseReason != nullptr) {
                header->append(st(HttpText)::ContentSpace,mResponseReason,st(HttpText)::CRLF);
            } else {
                header->append(st(HttpText)::ContentSpace,st(HttpStatus)::toString(mResponseStatus),st(HttpText)::CRLF);
            }
            break;
        }

        default:
            Trigger(IllegalArgumentException,"no support");
        break;
    }
    
    // conver header
    //MapIterator<String, String> headerIte = getIterator();
    ListIterator<Pair<String,String>> headerIte = getIterator();

    while (headerIte->hasValue()) {
        Pair<String,String> pair = headerIte->getValue();
        String headString = pair->getKey();
        if (headString != nullptr && !headString->equalsIgnoreCase(Status)) {
            header->append(headString, ": ", pair->getValue(),
                                st(HttpText)::CRLF);
        }

        headerIte->next();
    }

    ListIterator<HttpCookie> iterator = mCookies->getIterator();
    while (iterator->hasValue()) {
        HttpCookie cookie = iterator->getValue();
        switch(type) {
            case st(HttpPacket)::Request:
            header->append(st(HttpHeader)::Cookie,cookie->toString(type), st(HttpText)::CRLF);
            break;

            case st(HttpPacket)::Response:
            header->append(st(HttpHeader)::SetCookie,cookie->toString(type), st(HttpText)::CRLF);
            break;
        }
        
        iterator->next();
    }

    //Link
    if(mLinks != nullptr && mLinks->size() != 0) {
        auto linkIterator = mLinks->getIterator();
        while(linkIterator->hasValue()) {
            header->append(st(HttpHeader)::Link,": ",linkIterator->getValue()->toString(),st(HttpText)::CRLF);
            linkIterator->next();
        }
    }

    if (header->size() == 0) {
        return nullptr;
    }

    return header->toString(0, header->size() - 2);
}

} // namespace obotcha
