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
const String _HttpHeader::ClearSiteData = createString("clear-site-data");
const String _HttpHeader::Version = createString("#version");

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
            idMaps->put(ClearSiteData,createInteger(TypeClearSiteData));
            idMaps->put(Version,createInteger(TypeVersion));

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
            names->add(ClearSiteData);
            names->add(Version);
        });
    }
    
    mProtocol = protocol;
    mValues = createHashMap<String, String>();
    mCookies = createArrayList<HttpCookie>();
    mHeaderValues = createHashMap<int,Object>();
    reset();
}

void _HttpHeader::addHttpHeader(sp<_HttpHeader> h) {
    ForEveryOne(pairCookie,h->mCookies) {
        mCookies->add(pairCookie);
    }

    ForEveryOne(pair,h->mHeaderValues) {
        if(pair->getKey() == TypeLink) {
            auto links = Cast<ArrayList<HttpHeaderLink>>(pair->getValue());
            if(links != nullptr) {
                links = createArrayList<HttpHeaderLink>();
                setLinks(links);
            }
            links->add(h->getLinks());
            continue;
        }

        mHeaderValues->put(pair->getKey(),pair->getValue());
    }
}

void _HttpHeader::reset() { 
    mValues->clear(); 
    mCookies->clear();
    mHeaderValues->clear();
    
    setVersion(createHttpHeaderVersion());
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
                setAuthority(value);
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
                auto v = createHttpHeaderAcceptCharSet();
                v->import(value);
                setAcceptCharSet(v);
                return;
            }

            case TypeAcceptCh: {
                auto v = createHttpHeaderAcceptCh();
                v->import(value);
                setAcceptCh(v);
                return;
            }

            case TypeAccept:{
                auto v = createHttpHeaderAccept();
                v->import(value);
                setAccept(v);
                return;
            }

            case TypeAcceptEncoding:{
                auto v = createHttpHeaderAcceptEncoding();
                v->import(value);
                setAcceptEncoding(v);
                return;
            }

            case TypeAcceptLanguage: {
                auto v = createHttpHeaderAcceptLanguage();
                v->import(value);
                setAcceptLanguage(v);
                return;
            }

            case TypeTransferEncoding: {
                auto v = createHttpHeaderTransferEncoding();
                v->import(value);
                setTransferEncoding(v);
                return;
            }

            case TypeAcceptPatch: {
                auto v = createHttpHeaderAcceptPatch();
                v->import(value);
                setAcceptPatch(v);
                return;
            }

            case TypeAccessControlAllowCredentials: {
                auto v = createHttpHeaderAccessControlAllowCredentials();
                v->import(value);
                setAllowCredentials(v);
                return;
            }

            case TypeAccessControlAllowHeaders: {
                auto v = createHttpHeaderAccessControlAllowHeaders();
                v->import(value);
                setAllowHeaders(v);
                return;
            }

            case TypeAccessControlAllowMethods: {
                auto v = createHttpHeaderAccessControlAllowMethods();
                v->import(value);
                setAllowMethods(v);
                return;
            }

            case TypeAccessControlAllowOrigin: {
                auto v = createHttpHeaderAccessControlAllowOrigin();
                v->import(value);
                setAllowOrigin(v);
                return;
            }

            case TypeAccessControlExposeHeaders: {
                auto v = createHttpHeaderAccessControlExposeHeaders();
                v->import(value);
                setExposeHeaders(v);
                return;
            }
            
            case TypeAccessControlMaxAge: {
                auto v = createHttpHeaderAccessControlMaxAge();
                v->import(value);
                setMaxAge(v);
                return;
            }

            case TypeAccessControlRequestHeaders: {
                auto v = createHttpHeaderAccessControlRequestHeaders();
                v->import(value);
                setReqeuestHeaders(v);
                return;
            }

            case TypeAccessControlRequestMethod: {
                auto v = createHttpHeaderAccessControlRequestMethod();
                v->import(value);
                setRequestMethod(v);
                return;
            }

            case TypeAge: {
                auto v = createHttpHeaderAge();
                v->import(value);
                setAge(v);
                return;
            }

            case TypeAllow: {
                auto v = createHttpHeaderAllow();
                v->import(value);
                setAllow(v);
                return;
            }

            case TypeAuthorization: {
                auto v= createHttpHeaderAuthorization();
                v->import(value);
                setAuthorization(v);
                return;
            }
            
            case TypeCacheControl: {
                auto v = createHttpHeaderCacheControl();
                v->import(value);
                setCacheControl(v);
                return;
            }

            case TypeClearSiteData: {
                auto v = createHttpHeaderClearSiteData();
                v->import(value);
                setClearSiteData(v);
                return;
            }

            case TypeContentDisposition: {
                auto v = createHttpHeaderContentDisposition();
                v->import(value);
                setContentDisposition(v);
                return;
            }

            case TypeContentEncoding: {
                auto v = createHttpHeaderContentEncoding();
                v->import(value);
                setContentEncoding(v);
                return;
            }

            case TypeContentLanguage: {
                auto v = createHttpHeaderContentLanguage();
                v->import(value);
                setContentLanguage(v);
                return;
            }

            case TypeContentLength: {
                auto v = createHttpHeaderContentLength();
                v->import(value);
                setContentLength(v);
                return;
            }

            case TypeContentLocation: {
                auto v = createHttpHeaderContentLocation();
                v->import(value);
                setContentLocation(v);
                return;
            }

            case TypeContentType: {
                auto v = createHttpHeaderContentType();
                v->import(value);
                setContentType(v);
                return;
            }

            case TypeForwarded: {
                auto v = createHttpHeaderForwarded();
                v->import(value);
                setForwarded(v);
                return;
            }

            case TypeConnection: {
                auto v = createHttpHeaderConnection();
                v->import(value);
                setConnection(v);
                return;
            }

            case TypeDigest: {
                auto v = createHttpHeaderDigest();
                v->import(value);
                setDigest(v);
                return;
            }

            case TypeHost: {
                auto v = createHttpHeaderHost();
                v->import(value);
                setHost(v);
                return;
            }

            case TypeKeepAlive: {
                auto v = createHttpHeaderKeepAlive();
                v->import(value);
                setKeepAlive(v);
                return;
            }

            case TypeLink: {
                auto v = createHttpHeaderLink(value);
                addLink(v);
                return;
            }

            case TypeIfMatch: {
                auto v = createHttpHeaderMatch();
                v->import(value);
                setIfMatch(v);
                return;
            }

            case TypeIfNoneMatch: {
                auto v = createHttpHeaderMatch();
                v->import(value);
                setIfNoneMatch(v);
                return;
            }

            case TypeRetryAfter: {
                auto v = createHttpHeaderRetryAfter();
                v->import(value);
                setRetryAfter(v);
                return;
            }

            case TypeUserAgent: {
                auto v = createHttpHeaderUserAgent();
                v->import(value);
                setUserAgent(v);
                return;
            }
            
            case TypeIfModifiedSince: {
                auto v = createHttpHeaderIfModifiedSince();
                v->import(value);
                setIfModifiedSince(v);
                return;
            }

            case TypeIfRange: {
                auto v = createHttpHeaderIfRange();
                v->import(value);
                setIfRange(v);
                return;
            }

            case TypeIfUnmodifiedSince: {
                auto v = createHttpHeaderIfUnmodifiedSince();
                v->import(value);
                setIfUnmodifiedSince(v);
                return;
            }

            case TypeProxyAuthenticate: {
                auto v = createHttpHeaderProxyAuthenticate();
                v->import(value);
                setProxyAuthenticate(v);
                return;
            }

            case TypeProxyAuthorization: {
                auto v = createHttpHeaderProxyAuthorization();
                v->import(value);
                setProxyAuthorization(v);
                return;
            }
            
            case TypeStrictTransportSecurity: {
                auto v = createHttpHeaderStrictTransportSecurity();
                v->import(value);
                setStrictTransportSecurity(v);
                return;
            }

            case TypeXFrameOptions: {
                auto v = createHttpHeaderXFrameOptions();
                v->import(value);
                setXFrameOptions(v);
                return;
            }

            case TypeUpgrade: {
                auto v = createHttpHeaderUpgrade();
                v->import(value);
                setUpgrade(v);
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
                auto v = createHttpHeaderSecWebSocketAccept();
                v->import(value);
                setWebSocketAccept(v);
                return;
            }

            case TypeSecWebSocketKey: {
                auto v = createHttpHeaderSecWebSocketKey();
                v->import(value);
                setWebSocketKey(v);
                return;
            }

            case TypeSecWebSocketVersion: {
                auto v = createHttpHeaderSecWebSocketVersion();
                v->import(value);
                setWebSocketVersion(v);
                return;
            }

            case TypeSecWebSocketExtensions: {
                auto v = createHttpHeaderSecWebSocketExtensions();
                v->import(value);
                setWebSocketExtensions(v);
                return;
            }

            case TypeSecWebSocketOrigin: {
                auto v = createHttpHeaderSecWebSocketOrigin();
                v->import(value);
                setWebSocketOrigin(v);
                return;
            }

            case TypeSecWebSocketKey1: {
                auto v = createHttpHeaderSecWebSocketKey();
                v->import(value);
                setWebSocketKey1(v);
                return;
            }

            case TypeSecWebSocketKey2: {
                auto v = createHttpHeaderSecWebSocketKey();
                v->import(value);
                setWebSocketKey2(v);
                return;
            }

            case TypeSecWebSocketKey3: {
                auto v = createHttpHeaderSecWebSocketKey();
                v->import(value);
                setWebSocketKey3(v);;
                return;
            }

            case TypeSecWebSocketProtocol: {
                auto v = createHttpHeaderSecWebSocketProtocol();
                v->import(value);
                setWebSocketProtocol(v);
                return;
            }

            case TypeOrigin: {
                auto v = createHttpHeaderOrigin();
                v->import(value);
                setOrigin(v);
                return;
            }

            case TypePragma: {
                auto v = createHttpHeaderPragma();
                v->import(value);
                setPragma(v);
                return;
            }

            case TypeAcceptRanges: {
                auto v = createHttpHeaderAcceptRanges();
                v->import(value);
                setHttpHeaderAcceptRanges(v);
                return;
            }

            case TypeAltSvc: {
                auto v = createHttpHeaderAltSvc();
                v->import(value);
                setAltSvc(v);
                return;
            }

            case TypeContentRange: {
                auto v = createHttpHeaderContentRange();
                v->import(value);
                setContentRange(v);
                return;
            }

            case TypeContentSecurityPolicy: {
                auto v = createHttpHeaderContentSecurityPolicy();
                v->import(value);
                setSecurityPolicy(v);
                return;
            }

            case TypeContentSecurityPolicyReportOnly: {
                auto v = createHttpHeaderContentSecurityPolicy();
                v->import(value);
                setSecurityPolicyReportOnly(v);
                return;
            }

            case TypeCrossOriginEmbedderPolicy: {
                auto v = createHttpHeaderCrossOriginEmbedderPolicy();
                v->import(value);
                setCrossOriginEmbedderPolicy(v);
                return;
            }

            case TypeCrossOriginOpenerPolicy: {
                auto v = createHttpHeaderCrossOriginOpenerPolicy();
                v->import(value);
                setCrossOriginOpenerPolicy(v);
                return;
            }

            case TypeCrossOriginResourcePolicy: {
                auto v = createHttpHeaderCrossOriginResourcePolicy();
                v->import(value);
                setCrossOriginResourcePolicy(v);
                return;
            }

            case TypeDate: {
                auto v = createHttpHeaderDate();
                v->import(value);
                setDate(v);
                return;
            }

            case TypeExpect: {
                auto v = createHttpHeaderExpect();
                v->import(value);
                setExpect(v);
                return;
            }

            case TypeExpectCT: {
                auto v = createHttpHeaderExpectCT();
                v->import(value);
                setExpectCT(v);
                return;
            }

            case TypeExpires: {
                auto v = createHttpHeaderExpires();
                v->import(value);
                setExpires(v);
                return;
            }

            case TypeFrom: {
                auto v = createHttpHeaderFrom();
                v->import(value);
                setFrom(v);
                return;
            }

            case TypeRange: {
                auto v = createHttpHeaderRange();
                v->import(value);
                setRange(v);
                return;
            }

            case TypeReferer: {
                auto v = createHttpHeaderReferer();
                v->import(value);
                setReferer(v);
                return;
            }

            case TypeRefererPolicy: {
                auto v = createHttpHeaderReferrerPolicy();
                v->import(value);
                setRefererPolicy(v);
                return;
            }

            case TypeVary: {
                auto v = createHttpHeaderVary();
                v->import(value);
                setVary(v);
                return;
            }

            case TypeVia: {
                auto v = createHttpHeaderVia();
                v->import(value);
                setVia(v);
                return;
            }

            case TypeServer: {
                auto v = createHttpHeaderServer();
                v->import(value);
                setServer(v);
                return;
            }

            case TypeWarning: {
                auto v = createHttpHeaderWarning();
                v->import(value);
                setWarning(v);
                return;
            }

            case TypeDNT: {
                auto v = createHttpHeaderDnt();
                v->import(value);
                setDnt(v);
                return;
            }

            case TypeSaveData: {
                auto v = createHttpHeaderSaveData();
                v->import(value);
                setSaveData(v);
                return;
            }

            case TypeSecFetchDest: {
                auto v = createHttpHeaderSecFetchDest();
                v->import(value);
                setSecFetchDest(v);
                return;
            }

            case TypeSecFetchMode: {
                auto v = createHttpHeaderSecFetchMode();
                v->import(value);
                setSecFetchMode(v);
                return;
            }

            case TypeSecFetchSite: {
                auto v = createHttpHeaderSecFetchSite();
                v->import(value);
                setSecFetchSite(v);
                return;
            }

            case TypeSecFetchUser: {
                auto v = createHttpHeaderSecFetchUser();
                v->import(value);
                setSecFetchUser(v);
                return;
            }

            case TypeServerTiming: {
                auto v = createHttpHeaderServerTiming();
                v->import(value);
                setServerTiming(v);
                return;
            }

            case TypeSourceMap: {
                auto v = createHttpHeaderSourceMap();
                v->import(value);
                setSourceMap(v);
                return;
            }
        }
    }

    mValues->put(key->toLowerCase(), value);
}

String _HttpHeader::get(String header) {
    Integer id = idMaps->get(header->toLowerCase());
    if(id != nullptr) {
        auto headerValue = mHeaderValues->get(id->toValue());
        if(headerValue != nullptr) {
            return headerValue->toString();
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

//Authority
String _HttpHeader::getAuthority() {
    return Cast<String>(mHeaderValues->get(TypeAuthority));
}

void _HttpHeader::setAuthority(String s) {
    mHeaderValues->put(TypeAuthority,s);
}

//HttpHeaderAcceptCharSet
HttpHeaderAcceptCharSet _HttpHeader::getAcceptCharSet() {
    return Cast<HttpHeaderAcceptCharSet>(mHeaderValues->get(TypeAcceptCharset));
}

void _HttpHeader::setAcceptCharSet(HttpHeaderAcceptCharSet v) {
    mHeaderValues->put(TypeAcceptCharset,v);
}

HttpHeaderAccept _HttpHeader::getAccept() {
    return Cast<HttpHeaderAccept>(mHeaderValues->get(TypeAccept));
}

void _HttpHeader::setAccept(HttpHeaderAccept s) {
    mHeaderValues->put(TypeAccept,s);
}

HttpHeaderAcceptEncoding _HttpHeader::getAcceptEncoding() {
    return Cast<HttpHeaderAcceptEncoding>(mHeaderValues->get(TypeAcceptEncoding));
}

void _HttpHeader::setAcceptEncoding(HttpHeaderAcceptEncoding s) {
    mHeaderValues->put(TypeAcceptEncoding,s);
}

HttpHeaderAcceptLanguage _HttpHeader::getAcceptLanguage() {
    return Cast<HttpHeaderAcceptLanguage>(mHeaderValues->get(TypeAcceptLanguage));
}

void _HttpHeader::setAcceptLanguage(HttpHeaderAcceptLanguage s) {
    mHeaderValues->put(TypeAcceptLanguage,s);
}

HttpHeaderAcceptPatch _HttpHeader::getAcceptPatch() {
    return Cast<HttpHeaderAcceptPatch>(mHeaderValues->get(TypeAcceptPatch));
}

void _HttpHeader::setAcceptPatch(HttpHeaderAcceptPatch s) {
    mHeaderValues->put(TypeAcceptPatch,s);
}

HttpHeaderAccessControlAllowCredentials _HttpHeader::getAllowCredentials() {
    return Cast<HttpHeaderAccessControlAllowCredentials>(mHeaderValues->get(TypeAccessControlAllowCredentials));
}

void _HttpHeader::setAllowCredentials(HttpHeaderAccessControlAllowCredentials s) {
    mHeaderValues->put(TypeAccessControlAllowCredentials,s);
}

HttpHeaderAccessControlAllowHeaders _HttpHeader::getAllowHeaders() {
    return Cast<HttpHeaderAccessControlAllowHeaders>(mHeaderValues->get(TypeAccessControlAllowHeaders));
}

void _HttpHeader::setAllowHeaders(HttpHeaderAccessControlAllowHeaders s) {
    mHeaderValues->put(TypeAccessControlAllowHeaders,s);
}

HttpHeaderAccessControlAllowMethods _HttpHeader::getAllowMethods() {
    return Cast<HttpHeaderAccessControlAllowMethods>(mHeaderValues->get(TypeAccessControlAllowMethods));
}

void _HttpHeader::setAllowMethods(HttpHeaderAccessControlAllowMethods s) {
    mHeaderValues->put(TypeAccessControlAllowMethods,s);
}

//HttpHeaderAccessControlAllowOrigin
HttpHeaderAccessControlAllowOrigin _HttpHeader::getAllowOrigin() {
    return Cast<HttpHeaderAccessControlAllowOrigin>(mHeaderValues->get(TypeAccessControlAllowOrigin));
}

void _HttpHeader::setAllowOrigin(HttpHeaderAccessControlAllowOrigin s) {
    mHeaderValues->put(TypeAccessControlAllowOrigin,s);
}

HttpHeaderAccessControlExposeHeaders _HttpHeader::getExposeHeaders() {
    return Cast<HttpHeaderAccessControlExposeHeaders>(mHeaderValues->get(TypeAccessControlExposeHeaders));
}

void _HttpHeader::setExposeHeaders(HttpHeaderAccessControlExposeHeaders s) {
    mHeaderValues->put(TypeAccessControlExposeHeaders,s);
}

HttpHeaderAccessControlMaxAge _HttpHeader::getMaxAge() {
    return Cast<HttpHeaderAccessControlMaxAge>(mHeaderValues->get(TypeAccessControlMaxAge));
}

void _HttpHeader::setMaxAge(HttpHeaderAccessControlMaxAge s) {
    mHeaderValues->put(TypeAccessControlMaxAge,s);
}

HttpHeaderAccessControlRequestHeaders _HttpHeader::getRequestHeaders() {
    return Cast<HttpHeaderAccessControlRequestHeaders>(mHeaderValues->get(TypeAccessControlRequestHeaders));
}

void _HttpHeader::setReqeuestHeaders(HttpHeaderAccessControlRequestHeaders s) {
    mHeaderValues->put(TypeAccessControlRequestHeaders,s);
}

HttpHeaderAccessControlRequestMethod _HttpHeader::getRequestMethod() {
    return Cast<HttpHeaderAccessControlRequestMethod>(mHeaderValues->get(TypeAccessControlRequestMethod));
}

void _HttpHeader::setRequestMethod(HttpHeaderAccessControlRequestMethod s) {
    mHeaderValues->put(TypeAccessControlRequestMethod,s);
}

HttpHeaderAge _HttpHeader::getAge() {
    return Cast<HttpHeaderAge>(mHeaderValues->get(TypeAge));
}

void _HttpHeader::setAge(HttpHeaderAge s) {
    mHeaderValues->put(TypeAge,s);
}

HttpHeaderAllow _HttpHeader::getAllow() {
    return Cast<HttpHeaderAllow>(mHeaderValues->get(TypeAllow));
}

void _HttpHeader::setAllow(HttpHeaderAllow s) {
    mHeaderValues->put(TypeAllow,s);
}

HttpHeaderAuthorization _HttpHeader::getAuthorization() {
    return Cast<HttpHeaderAuthorization>(mHeaderValues->get(TypeAuthorization));
}

void _HttpHeader::setAuthorization(HttpHeaderAuthorization s) {
    mHeaderValues->put(TypeAuthorization,s);
}

HttpHeaderCacheControl _HttpHeader::getCacheControl() {
    return Cast<HttpHeaderCacheControl>(mHeaderValues->get(TypeCacheControl));
}

void _HttpHeader::setCacheControl(HttpHeaderCacheControl s) {
    mHeaderValues->put(TypeCacheControl,s);
}

HttpHeaderClearSiteData _HttpHeader::getClearSiteData() {
    return Cast<HttpHeaderClearSiteData>(mHeaderValues->get(TypeClearSiteData));
}

void _HttpHeader::setClearSiteData(HttpHeaderClearSiteData s) {
    mHeaderValues->put(TypeClearSiteData,s);
}

HttpHeaderContentDisposition _HttpHeader::getContentDisposition() {
    return Cast<HttpHeaderContentDisposition>(mHeaderValues->get(TypeContentDisposition));
}

void _HttpHeader::setContentDisposition(HttpHeaderContentDisposition s) {
    mHeaderValues->put(TypeContentDisposition,s);
}

HttpHeaderContentEncoding _HttpHeader::getContentEncoding() {
    return Cast<HttpHeaderContentEncoding>(mHeaderValues->get(TypeContentEncoding));
}

void _HttpHeader::setContentEncoding(HttpHeaderContentEncoding s) {
    mHeaderValues->put(TypeContentEncoding,s);
}

HttpHeaderContentLanguage _HttpHeader::getContentLanguage() {
    return Cast<HttpHeaderContentLanguage>(mHeaderValues->get(TypeContentLanguage));
}

void _HttpHeader::setContentLanguage(HttpHeaderContentLanguage s) {
    mHeaderValues->put(TypeContentLanguage,s);
}

HttpHeaderContentLength _HttpHeader::getContentLength() {
    return Cast<HttpHeaderContentLength>(mHeaderValues->get(TypeContentLength));
}

void _HttpHeader::setContentLength(HttpHeaderContentLength s) {
    mHeaderValues->put(TypeContentLength,s);
}

HttpHeaderContentLocation _HttpHeader::getContentLocation() {
    return Cast<HttpHeaderContentLocation>(mHeaderValues->get(TypeContentLocation));
}

void _HttpHeader::setContentLocation(HttpHeaderContentLocation s) {
    mHeaderValues->put(TypeContentLocation,s);
}

HttpHeaderContentType _HttpHeader::getContentType() {
    return Cast<HttpHeaderContentType>(mHeaderValues->get(TypeContentType));
}

void _HttpHeader::setContentType(HttpHeaderContentType s) {
    mHeaderValues->put(TypeContentType,s);
}

HttpHeaderForwarded _HttpHeader::getForwarded() {
    return Cast<HttpHeaderForwarded>(mHeaderValues->get(TypeForwarded));
}

void _HttpHeader::setForwarded(HttpHeaderForwarded s) {
    mHeaderValues->put(TypeForwarded,s);
}

HttpHeaderConnection _HttpHeader::getConnection() {
    return Cast<HttpHeaderConnection>(mHeaderValues->get(TypeConnection));
}

void _HttpHeader::setConnection(HttpHeaderConnection s) {
    mHeaderValues->put(TypeConnection,s);
}

HttpHeaderDigest _HttpHeader::getDigest() {
    return Cast<HttpHeaderConnection>(mHeaderValues->get(TypeDigest));
}

void _HttpHeader::setDigest(HttpHeaderDigest s) {
    mHeaderValues->put(TypeDigest,s);
}

HttpHeaderHost _HttpHeader::getHost() {
    return Cast<HttpHeaderHost>(mHeaderValues->get(TypeHost));
}

void _HttpHeader::setHost(HttpHeaderHost s) {
    mHeaderValues->put(TypeHost,s);
}

HttpHeaderKeepAlive _HttpHeader::getKeepAlive() {
    return Cast<HttpHeaderKeepAlive>(mHeaderValues->get(TypeKeepAlive));
}

void _HttpHeader::setKeepAlive(HttpHeaderKeepAlive s) {
    mHeaderValues->put(TypeKeepAlive,s);
}

ArrayList<HttpHeaderLink> _HttpHeader::getLinks() {
    return Cast<ArrayList<HttpHeaderLink>>(mHeaderValues->get(TypeLink));
}

void _HttpHeader::setLinks(ArrayList<HttpHeaderLink> s) {
    mHeaderValues->put(TypeLink,s);
}

void _HttpHeader::addLink(HttpHeaderLink s) {
    auto links = getLinks();
    if(links == nullptr) {
        links = createArrayList<HttpHeaderLink>();
        setLinks(links);
    }

    links->add(s);
}

HttpHeaderMatch _HttpHeader::getIfMatch() {
    return Cast<HttpHeaderMatch>(mHeaderValues->get(TypeIfMatch));
}

void _HttpHeader::setIfMatch(HttpHeaderMatch s) {
    mHeaderValues->put(TypeIfMatch,s);
}

HttpHeaderMatch _HttpHeader::getIfNoneMatch() {
    return Cast<HttpHeaderMatch>(mHeaderValues->get(TypeIfNoneMatch));
}

void _HttpHeader::setIfNoneMatch(HttpHeaderMatch s) {
    mHeaderValues->put(TypeIfNoneMatch,s);
}

HttpHeaderRetryAfter _HttpHeader::getRetryAfter() {
    return Cast<HttpHeaderRetryAfter>(mHeaderValues->get(TypeRetryAfter));
}

void _HttpHeader::setRetryAfter(HttpHeaderRetryAfter s) {
    mHeaderValues->put(TypeRetryAfter,s);
}

HttpHeaderUserAgent _HttpHeader::getUserAgent() {
    return Cast<HttpHeaderUserAgent>(mHeaderValues->get(TypeUserAgent));
}

void _HttpHeader::setUserAgent(HttpHeaderUserAgent s) {
    mHeaderValues->put(TypeUserAgent,s);
}

HttpHeaderIfModifiedSince _HttpHeader::getIfModifiedSince() {
    return Cast<HttpHeaderIfModifiedSince>(mHeaderValues->get(TypeIfModifiedSince));
}

void _HttpHeader::setIfModifiedSince(HttpHeaderIfModifiedSince s) {
    mHeaderValues->put(TypeIfModifiedSince,s);
}

HttpHeaderIfRange _HttpHeader::getIfRange() {
    return Cast<HttpHeaderIfRange>(mHeaderValues->get(TypeIfRange));
}

void _HttpHeader::setIfRange(HttpHeaderIfRange s) {
    mHeaderValues->put(TypeIfRange,s);
}

HttpHeaderIfUnmodifiedSince _HttpHeader::getIfUnmodifiedSince() {
    return Cast<HttpHeaderIfUnmodifiedSince>(mHeaderValues->get(TypeIfUnmodifiedSince));
}

void _HttpHeader::setIfUnmodifiedSince(HttpHeaderIfUnmodifiedSince s) {
    mHeaderValues->put(TypeIfUnmodifiedSince,s);
}

HttpHeaderProxyAuthenticate _HttpHeader::getProxyAuthenticate() {
    return Cast<HttpHeaderProxyAuthenticate>(mHeaderValues->get(TypeProxyAuthenticate));
}

void _HttpHeader::setProxyAuthenticate(HttpHeaderProxyAuthenticate s) {
    mHeaderValues->put(TypeProxyAuthenticate,s);
}

HttpHeaderProxyAuthorization _HttpHeader::getProxyAuthorization() {
    return Cast<HttpHeaderProxyAuthorization>(mHeaderValues->get(TypeProxyAuthorization));
}

void _HttpHeader::setProxyAuthorization(HttpHeaderProxyAuthorization s) {
    mHeaderValues->put(TypeProxyAuthorization,s);
}

HttpHeaderStrictTransportSecurity _HttpHeader::getStrictTransportSecurity() {
    return Cast<HttpHeaderStrictTransportSecurity>(mHeaderValues->get(TypeStrictTransportSecurity));
}

void _HttpHeader::setStrictTransportSecurity(HttpHeaderStrictTransportSecurity s) {
    mHeaderValues->put(TypeStrictTransportSecurity,s);
}

HttpHeaderVersion _HttpHeader::getVersion() {
    return Cast<HttpHeaderVersion>(mHeaderValues->get(TypeVersion));
}

void _HttpHeader::setVersion(HttpHeaderVersion s) {
    mHeaderValues->put(TypeVersion,s);
}

HttpHeaderXFrameOptions _HttpHeader::getXFrameOptions() {
    return Cast<HttpHeaderXFrameOptions>(mHeaderValues->get(TypeXFrameOptions));
}

void _HttpHeader::setXFrameOptions(HttpHeaderXFrameOptions s) {
    mHeaderValues->put(TypeXFrameOptions,s);
}

HttpHeaderTransferEncoding _HttpHeader::getTransferEncoding() {
    return Cast<HttpHeaderTransferEncoding>(mHeaderValues->get(TypeTransferEncoding));
}

void _HttpHeader::setTransferEncoding(HttpHeaderTransferEncoding s) {
    mHeaderValues->put(TypeTransferEncoding,s);
}

void _HttpHeader::setUpgrade(HttpHeaderUpgrade s) {
    mHeaderValues->put(TypeUpgrade,s);
}

HttpHeaderUpgrade _HttpHeader::getUpgrade() {
    return Cast<HttpHeaderUpgrade>(mHeaderValues->get(TypeUpgrade));
}

void _HttpHeader::setWebSocketAccept(HttpHeaderSecWebSocketAccept s) {
    mHeaderValues->put(TypeSecWebSocketAccept,s);
}

HttpHeaderSecWebSocketAccept _HttpHeader::getWebSocketAccept() {
    return Cast<HttpHeaderSecWebSocketAccept>(mHeaderValues->get(TypeSecWebSocketAccept));
}

void _HttpHeader::setWebSocketKey(HttpHeaderSecWebSocketKey s) {
    mHeaderValues->put(TypeSecWebSocketKey,s);
}

HttpHeaderSecWebSocketKey _HttpHeader::getWebSocketKey() {
    return Cast<HttpHeaderSecWebSocketKey>(mHeaderValues->get(TypeSecWebSocketKey));
}

void _HttpHeader::setWebSocketProtocol(HttpHeaderSecWebSocketProtocol s) {
    mHeaderValues->put(TypeSecWebSocketProtocol,s);
}

HttpHeaderSecWebSocketProtocol _HttpHeader::getWebSocketProtocol() {
    return Cast<HttpHeaderSecWebSocketProtocol>(mHeaderValues->get(TypeSecWebSocketProtocol));
}

void _HttpHeader::setWebSocketKey1(HttpHeaderSecWebSocketKey s) {
    mHeaderValues->put(TypeSecWebSocketKey1,s);
}

HttpHeaderSecWebSocketKey _HttpHeader::getWebSocketKey1() {
    return Cast<HttpHeaderSecWebSocketKey>(mHeaderValues->get(TypeSecWebSocketKey1));
}

void _HttpHeader::setWebSocketKey2(HttpHeaderSecWebSocketKey s) {
    mHeaderValues->put(TypeSecWebSocketKey2,s);
}

HttpHeaderSecWebSocketKey _HttpHeader::getWebSocketKey2() {
    return Cast<HttpHeaderSecWebSocketKey>(mHeaderValues->get(TypeSecWebSocketKey2));
}

void _HttpHeader::setWebSocketKey3(HttpHeaderSecWebSocketKey s) {
    mHeaderValues->put(TypeSecWebSocketKey3,s);
}

HttpHeaderSecWebSocketKey _HttpHeader::getWebSocketKey3() {
    return Cast<HttpHeaderSecWebSocketKey>(mHeaderValues->get(TypeSecWebSocketKey3));
}

void _HttpHeader::setWebSocketVersion(HttpHeaderSecWebSocketVersion s) {
    mHeaderValues->put(TypeSecWebSocketVersion,s);
}

HttpHeaderSecWebSocketVersion _HttpHeader::getWebSocketVersion() {
    return Cast<HttpHeaderSecWebSocketVersion>(mHeaderValues->get(TypeSecWebSocketVersion));
}

void _HttpHeader::setWebSocketExtensions(HttpHeaderSecWebSocketExtensions s) {
    mHeaderValues->put(TypeSecWebSocketExtensions,s);
}

HttpHeaderSecWebSocketExtensions _HttpHeader::getWebSocketExtensions() {
    return Cast<HttpHeaderSecWebSocketExtensions>(mHeaderValues->get(TypeSecWebSocketExtensions));
}

void _HttpHeader::setWebSocketOrigin(HttpHeaderSecWebSocketOrigin s) {
    mHeaderValues->put(TypeSecWebSocketOrigin,s);
}

HttpHeaderSecWebSocketOrigin _HttpHeader::getWebSocketOrigin() {
    return Cast<HttpHeaderSecWebSocketOrigin>(mHeaderValues->get(TypeSecWebSocketOrigin));
}

void _HttpHeader::setOrigin(HttpHeaderOrigin s) {
    mHeaderValues->put(TypeOrigin,s);
}

HttpHeaderOrigin _HttpHeader::getOrigin() {
    return Cast<HttpHeaderOrigin>(mHeaderValues->get(TypeOrigin));
}

void _HttpHeader::setPragma(HttpHeaderPragma s) {
    mHeaderValues->put(TypePragma,s);
}

HttpHeaderPragma _HttpHeader::getPragma() {
    return Cast<HttpHeaderPragma>(mHeaderValues->get(TypePragma));
}

void _HttpHeader::setHttpHeaderAcceptRanges(HttpHeaderAcceptRanges s) {
    mHeaderValues->put(TypeAcceptRanges,s);
}

HttpHeaderAcceptRanges _HttpHeader::getAcceptRanges() {
    return Cast<HttpHeaderAcceptRanges>(mHeaderValues->get(TypeAcceptRanges));
}

void _HttpHeader::setAltSvc(HttpHeaderAltSvc s) {
    mHeaderValues->put(TypeAltSvc,s);
}

HttpHeaderAltSvc _HttpHeader::getAltSvc() {
    return Cast<HttpHeaderAltSvc>(mHeaderValues->get(TypeAltSvc));
}

void _HttpHeader::setContentRange(HttpHeaderContentRange s) {
    mHeaderValues->put(TypeContentRange,s);
}

HttpHeaderContentRange _HttpHeader::getContentRange() {
    return Cast<HttpHeaderContentRange>(mHeaderValues->get(TypeContentRange));
}

void _HttpHeader::setSecurityPolicy(HttpHeaderContentSecurityPolicy s) {
    mHeaderValues->put(TypeContentSecurityPolicy,s);
}

HttpHeaderContentSecurityPolicy _HttpHeader::getSecurityPolicy() {
    return Cast<HttpHeaderContentSecurityPolicy>(mHeaderValues->get(TypeContentSecurityPolicy));
}

void _HttpHeader::setSecurityPolicyReportOnly(HttpHeaderContentSecurityPolicy s) {
    mHeaderValues->put(TypeContentSecurityPolicyReportOnly,s);
}

HttpHeaderContentSecurityPolicy _HttpHeader::getSecurityPolicyReportOnly() {
    return Cast<HttpHeaderContentSecurityPolicy>(mHeaderValues->get(TypeContentSecurityPolicyReportOnly));
}

HttpHeaderCrossOriginEmbedderPolicy _HttpHeader::getCrossOriginEmbedderPolicy() {
    return Cast<HttpHeaderCrossOriginEmbedderPolicy>(mHeaderValues->get(TypeCrossOriginEmbedderPolicy));
}

void _HttpHeader::setCrossOriginEmbedderPolicy(HttpHeaderCrossOriginEmbedderPolicy s) {
    mHeaderValues->put(TypeCrossOriginEmbedderPolicy,s);
}

HttpHeaderCrossOriginOpenerPolicy _HttpHeader::getCrossOriginOpenerPolicy() {
    return Cast<HttpHeaderCrossOriginOpenerPolicy>(mHeaderValues->get(TypeCrossOriginOpenerPolicy));
}

void _HttpHeader::setCrossOriginOpenerPolicy(HttpHeaderCrossOriginOpenerPolicy s) {
    mHeaderValues->put(TypeCrossOriginOpenerPolicy,s);
}

HttpHeaderCrossOriginResourcePolicy _HttpHeader::getCrossOriginResourcePolicy() {
    return Cast<HttpHeaderCrossOriginResourcePolicy>(mHeaderValues->get(TypeCrossOriginResourcePolicy));
}

void _HttpHeader::setCrossOriginResourcePolicy(HttpHeaderCrossOriginResourcePolicy s) {
    mHeaderValues->put(TypeCrossOriginResourcePolicy,s);
}

HttpHeaderDate _HttpHeader::getDate() {
    return Cast<HttpHeaderDate>(mHeaderValues->get(TypeDate));
}

void _HttpHeader::setDate(HttpHeaderDate s) {
    mHeaderValues->put(TypeDate,s);
}

HttpHeaderExpect _HttpHeader::getExpect() {
    return Cast<HttpHeaderExpect>(mHeaderValues->get(TypeExpect));
}

void _HttpHeader::setExpect(HttpHeaderExpect s) {
    mHeaderValues->put(TypeExpect,s);
}

HttpHeaderExpectCT _HttpHeader::getExpectCT() {
    return Cast<HttpHeaderExpectCT>(mHeaderValues->get(TypeExpectCT));
}

void _HttpHeader::setExpectCT(HttpHeaderExpectCT s) {
    mHeaderValues->put(TypeExpectCT,s);
}

HttpHeaderExpires _HttpHeader::getExpires() {
    return Cast<HttpHeaderExpires>(mHeaderValues->get(TypeExpires));
}

void _HttpHeader::setExpires(HttpHeaderExpires s) {
    mHeaderValues->put(TypeExpires,s);
}

HttpHeaderFrom _HttpHeader::getFrom() {
    return Cast<HttpHeaderFrom>(mHeaderValues->get(TypeFrom));
}

void _HttpHeader::setFrom(HttpHeaderFrom s) {
    mHeaderValues->put(TypeFrom,s);
}

HttpHeaderRange _HttpHeader::getRange() {
    return Cast<HttpHeaderRange>(mHeaderValues->get(TypeRange));
}

void _HttpHeader::setRange(HttpHeaderRange s) {
    mHeaderValues->put(TypeRange,s);
}

HttpHeaderReferer _HttpHeader::getReferer() {
    return Cast<HttpHeaderReferer>(mHeaderValues->get(TypeReferer));
}

void _HttpHeader::setReferer(HttpHeaderReferer s) {
    mHeaderValues->put(TypeReferer,s);
}

HttpHeaderReferrerPolicy _HttpHeader::getRefererPolicy() {
    return Cast<HttpHeaderReferrerPolicy>(mHeaderValues->get(TypeRefererPolicy));
}

void _HttpHeader::setRefererPolicy(HttpHeaderReferrerPolicy s) {
    mHeaderValues->put(TypeRefererPolicy,s);
}

HttpHeaderVary _HttpHeader::getVary() {
    return Cast<HttpHeaderVary>(mHeaderValues->get(TypeVary));
}

void _HttpHeader::setVary(HttpHeaderVary s) {
    mHeaderValues->put(TypeVary,s);
}

HttpHeaderVia _HttpHeader::getVia() {
    return Cast<HttpHeaderVia>(mHeaderValues->get(TypeVia));
}

void _HttpHeader::setVia(HttpHeaderVia s) {
    mHeaderValues->put(TypeVia,s);
}

HttpHeaderServer _HttpHeader::getServer() {
    return Cast<HttpHeaderServer>(mHeaderValues->get(TypeServer));
}

void _HttpHeader::setServer(HttpHeaderServer s) {
    mHeaderValues->put(TypeServer,s);
}

HttpHeaderWarning _HttpHeader::getWarning() {
    return Cast<HttpHeaderWarning>(mHeaderValues->get(TypeWarning));
}

void _HttpHeader::setWarning(HttpHeaderWarning s) {
    mHeaderValues->put(TypeWarning,s);
}

HttpHeaderAcceptCh _HttpHeader::getAcceptCh() {
    return Cast<HttpHeaderAcceptCh>(mHeaderValues->get(TypeAcceptCh));
}

void _HttpHeader::setAcceptCh(HttpHeaderAcceptCh s) {
    mHeaderValues->put(TypeAcceptCh,s);
}

HttpHeaderDnt _HttpHeader::getDnt() {
    return Cast<HttpHeaderDnt>(mHeaderValues->get(TypeDNT));
}

void _HttpHeader::setDnt(HttpHeaderDnt s) {
    mHeaderValues->put(TypeDNT,s);
}

HttpHeaderSaveData _HttpHeader::getSaveData() {
    return Cast<HttpHeaderSaveData>(mHeaderValues->get(TypeSaveData));
}

void _HttpHeader::setSaveData(HttpHeaderSaveData s) {
    mHeaderValues->put(TypeSaveData,s);
}

HttpHeaderSecFetchDest _HttpHeader::getSecFetchDest() {
    return Cast<HttpHeaderSecFetchDest>(mHeaderValues->get(TypeSecFetchDest));
}

void _HttpHeader::setSecFetchDest(HttpHeaderSecFetchDest s) {
    mHeaderValues->put(TypeSecFetchDest,s);
}

HttpHeaderSecFetchMode _HttpHeader::getSecFetchMode() {
    return Cast<HttpHeaderSecFetchMode>(mHeaderValues->get(TypeSecFetchMode));
}

void _HttpHeader::setSecFetchMode(HttpHeaderSecFetchMode s) {
    mHeaderValues->put(TypeSecFetchMode,s);
}

HttpHeaderSecFetchSite _HttpHeader::getSecFetchSite() {
    return Cast<HttpHeaderSecFetchSite>(mHeaderValues->get(TypeSecFetchSite));
}

void _HttpHeader::setSecFetchSite(HttpHeaderSecFetchSite s) {
    mHeaderValues->put(TypeSecFetchSite,s);
}

HttpHeaderSecFetchUser _HttpHeader::getSecFetchUser() {
    return Cast<HttpHeaderSecFetchUser>(mHeaderValues->get(TypeSecFetchUser));
}

void _HttpHeader::setSecFetchUser(HttpHeaderSecFetchUser s) {
    mHeaderValues->put(TypeSecFetchUser,s);
}

HttpHeaderSourceMap _HttpHeader::getSourceMap() {
    return Cast<HttpHeaderSourceMap>(mHeaderValues->get(TypeSourceMap));
}

void _HttpHeader::setSourceMap(HttpHeaderSourceMap s) {
    mHeaderValues->put(TypeSourceMap,s);
}

HttpHeaderServerTiming _HttpHeader::getServerTiming() {
    return Cast<HttpHeaderServerTiming>(mHeaderValues->get(TypeServerTiming));
}

void _HttpHeader::setServerTiming(HttpHeaderServerTiming s) {
    mHeaderValues->put(TypeServerTiming,s);
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
            header->append(st(HttpText)::ContentSpace,getVersion()->toString(),st(HttpText)::CRLF);
            break;
        }

        case st(HttpPacket)::Response: {
            header->append(getVersion()->toString(),st(HttpText)::ContentSpace,createString(mResponseStatus));
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
    
    ForEveryOne(pair,mHeaderValues) {
        switch(pair->getKey()) {
            case TypeLink: {
                auto links = Cast<ArrayList<HttpHeaderLink>>(pair->getValue());
                if(links != nullptr && links->size() != 0) {
                    auto linkIterator = links->getIterator();
                    while(linkIterator->hasValue()) {
                        header->append(st(HttpHeader)::Link,": ",linkIterator->getValue()->toString(),st(HttpText)::CRLF);
                        linkIterator->next();
                    }
                }
                continue;
            }
            break;

            case TypeCacheControl: {
                int headid = pair->getKey();
                String value = Cast<HttpHeaderCacheControl>(pair->getValue())->toString(mType);
                if(value != nullptr) {
                    String head = findString(headid);
                    header->append(head, ": ",value,st(HttpText)::CRLF);
                }
            }
            break;

            case TypeVersion:
            case TypeStatus:
            //do nothing
            break;

            default: {
                int headid = pair->getKey();
                String value = pair->getValue()->toString();
                String head = findString(headid);
                if (head != nullptr) {
                    header->append(head, ": ", value,st(HttpText)::CRLF);
                }
            }
        }
    }
    
    ListIterator<HttpCookie> iterator = mCookies->getIterator();
    while (iterator->hasValue()) {
        HttpCookie cookie = iterator->getValue();
        switch(type) {
            case st(HttpPacket)::Request:
            header->append(st(HttpHeader)::Cookie,": ",cookie->toString(type), st(HttpText)::CRLF);
            break;

            case st(HttpPacket)::Response:
            header->append(st(HttpHeader)::SetCookie,": ",cookie->toString(type), st(HttpText)::CRLF);
            break;
        }
        
        iterator->next();
    }

    if (header->size() == 0) {
        return nullptr;
    }

    return header->toString(0, header->size() - 2);
}

MapIterator<int,Object> _HttpHeader::getIterator() {
    return mHeaderValues->getIterator();
}

} // namespace obotcha
