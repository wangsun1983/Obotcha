#include <string.h>
#include <thread>
#include <mutex>

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
#include "Inspect.hpp"

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
const String _HttpHeader::CrossOriginEmbedderPolicy = createString("cross-origin-embedder-policy");
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
// Http2 authority
const String _HttpHeader::Authority = createString(":authority");
const String _HttpHeader::ClearSiteData = createString("clear-site-data");
const String _HttpHeader::Version = createString("#version");

// Transfer-Encoding type
const String _HttpHeader::TransferChunked = createString("chunked");

// Http connection
const String _HttpHeader::ConnectionClose = createString("close");

#define INIT_HTTP_HEADER(HeaderString,HeaderType) \
    st(HttpHeader)::idMaps->put(HeaderString,createInteger(HeaderType)); \
    st(HttpHeader)::names->add(HeaderString);

_HttpHeader::_HttpHeader(int protocol) {
    static std::once_flag flag;
    std::call_once(flag, []() {
        INIT_HTTP_HEADER(Method,TypeMethod);
        INIT_HTTP_HEADER(Path,TypePath);
        INIT_HTTP_HEADER(Scheme,TypeScheme);
        INIT_HTTP_HEADER(Status,TypeStatus);
        INIT_HTTP_HEADER(Protocol,TypeProtocol);
        INIT_HTTP_HEADER(Accept,TypeAccept);
        INIT_HTTP_HEADER(AcceptCh,TypeAcceptCh);
        INIT_HTTP_HEADER(AcceptCharset,TypeAcceptCharset);
        INIT_HTTP_HEADER(AcceptPatch,TypeAcceptPatch);
        INIT_HTTP_HEADER(AcceptDatetime,TypeAcceptDatetime);
        INIT_HTTP_HEADER(AcceptEncoding,TypeAcceptEncoding);
        INIT_HTTP_HEADER(AcceptLanguage,TypeAcceptLanguage);
        INIT_HTTP_HEADER(AcceptRanges,TypeAcceptRanges);
        INIT_HTTP_HEADER(AccessControlAllowCredentials,TypeAccessControlAllowCredentials);
        INIT_HTTP_HEADER(AccessControlAllowHeaders,TypeAccessControlAllowHeaders);
        INIT_HTTP_HEADER(AccessControlAllowMethods,TypeAccessControlAllowMethods);
        INIT_HTTP_HEADER(AccessControlAllowOrigin,TypeAccessControlAllowOrigin);
        INIT_HTTP_HEADER(AccessControlExposeHeaders,TypeAccessControlExposeHeaders);
        INIT_HTTP_HEADER(AccessControlMaxAge,TypeAccessControlMaxAge);
        INIT_HTTP_HEADER(AccessControlRequestHeaders,TypeAccessControlRequestHeaders);
        INIT_HTTP_HEADER(AccessControlRequestMethod,TypeAccessControlRequestMethod);
        INIT_HTTP_HEADER(Age,TypeAge);
        INIT_HTTP_HEADER(Allow,TypeAllow);
        INIT_HTTP_HEADER(AltSvc,TypeAltSvc);
        INIT_HTTP_HEADER(Authorization,TypeAuthorization);
        INIT_HTTP_HEADER(CacheControl,TypeCacheControl);
        INIT_HTTP_HEADER(Connection,TypeConnection);
        INIT_HTTP_HEADER(ContentDisposition,TypeContentDisposition);
        INIT_HTTP_HEADER(ContentEncoding,TypeContentEncoding);
        INIT_HTTP_HEADER(ContentLanguage,TypeContentLanguage);
        INIT_HTTP_HEADER(ContentLength,TypeContentLength);
        INIT_HTTP_HEADER(ContentLocation,TypeContentLocation);
        INIT_HTTP_HEADER(ContentMD5,TypeContentMD5);
        INIT_HTTP_HEADER(ContentRange,TypeContentRange);
        INIT_HTTP_HEADER(ContentSecurityPolicyReportOnly,TypeContentSecurityPolicyReportOnly);
        INIT_HTTP_HEADER(ContentSecurityPolicy,TypeContentSecurityPolicy);
        INIT_HTTP_HEADER(ContentType,TypeContentType);
        INIT_HTTP_HEADER(Cookie,TypeCookie);
        INIT_HTTP_HEADER(CrossOriginEmbedderPolicy,TypeCrossOriginEmbedderPolicy);
        INIT_HTTP_HEADER(CrossOriginOpenerPolicy,TypeCrossOriginOpenerPolicy);
        INIT_HTTP_HEADER(CrossOriginResourcePolicy,TypeCrossOriginResourcePolicy);
        INIT_HTTP_HEADER(DNT,TypeDNT);
        INIT_HTTP_HEADER(Date,TypeDate);
        INIT_HTTP_HEADER(ETag,TypeETag);
        INIT_HTTP_HEADER(Expect,TypeExpect);
        INIT_HTTP_HEADER(ExpectCT,TypeExpectCT);
        INIT_HTTP_HEADER(Expires,TypeExpires);
        INIT_HTTP_HEADER(From,TypeFrom);
        INIT_HTTP_HEADER(FrontEndHttps,TypeFrontEndHttps);
        INIT_HTTP_HEADER(Host,TypeHost);
        INIT_HTTP_HEADER(IfMatch,TypeIfMatch);
        INIT_HTTP_HEADER(IfModifiedSince,TypeIfModifiedSince);
        INIT_HTTP_HEADER(IfNoneMatch,TypeIfNoneMatch);
        INIT_HTTP_HEADER(IfRange,TypeIfRange);
        INIT_HTTP_HEADER(IfUnmodifiedSince,TypeIfUnmodifiedSince);
        INIT_HTTP_HEADER(KeepAlive,TypeKeepAlive);
        INIT_HTTP_HEADER(LastModified,TypeLastModified);
        INIT_HTTP_HEADER(Link,TypeLink);
        INIT_HTTP_HEADER(Location,TypeLocation);
        INIT_HTTP_HEADER(MaxForwards,TypeMaxForwards);
        INIT_HTTP_HEADER(Origin,TypeOrigin);
        INIT_HTTP_HEADER(P3P,TypeP3P);
        INIT_HTTP_HEADER(Pragma,TypePragma);
        INIT_HTTP_HEADER(ProxyAuthenticate,TypeProxyAuthenticate);
        INIT_HTTP_HEADER(ProxyAuthorization,TypeProxyAuthorization);
        INIT_HTTP_HEADER(ProxyConnection,TypeProxyConnection);
        INIT_HTTP_HEADER(Range,TypeRange);
        INIT_HTTP_HEADER(Referer,TypeReferer);
        INIT_HTTP_HEADER(RefererPolicy,TypeRefererPolicy);
        INIT_HTTP_HEADER(Refresh,TypeRefresh);
        INIT_HTTP_HEADER(RetryAfter,TypeRetryAfter);
        INIT_HTTP_HEADER(SaveData,TypeSaveData);
        INIT_HTTP_HEADER(SecWebSocketKey,TypeSecWebSocketKey);
        INIT_HTTP_HEADER(SecWebSocketAccept,TypeSecWebSocketAccept);
        INIT_HTTP_HEADER(Server,TypeServer);
        INIT_HTTP_HEADER(SetCookie,TypeSetCookie);
        INIT_HTTP_HEADER(SecTokenBinding,TypeSecTokenBinding);
        INIT_HTTP_HEADER(SecFetchDest,TypeSecFetchDest);
        INIT_HTTP_HEADER(SecFetchMode,TypeSecFetchMode);
        INIT_HTTP_HEADER(SecFetchSite,TypeSecFetchSite);
        INIT_HTTP_HEADER(SecFetchUser,TypeSecFetchUser);
        INIT_HTTP_HEADER(StrictTransportSecurity,TypeStrictTransportSecurity);
        INIT_HTTP_HEADER(TE,TypeTE);
        INIT_HTTP_HEADER(Timestamp,TypeTimestamp);
        INIT_HTTP_HEADER(Trailer,TypeTrailer);
        INIT_HTTP_HEADER(TransferEncoding,TypeTransferEncoding);
        INIT_HTTP_HEADER(Upgrade,TypeUpgrade);
        INIT_HTTP_HEADER(UserAgent,TypeUserAgent);
        INIT_HTTP_HEADER(VIP,TypeVIP);
        INIT_HTTP_HEADER(Vary,TypeVary);
        INIT_HTTP_HEADER(Via,TypeVia);
        INIT_HTTP_HEADER(WWWAuthenticate,TypeWWWAuthenticate);
        INIT_HTTP_HEADER(Warning,TypeWarning);
        INIT_HTTP_HEADER(XAccelRedirect,TypeXAccelRedirect);
        INIT_HTTP_HEADER(XContentSecurityPolicyReportOnly,TypeXContentSecurityPolicyReportOnly);
        INIT_HTTP_HEADER(XContentTypeOptions,TypeXContentTypeOptions);
        INIT_HTTP_HEADER(XForwardedFor,TypeXForwardedFor);
        INIT_HTTP_HEADER(XForwardedProto,TypeXForwardedProto);
        INIT_HTTP_HEADER(Forwarded,TypeForwarded);
        INIT_HTTP_HEADER(XFrameOptions,TypeXFrameOptions);
        INIT_HTTP_HEADER(XPoweredBy,TypeXPoweredBy);
        INIT_HTTP_HEADER(XRealIP,TypeXRealIP);
        INIT_HTTP_HEADER(XRequestedWith,TypeXRequestedWith);
        INIT_HTTP_HEADER(XThriftProtocol,TypeXThriftProtocol);
        INIT_HTTP_HEADER(XUACompatible,TypeXUACompatible);
        INIT_HTTP_HEADER(XWapProfile,TypeXWapProfile);
        INIT_HTTP_HEADER(XXSSProtection,TypeXXSSProtection);
        INIT_HTTP_HEADER(SecWebSocketVersion,TypeSecWebSocketVersion);
        INIT_HTTP_HEADER(SecWebSocketExtensions,TypeSecWebSocketExtensions);
        INIT_HTTP_HEADER(SecWebSocketOrigin,TypeSecWebSocketOrigin);
        INIT_HTTP_HEADER(SecWebSocketKey1,TypeSecWebSocketKey1);
        INIT_HTTP_HEADER(SecWebSocketKey2,TypeSecWebSocketKey2);
        INIT_HTTP_HEADER(SecWebSocketKey3,TypeSecWebSocketKey3);
        INIT_HTTP_HEADER(SecWebSocketProtocol,TypeSecWebSocketProtocol);
        INIT_HTTP_HEADER(ServerTiming,TypeServerTiming);
        INIT_HTTP_HEADER(SourceMap,TypeSourceMap);
        INIT_HTTP_HEADER(Digest,TypeDigest);
        INIT_HTTP_HEADER(Authority,TypeAuthority);
        INIT_HTTP_HEADER(ClearSiteData,TypeClearSiteData);
        INIT_HTTP_HEADER(Version,TypeVersion);
    });
    mProtocol = protocol;
    mCookies = createArrayList<HttpCookie>();
    mHeaderValues = createHashMap<String,Object>();
    reset();
}
#undef INIT_HTTP_HEADER

void _HttpHeader::append(sp<_HttpHeader> h) {
    ForEveryOne(pairCookie,h->mCookies) {
        mCookies->add(pairCookie);
    }

    ForEveryOne(pair,h->mHeaderValues) {
        if(pair->getKey()->equals(Link)) {
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
    //mValues->clear(); 
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
                mUrl->load(value);
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
                v->load(value);
                setAcceptCharSet(v);
                return;
            }

            case TypeAcceptCh: {
                auto v = createHttpHeaderAcceptCh();
                v->load(value);
                setAcceptCh(v);
                return;
            }

            case TypeAccept:{
                auto v = createHttpHeaderAccept();
                v->load(value);
                setAccept(v);
                return;
            }

            case TypeAcceptEncoding:{
                auto v = createHttpHeaderAcceptEncoding();
                v->load(value);
                setAcceptEncoding(v);
                return;
            }

            case TypeAcceptLanguage: {
                auto v = createHttpHeaderAcceptLanguage();
                v->load(value);
                setAcceptLanguage(v);
                return;
            }

            case TypeTransferEncoding: {
                auto v = createHttpHeaderTransferEncoding();
                v->load(value);
                setTransferEncoding(v);
                return;
            }

            case TypeAcceptPatch: {
                auto v = createHttpHeaderAcceptPatch();
                v->load(value);
                setAcceptPatch(v);
                return;
            }

            case TypeVersion: {
                auto v = createHttpHeaderVersion();
                v->load(value);
                setVersion(v);
                return;
            }

            case TypeAccessControlAllowCredentials: {
                auto v = createHttpHeaderAccessControlAllowCredentials();
                v->load(value);
                setAllowCredentials(v);
                return;
            }

            case TypeAccessControlAllowHeaders: {
                auto v = createHttpHeaderAccessControlAllowHeaders();
                v->load(value);
                setAllowHeaders(v);
                return;
            }

            case TypeAccessControlAllowMethods: {
                auto v = createHttpHeaderAccessControlAllowMethods();
                v->load(value);
                setAllowMethods(v);
                return;
            }

            case TypeAccessControlAllowOrigin: {
                auto v = createHttpHeaderAccessControlAllowOrigin();
                v->load(value);
                setAllowOrigin(v);
                return;
            }

            case TypeAccessControlExposeHeaders: {
                auto v = createHttpHeaderAccessControlExposeHeaders();
                v->load(value);
                setExposeHeaders(v);
                return;
            }
            
            case TypeAccessControlMaxAge: {
                auto v = createHttpHeaderAccessControlMaxAge();
                v->load(value);
                setMaxAge(v);
                return;
            }

            case TypeAccessControlRequestHeaders: {
                auto v = createHttpHeaderAccessControlRequestHeaders();
                v->load(value);
                setAccessControlReqeuestHeaders(v);
                return;
            }

            case TypeAccessControlRequestMethod: {
                auto v = createHttpHeaderAccessControlRequestMethod();
                v->load(value);
                setAccessControlRequestMethod(v);
                return;
            }

            case TypeAge: {
                auto v = createHttpHeaderAge();
                v->load(value);
                setAge(v);
                return;
            }

            case TypeAllow: {
                auto v = createHttpHeaderAllow();
                v->load(value);
                setAllow(v);
                return;
            }

            case TypeAuthorization: {
                auto v= createHttpHeaderAuthorization();
                v->load(value);
                setAuthorization(v);
                return;
            }
            
            case TypeCacheControl: {
                auto v = createHttpHeaderCacheControl();
                v->load(value);
                setCacheControl(v);
                return;
            }

            case TypeClearSiteData: {
                auto v = createHttpHeaderClearSiteData();
                v->load(value);
                setClearSiteData(v);
                return;
            }

            case TypeContentDisposition: {
                auto v = createHttpHeaderContentDisposition();
                v->load(value);
                setContentDisposition(v);
                return;
            }

            case TypeContentEncoding: {
                auto v = createHttpHeaderContentEncoding();
                v->load(value);
                setContentEncoding(v);
                return;
            }

            case TypeContentLanguage: {
                auto v = createHttpHeaderContentLanguage();
                v->load(value);
                setContentLanguage(v);
                return;
            }

            case TypeContentLength: {
                auto v = createHttpHeaderContentLength();
                v->load(value);
                setContentLength(v);
                return;
            }

            case TypeContentLocation: {
                auto v = createHttpHeaderContentLocation();
                v->load(value);
                setContentLocation(v);
                return;
            }

            case TypeContentType: {
                auto v = createHttpHeaderContentType();
                v->load(value);
                setContentType(v);
                return;
            }

            case TypeForwarded: {
                auto v = createHttpHeaderForwarded();
                v->load(value);
                setForwarded(v);
                return;
            }

            case TypeConnection: {
                auto v = createHttpHeaderConnection();
                v->load(value);
                setConnection(v);
                return;
            }

            case TypeDigest: {
                auto v = createHttpHeaderDigest();
                v->load(value);
                setDigest(v);
                return;
            }

            case TypeHost: {
                auto v = createHttpHeaderHost();
                v->load(value);
                setHost(v);
                return;
            }

            case TypeKeepAlive: {
                auto v = createHttpHeaderKeepAlive();
                v->load(value);
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
                v->load(value);
                setIfMatch(v);
                return;
            }

            case TypeIfNoneMatch: {
                auto v = createHttpHeaderMatch();
                v->load(value);
                setIfNoneMatch(v);
                return;
            }

            case TypeRetryAfter: {
                auto v = createHttpHeaderRetryAfter();
                v->load(value);
                setRetryAfter(v);
                return;
            }

            case TypeUserAgent: {
                auto v = createHttpHeaderUserAgent();
                v->load(value);
                setUserAgent(v);
                return;
            }
            
            case TypeIfModifiedSince: {
                auto v = createHttpHeaderIfModifiedSince();
                v->load(value);
                setIfModifiedSince(v);
                return;
            }

            case TypeIfRange: {
                auto v = createHttpHeaderIfRange();
                v->load(value);
                setIfRange(v);
                return;
            }

            case TypeIfUnmodifiedSince: {
                auto v = createHttpHeaderIfUnmodifiedSince();
                v->load(value);
                setIfUnmodifiedSince(v);
                return;
            }

            case TypeProxyAuthenticate: {
                auto v = createHttpHeaderProxyAuthenticate();
                v->load(value);
                setProxyAuthenticate(v);
                return;
            }

            case TypeProxyAuthorization: {
                auto v = createHttpHeaderProxyAuthorization();
                v->load(value);
                setProxyAuthorization(v);
                return;
            }
            
            case TypeStrictTransportSecurity: {
                auto v = createHttpHeaderStrictTransportSecurity();
                v->load(value);
                setStrictTransportSecurity(v);
                return;
            }

            case TypeXFrameOptions: {
                auto v = createHttpHeaderXFrameOptions();
                v->load(value);
                setXFrameOptions(v);
                return;
            }

            case TypeUpgrade: {
                auto v = createHttpHeaderUpgrade();
                v->load(value);
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
                v->load(value);
                setWebSocketAccept(v);
                return;
            }

            case TypeSecWebSocketKey: {
                auto v = createHttpHeaderSecWebSocketKey();
                v->load(value);
                setWebSocketKey(v);
                return;
            }

            case TypeSecWebSocketVersion: {
                auto v = createHttpHeaderSecWebSocketVersion();
                v->load(value);
                setWebSocketVersion(v);
                return;
            }

            case TypeSecWebSocketExtensions: {
                auto v = createHttpHeaderSecWebSocketExtensions();
                v->load(value);
                setWebSocketExtensions(v);
                return;
            }

            case TypeSecWebSocketOrigin: {
                auto v = createHttpHeaderSecWebSocketOrigin();
                v->load(value);
                setWebSocketOrigin(v);
                return;
            }

            case TypeSecWebSocketKey1: {
                auto v = createHttpHeaderSecWebSocketKey();
                v->load(value);
                setWebSocketKey1(v);
                return;
            }

            case TypeSecWebSocketKey2: {
                auto v = createHttpHeaderSecWebSocketKey();
                v->load(value);
                setWebSocketKey2(v);
                return;
            }

            case TypeSecWebSocketKey3: {
                auto v = createHttpHeaderSecWebSocketKey();
                v->load(value);
                setWebSocketKey3(v);;
                return;
            }

            case TypeSecWebSocketProtocol: {
                auto v = createHttpHeaderSecWebSocketProtocol();
                v->load(value);
                setWebSocketProtocol(v);
                return;
            }

            case TypeOrigin: {
                auto v = createHttpHeaderOrigin();
                v->load(value);
                setOrigin(v);
                return;
            }

            case TypePragma: {
                auto v = createHttpHeaderPragma();
                v->load(value);
                setPragma(v);
                return;
            }

            case TypeAcceptRanges: {
                auto v = createHttpHeaderAcceptRanges();
                v->load(value);
                setHttpHeaderAcceptRanges(v);
                return;
            }

            case TypeAltSvc: {
                auto v = createHttpHeaderAltSvc();
                v->load(value);
                setAltSvc(v);
                return;
            }

            case TypeContentRange: {
                auto v = createHttpHeaderContentRange();
                v->load(value);
                setContentRange(v);
                return;
            }

            case TypeContentSecurityPolicy: {
                auto v = createHttpHeaderContentSecurityPolicy();
                v->load(value);
                setSecurityPolicy(v);
                return;
            }

            case TypeContentSecurityPolicyReportOnly: {
                auto v = createHttpHeaderContentSecurityPolicy();
                v->load(value);
                setSecurityPolicyReportOnly(v);
                return;
            }

            case TypeCrossOriginEmbedderPolicy: {
                auto v = createHttpHeaderCrossOriginEmbedderPolicy();
                v->load(value);
                setCrossOriginEmbedderPolicy(v);
                return;
            }

            case TypeCrossOriginOpenerPolicy: {
                auto v = createHttpHeaderCrossOriginOpenerPolicy();
                v->load(value);
                setCrossOriginOpenerPolicy(v);
                return;
            }

            case TypeCrossOriginResourcePolicy: {
                auto v = createHttpHeaderCrossOriginResourcePolicy();
                v->load(value);
                setCrossOriginResourcePolicy(v);
                return;
            }

            case TypeDate: {
                auto v = createHttpHeaderDate();
                v->load(value);
                setDate(v);
                return;
            }

            case TypeExpect: {
                auto v = createHttpHeaderExpect();
                v->load(value);
                setExpect(v);
                return;
            }

            case TypeExpectCT: {
                auto v = createHttpHeaderExpectCT();
                v->load(value);
                setExpectCT(v);
                return;
            }

            case TypeExpires: {
                auto v = createHttpHeaderExpires();
                v->load(value);
                setExpires(v);
                return;
            }

            case TypeFrom: {
                auto v = createHttpHeaderFrom();
                v->load(value);
                setFrom(v);
                return;
            }

            case TypeRange: {
                auto v = createHttpHeaderRange();
                v->load(value);
                setRange(v);
                return;
            }

            case TypeReferer: {
                auto v = createHttpHeaderReferer();
                v->load(value);
                setReferer(v);
                return;
            }

            case TypeRefererPolicy: {
                auto v = createHttpHeaderReferrerPolicy();
                v->load(value);
                setRefererPolicy(v);
                return;
            }

            case TypeVary: {
                auto v = createHttpHeaderVary();
                v->load(value);
                setVary(v);
                return;
            }

            case TypeVia: {
                auto v = createHttpHeaderVia();
                v->load(value);
                setVia(v);
                return;
            }

            case TypeServer: {
                auto v = createHttpHeaderServer();
                v->load(value);
                setServer(v);
                return;
            }

            case TypeWarning: {
                auto v = createHttpHeaderWarning();
                v->load(value);
                setWarning(v);
                return;
            }

            case TypeDNT: {
                auto v = createHttpHeaderDnt();
                v->load(value);
                setDnt(v);
                return;
            }

            case TypeSaveData: {
                auto v = createHttpHeaderSaveData();
                v->load(value);
                setSaveData(v);
                return;
            }

            case TypeSecFetchDest: {
                auto v = createHttpHeaderSecFetchDest();
                v->load(value);
                setSecFetchDest(v);
                return;
            }

            case TypeSecFetchMode: {
                auto v = createHttpHeaderSecFetchMode();
                v->load(value);
                setSecFetchMode(v);
                return;
            }

            case TypeSecFetchSite: {
                auto v = createHttpHeaderSecFetchSite();
                v->load(value);
                setSecFetchSite(v);
                return;
            }

            case TypeSecFetchUser: {
                auto v = createHttpHeaderSecFetchUser();
                v->load(value);
                setSecFetchUser(v);
                return;
            }

            case TypeServerTiming: {
                auto v = createHttpHeaderServerTiming();
                v->load(value);
                setServerTiming(v);
                return;
            }

            case TypeSourceMap: {
                auto v = createHttpHeaderSourceMap();
                v->load(value);
                setSourceMap(v);
                return;
            }
        }
    }
    mHeaderValues->put(key->toLowerCase(), value);
}

String _HttpHeader::get(String header) {
    auto value = mHeaderValues->get(header->toLowerCase());
    if(value == nullptr) {
        return nullptr;
    }
    return value->toString();
}

int _HttpHeader::size() { 
    return mHeaderValues->size(); 
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

bool _HttpHeader::setResponseReason(String s) { 
    Inspect(!st(HttpStatus)::isValid(s),false);
    mResponseReason = s; 
    return true;
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
    return Cast<String>(mHeaderValues->get(Authority));
}

void _HttpHeader::setAuthority(String s) {
    mHeaderValues->put(Authority,s);
}

//HttpHeaderAcceptCharSet
HttpHeaderAcceptCharSet _HttpHeader::getAcceptCharSet() {
    return Cast<HttpHeaderAcceptCharSet>(mHeaderValues->get(AcceptCharset));
}

void _HttpHeader::setAcceptCharSet(HttpHeaderAcceptCharSet v) {
    mHeaderValues->put(AcceptCharset,v);
}

HttpHeaderAccept _HttpHeader::getAccept() {
    return Cast<HttpHeaderAccept>(mHeaderValues->get(Accept));
}

void _HttpHeader::setAccept(HttpHeaderAccept s) {
    mHeaderValues->put(Accept,s);
}

HttpHeaderAcceptEncoding _HttpHeader::getAcceptEncoding() {
    return Cast<HttpHeaderAcceptEncoding>(mHeaderValues->get(AcceptEncoding));
}

void _HttpHeader::setAcceptEncoding(HttpHeaderAcceptEncoding s) {
    mHeaderValues->put(AcceptEncoding,s);
}

HttpHeaderAcceptLanguage _HttpHeader::getAcceptLanguage() {
    return Cast<HttpHeaderAcceptLanguage>(mHeaderValues->get(AcceptLanguage));
}

void _HttpHeader::setAcceptLanguage(HttpHeaderAcceptLanguage s) {
    mHeaderValues->put(AcceptLanguage,s);
}

HttpHeaderAcceptPatch _HttpHeader::getAcceptPatch() {
    return Cast<HttpHeaderAcceptPatch>(mHeaderValues->get(AcceptPatch));
}

void _HttpHeader::setAcceptPatch(HttpHeaderAcceptPatch s) {
    mHeaderValues->put(AcceptPatch,s);
}

HttpHeaderAccessControlAllowCredentials _HttpHeader::getAllowCredentials() {
    return Cast<HttpHeaderAccessControlAllowCredentials>(mHeaderValues->get(AccessControlAllowCredentials));
}

void _HttpHeader::setAllowCredentials(HttpHeaderAccessControlAllowCredentials s) {
    mHeaderValues->put(AccessControlAllowCredentials,s);
}

HttpHeaderAccessControlAllowHeaders _HttpHeader::getAllowHeaders() {
    return Cast<HttpHeaderAccessControlAllowHeaders>(mHeaderValues->get(AccessControlAllowHeaders));
}

void _HttpHeader::setAllowHeaders(HttpHeaderAccessControlAllowHeaders s) {
    mHeaderValues->put(AccessControlAllowHeaders,s);
}

HttpHeaderAccessControlAllowMethods _HttpHeader::getAllowMethods() {
    return Cast<HttpHeaderAccessControlAllowMethods>(mHeaderValues->get(AccessControlAllowMethods));
}

void _HttpHeader::setAllowMethods(HttpHeaderAccessControlAllowMethods s) {
    mHeaderValues->put(AccessControlAllowMethods,s);
}

//HttpHeaderAccessControlAllowOrigin
HttpHeaderAccessControlAllowOrigin _HttpHeader::getAllowOrigin() {
    return Cast<HttpHeaderAccessControlAllowOrigin>(mHeaderValues->get(AccessControlAllowOrigin));
}

void _HttpHeader::setAllowOrigin(HttpHeaderAccessControlAllowOrigin s) {
    mHeaderValues->put(AccessControlAllowOrigin,s);
}

HttpHeaderAccessControlExposeHeaders _HttpHeader::getExposeHeaders() {
    return Cast<HttpHeaderAccessControlExposeHeaders>(mHeaderValues->get(AccessControlExposeHeaders));
}

void _HttpHeader::setExposeHeaders(HttpHeaderAccessControlExposeHeaders s) {
    mHeaderValues->put(AccessControlExposeHeaders,s);
}

HttpHeaderAccessControlMaxAge _HttpHeader::getMaxAge() {
    return Cast<HttpHeaderAccessControlMaxAge>(mHeaderValues->get(AccessControlMaxAge));
}

void _HttpHeader::setMaxAge(HttpHeaderAccessControlMaxAge s) {
    mHeaderValues->put(AccessControlMaxAge,s);
}

HttpHeaderAccessControlRequestHeaders _HttpHeader::getAccessControlRequestHeaders() {
    return Cast<HttpHeaderAccessControlRequestHeaders>(mHeaderValues->get(AccessControlRequestHeaders));
}

void _HttpHeader::setAccessControlReqeuestHeaders(HttpHeaderAccessControlRequestHeaders s) {
    mHeaderValues->put(AccessControlRequestHeaders,s);
}

HttpHeaderAccessControlRequestMethod _HttpHeader::getAccessControlRequestMethod() {
    return Cast<HttpHeaderAccessControlRequestMethod>(mHeaderValues->get(AccessControlRequestMethod));
}

void _HttpHeader::setAccessControlRequestMethod(HttpHeaderAccessControlRequestMethod s) {
    mHeaderValues->put(AccessControlRequestMethod,s);
}

HttpHeaderAge _HttpHeader::getAge() {
    return Cast<HttpHeaderAge>(mHeaderValues->get(Age));
}

void _HttpHeader::setAge(HttpHeaderAge s) {
    mHeaderValues->put(Age,s);
}

HttpHeaderAllow _HttpHeader::getAllow() {
    return Cast<HttpHeaderAllow>(mHeaderValues->get(Allow));
}

void _HttpHeader::setAllow(HttpHeaderAllow s) {
    mHeaderValues->put(Allow,s);
}

HttpHeaderAuthorization _HttpHeader::getAuthorization() {
    return Cast<HttpHeaderAuthorization>(mHeaderValues->get(Authorization));
}

void _HttpHeader::setAuthorization(HttpHeaderAuthorization s) {
    mHeaderValues->put(Authorization,s);
}

HttpHeaderCacheControl _HttpHeader::getCacheControl() {
    return Cast<HttpHeaderCacheControl>(mHeaderValues->get(CacheControl));
}

void _HttpHeader::setCacheControl(HttpHeaderCacheControl s) {
    mHeaderValues->put(CacheControl,s);
}

HttpHeaderClearSiteData _HttpHeader::getClearSiteData() {
    return Cast<HttpHeaderClearSiteData>(mHeaderValues->get(ClearSiteData));
}

void _HttpHeader::setClearSiteData(HttpHeaderClearSiteData s) {
    mHeaderValues->put(ClearSiteData,s);
}

HttpHeaderContentDisposition _HttpHeader::getContentDisposition() {
    return Cast<HttpHeaderContentDisposition>(mHeaderValues->get(ContentDisposition));
}

void _HttpHeader::setContentDisposition(HttpHeaderContentDisposition s) {
    mHeaderValues->put(ContentDisposition,s);
}

HttpHeaderContentEncoding _HttpHeader::getContentEncoding() {
    return Cast<HttpHeaderContentEncoding>(mHeaderValues->get(ContentEncoding));
}

void _HttpHeader::setContentEncoding(HttpHeaderContentEncoding s) {
    mHeaderValues->put(ContentEncoding,s);
}

HttpHeaderContentLanguage _HttpHeader::getContentLanguage() {
    return Cast<HttpHeaderContentLanguage>(mHeaderValues->get(ContentLanguage));
}

void _HttpHeader::setContentLanguage(HttpHeaderContentLanguage s) {
    mHeaderValues->put(ContentLanguage,s);
}

HttpHeaderContentLength _HttpHeader::getContentLength() {
    return Cast<HttpHeaderContentLength>(mHeaderValues->get(ContentLength));
}

void _HttpHeader::setContentLength(HttpHeaderContentLength s) {
    mHeaderValues->put(ContentLength,s);
}

HttpHeaderContentLocation _HttpHeader::getContentLocation() {
    return Cast<HttpHeaderContentLocation>(mHeaderValues->get(ContentLocation));
}

void _HttpHeader::setContentLocation(HttpHeaderContentLocation s) {
    mHeaderValues->put(ContentLocation,s);
}

HttpHeaderContentType _HttpHeader::getContentType() {
    return Cast<HttpHeaderContentType>(mHeaderValues->get(ContentType));
}

void _HttpHeader::setContentType(HttpHeaderContentType s) {
    mHeaderValues->put(ContentType,s);
}

HttpHeaderForwarded _HttpHeader::getForwarded() {
    return Cast<HttpHeaderForwarded>(mHeaderValues->get(Forwarded));
}

void _HttpHeader::setForwarded(HttpHeaderForwarded s) {
    mHeaderValues->put(Forwarded,s);
}

HttpHeaderConnection _HttpHeader::getConnection() {
    return Cast<HttpHeaderConnection>(mHeaderValues->get(Connection));
}

void _HttpHeader::setConnection(HttpHeaderConnection s) {
    mHeaderValues->put(Connection,s);
}

HttpHeaderDigest _HttpHeader::getDigest() {
    return Cast<HttpHeaderDigest>(mHeaderValues->get(Digest));
}

void _HttpHeader::setDigest(HttpHeaderDigest s) {
    mHeaderValues->put(Digest,s);
}

HttpHeaderHost _HttpHeader::getHost() {
    return Cast<HttpHeaderHost>(mHeaderValues->get(Host));
}

void _HttpHeader::setHost(HttpHeaderHost s) {
    mHeaderValues->put(Host,s);
}

HttpHeaderKeepAlive _HttpHeader::getKeepAlive() {
    return Cast<HttpHeaderKeepAlive>(mHeaderValues->get(KeepAlive));
}

void _HttpHeader::setKeepAlive(HttpHeaderKeepAlive s) {
    mHeaderValues->put(KeepAlive,s);
}

ArrayList<HttpHeaderLink> _HttpHeader::getLinks() {
    return Cast<ArrayList<HttpHeaderLink>>(mHeaderValues->get(Link));
}

void _HttpHeader::setLinks(ArrayList<HttpHeaderLink> s) {
    mHeaderValues->put(Link,s);
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
    return Cast<HttpHeaderMatch>(mHeaderValues->get(IfMatch));
}

void _HttpHeader::setIfMatch(HttpHeaderMatch s) {
    mHeaderValues->put(IfMatch,s);
}

HttpHeaderMatch _HttpHeader::getIfNoneMatch() {
    return Cast<HttpHeaderMatch>(mHeaderValues->get(IfNoneMatch));
}

void _HttpHeader::setIfNoneMatch(HttpHeaderMatch s) {
    mHeaderValues->put(IfNoneMatch,s);
}

HttpHeaderRetryAfter _HttpHeader::getRetryAfter() {
    return Cast<HttpHeaderRetryAfter>(mHeaderValues->get(RetryAfter));
}

void _HttpHeader::setRetryAfter(HttpHeaderRetryAfter s) {
    mHeaderValues->put(RetryAfter,s);
}

HttpHeaderUserAgent _HttpHeader::getUserAgent() {
    return Cast<HttpHeaderUserAgent>(mHeaderValues->get(UserAgent));
}

void _HttpHeader::setUserAgent(HttpHeaderUserAgent s) {
    mHeaderValues->put(UserAgent,s);
}

HttpHeaderIfModifiedSince _HttpHeader::getIfModifiedSince() {
    return Cast<HttpHeaderIfModifiedSince>(mHeaderValues->get(IfModifiedSince));
}

void _HttpHeader::setIfModifiedSince(HttpHeaderIfModifiedSince s) {
    mHeaderValues->put(IfModifiedSince,s);
}

HttpHeaderIfRange _HttpHeader::getIfRange() {
    return Cast<HttpHeaderIfRange>(mHeaderValues->get(IfRange));
}

void _HttpHeader::setIfRange(HttpHeaderIfRange s) {
    mHeaderValues->put(IfRange,s);
}

HttpHeaderIfUnmodifiedSince _HttpHeader::getIfUnmodifiedSince() {
    return Cast<HttpHeaderIfUnmodifiedSince>(mHeaderValues->get(IfUnmodifiedSince));
}

void _HttpHeader::setIfUnmodifiedSince(HttpHeaderIfUnmodifiedSince s) {
    mHeaderValues->put(IfUnmodifiedSince,s);
}

HttpHeaderProxyAuthenticate _HttpHeader::getProxyAuthenticate() {
    return Cast<HttpHeaderProxyAuthenticate>(mHeaderValues->get(ProxyAuthenticate));
}

void _HttpHeader::setProxyAuthenticate(HttpHeaderProxyAuthenticate s) {
    mHeaderValues->put(ProxyAuthenticate,s);
}

HttpHeaderProxyAuthorization _HttpHeader::getProxyAuthorization() {
    return Cast<HttpHeaderProxyAuthorization>(mHeaderValues->get(ProxyAuthorization));
}

void _HttpHeader::setProxyAuthorization(HttpHeaderProxyAuthorization s) {
    mHeaderValues->put(ProxyAuthorization,s);
}

HttpHeaderStrictTransportSecurity _HttpHeader::getStrictTransportSecurity() {
    return Cast<HttpHeaderStrictTransportSecurity>(mHeaderValues->get(StrictTransportSecurity));
}

void _HttpHeader::setStrictTransportSecurity(HttpHeaderStrictTransportSecurity s) {
    mHeaderValues->put(StrictTransportSecurity,s);
}

HttpHeaderVersion _HttpHeader::getVersion() {
    return Cast<HttpHeaderVersion>(mHeaderValues->get(Version));
}

void _HttpHeader::setVersion(HttpHeaderVersion s) {
    mHeaderValues->put(Version,s);
}

HttpHeaderXFrameOptions _HttpHeader::getXFrameOptions() {
    return Cast<HttpHeaderXFrameOptions>(mHeaderValues->get(XFrameOptions));
}

void _HttpHeader::setXFrameOptions(HttpHeaderXFrameOptions s) {
    mHeaderValues->put(XFrameOptions,s);
}

HttpHeaderTransferEncoding _HttpHeader::getTransferEncoding() {
    return Cast<HttpHeaderTransferEncoding>(mHeaderValues->get(TransferEncoding));
}

void _HttpHeader::setTransferEncoding(HttpHeaderTransferEncoding s) {
    mHeaderValues->put(TransferEncoding,s);
}

void _HttpHeader::setUpgrade(HttpHeaderUpgrade s) {
    mHeaderValues->put(Upgrade,s);
}

HttpHeaderUpgrade _HttpHeader::getUpgrade() {
    return Cast<HttpHeaderUpgrade>(mHeaderValues->get(Upgrade));
}

void _HttpHeader::setWebSocketAccept(HttpHeaderSecWebSocketAccept s) {
    mHeaderValues->put(SecWebSocketAccept,s);
}

HttpHeaderSecWebSocketAccept _HttpHeader::getWebSocketAccept() {
    return Cast<HttpHeaderSecWebSocketAccept>(mHeaderValues->get(SecWebSocketAccept));
}

void _HttpHeader::setWebSocketKey(HttpHeaderSecWebSocketKey s) {
    mHeaderValues->put(SecWebSocketKey,s);
}

HttpHeaderSecWebSocketKey _HttpHeader::getWebSocketKey() {
    return Cast<HttpHeaderSecWebSocketKey>(mHeaderValues->get(SecWebSocketKey));
}

void _HttpHeader::setWebSocketProtocol(HttpHeaderSecWebSocketProtocol s) {
    mHeaderValues->put(SecWebSocketProtocol,s);
}

HttpHeaderSecWebSocketProtocol _HttpHeader::getWebSocketProtocol() {
    return Cast<HttpHeaderSecWebSocketProtocol>(mHeaderValues->get(SecWebSocketProtocol));
}

void _HttpHeader::setWebSocketKey1(HttpHeaderSecWebSocketKey s) {
    mHeaderValues->put(SecWebSocketKey1,s);
}

HttpHeaderSecWebSocketKey _HttpHeader::getWebSocketKey1() {
    return Cast<HttpHeaderSecWebSocketKey>(mHeaderValues->get(SecWebSocketKey1));
}

void _HttpHeader::setWebSocketKey2(HttpHeaderSecWebSocketKey s) {
    mHeaderValues->put(SecWebSocketKey2,s);
}

HttpHeaderSecWebSocketKey _HttpHeader::getWebSocketKey2() {
    return Cast<HttpHeaderSecWebSocketKey>(mHeaderValues->get(SecWebSocketKey2));
}

void _HttpHeader::setWebSocketKey3(HttpHeaderSecWebSocketKey s) {
    mHeaderValues->put(SecWebSocketKey3,s);
}

HttpHeaderSecWebSocketKey _HttpHeader::getWebSocketKey3() {
    return Cast<HttpHeaderSecWebSocketKey>(mHeaderValues->get(SecWebSocketKey3));
}

void _HttpHeader::setWebSocketVersion(HttpHeaderSecWebSocketVersion s) {
    mHeaderValues->put(SecWebSocketVersion,s);
}

HttpHeaderSecWebSocketVersion _HttpHeader::getWebSocketVersion() {
    return Cast<HttpHeaderSecWebSocketVersion>(mHeaderValues->get(SecWebSocketVersion));
}

void _HttpHeader::setWebSocketExtensions(HttpHeaderSecWebSocketExtensions s) {
    mHeaderValues->put(SecWebSocketExtensions,s);
}

HttpHeaderSecWebSocketExtensions _HttpHeader::getWebSocketExtensions() {
    return Cast<HttpHeaderSecWebSocketExtensions>(mHeaderValues->get(SecWebSocketExtensions));
}

void _HttpHeader::setWebSocketOrigin(HttpHeaderSecWebSocketOrigin s) {
    mHeaderValues->put(SecWebSocketOrigin,s);
}

HttpHeaderSecWebSocketOrigin _HttpHeader::getWebSocketOrigin() {
    return Cast<HttpHeaderSecWebSocketOrigin>(mHeaderValues->get(SecWebSocketOrigin));
}

void _HttpHeader::setOrigin(HttpHeaderOrigin s) {
    mHeaderValues->put(Origin,s);
}

HttpHeaderOrigin _HttpHeader::getOrigin() {
    return Cast<HttpHeaderOrigin>(mHeaderValues->get(Origin));
}

void _HttpHeader::setPragma(HttpHeaderPragma s) {
    mHeaderValues->put(Pragma,s);
}

HttpHeaderPragma _HttpHeader::getPragma() {
    return Cast<HttpHeaderPragma>(mHeaderValues->get(Pragma));
}

void _HttpHeader::setHttpHeaderAcceptRanges(HttpHeaderAcceptRanges s) {
    mHeaderValues->put(AcceptRanges,s);
}

HttpHeaderAcceptRanges _HttpHeader::getAcceptRanges() {
    return Cast<HttpHeaderAcceptRanges>(mHeaderValues->get(AcceptRanges));
}

void _HttpHeader::setAltSvc(HttpHeaderAltSvc s) {
    mHeaderValues->put(AltSvc,s);
}

HttpHeaderAltSvc _HttpHeader::getAltSvc() {
    return Cast<HttpHeaderAltSvc>(mHeaderValues->get(AltSvc));
}

void _HttpHeader::setContentRange(HttpHeaderContentRange s) {
    mHeaderValues->put(ContentRange,s);
}

HttpHeaderContentRange _HttpHeader::getContentRange() {
    return Cast<HttpHeaderContentRange>(mHeaderValues->get(ContentRange));
}

void _HttpHeader::setSecurityPolicy(HttpHeaderContentSecurityPolicy s) {
    mHeaderValues->put(ContentSecurityPolicy,s);
}

HttpHeaderContentSecurityPolicy _HttpHeader::getSecurityPolicy() {
    return Cast<HttpHeaderContentSecurityPolicy>(mHeaderValues->get(ContentSecurityPolicy));
}

void _HttpHeader::setSecurityPolicyReportOnly(HttpHeaderContentSecurityPolicy s) {
    mHeaderValues->put(ContentSecurityPolicyReportOnly,s);
}

HttpHeaderContentSecurityPolicy _HttpHeader::getSecurityPolicyReportOnly() {
    return Cast<HttpHeaderContentSecurityPolicy>(mHeaderValues->get(ContentSecurityPolicyReportOnly));
}

HttpHeaderCrossOriginEmbedderPolicy _HttpHeader::getCrossOriginEmbedderPolicy() {
    return Cast<HttpHeaderCrossOriginEmbedderPolicy>(mHeaderValues->get(CrossOriginEmbedderPolicy));
}

void _HttpHeader::setCrossOriginEmbedderPolicy(HttpHeaderCrossOriginEmbedderPolicy s) {
    mHeaderValues->put(CrossOriginEmbedderPolicy,s);
}

HttpHeaderCrossOriginOpenerPolicy _HttpHeader::getCrossOriginOpenerPolicy() {
    return Cast<HttpHeaderCrossOriginOpenerPolicy>(mHeaderValues->get(CrossOriginOpenerPolicy));
}

void _HttpHeader::setCrossOriginOpenerPolicy(HttpHeaderCrossOriginOpenerPolicy s) {
    mHeaderValues->put(CrossOriginOpenerPolicy,s);
}

HttpHeaderCrossOriginResourcePolicy _HttpHeader::getCrossOriginResourcePolicy() {
    return Cast<HttpHeaderCrossOriginResourcePolicy>(mHeaderValues->get(CrossOriginResourcePolicy));
}

void _HttpHeader::setCrossOriginResourcePolicy(HttpHeaderCrossOriginResourcePolicy s) {
    mHeaderValues->put(CrossOriginResourcePolicy,s);
}

HttpHeaderDate _HttpHeader::getDate() {
    return Cast<HttpHeaderDate>(mHeaderValues->get(Date));
}

void _HttpHeader::setDate(HttpHeaderDate s) {
    mHeaderValues->put(Date,s);
}

HttpHeaderExpect _HttpHeader::getExpect() {
    return Cast<HttpHeaderExpect>(mHeaderValues->get(Expect));
}

void _HttpHeader::setExpect(HttpHeaderExpect s) {
    mHeaderValues->put(Expect,s);
}

HttpHeaderExpectCT _HttpHeader::getExpectCT() {
    return Cast<HttpHeaderExpectCT>(mHeaderValues->get(ExpectCT));
}

void _HttpHeader::setExpectCT(HttpHeaderExpectCT s) {
    mHeaderValues->put(ExpectCT,s);
}

HttpHeaderExpires _HttpHeader::getExpires() {
    return Cast<HttpHeaderExpires>(mHeaderValues->get(Expires));
}

void _HttpHeader::setExpires(HttpHeaderExpires s) {
    mHeaderValues->put(Expires,s);
}

HttpHeaderFrom _HttpHeader::getFrom() {
    return Cast<HttpHeaderFrom>(mHeaderValues->get(From));
}

void _HttpHeader::setFrom(HttpHeaderFrom s) {
    mHeaderValues->put(From,s);
}

HttpHeaderRange _HttpHeader::getRange() {
    return Cast<HttpHeaderRange>(mHeaderValues->get(Range));
}

void _HttpHeader::setRange(HttpHeaderRange s) {
    mHeaderValues->put(Range,s);
}

HttpHeaderReferer _HttpHeader::getReferer() {
    return Cast<HttpHeaderReferer>(mHeaderValues->get(Referer));
}

void _HttpHeader::setReferer(HttpHeaderReferer s) {
    mHeaderValues->put(Referer,s);
}

HttpHeaderReferrerPolicy _HttpHeader::getRefererPolicy() {
    return Cast<HttpHeaderReferrerPolicy>(mHeaderValues->get(RefererPolicy));
}

void _HttpHeader::setRefererPolicy(HttpHeaderReferrerPolicy s) {
    mHeaderValues->put(RefererPolicy,s);
}

HttpHeaderVary _HttpHeader::getVary() {
    return Cast<HttpHeaderVary>(mHeaderValues->get(Vary));
}

void _HttpHeader::setVary(HttpHeaderVary s) {
    mHeaderValues->put(Vary,s);
}

HttpHeaderVia _HttpHeader::getVia() {
    return Cast<HttpHeaderVia>(mHeaderValues->get(Via));
}

void _HttpHeader::setVia(HttpHeaderVia s) {
    mHeaderValues->put(Via,s);
}

HttpHeaderServer _HttpHeader::getServer() {
    return Cast<HttpHeaderServer>(mHeaderValues->get(Server));
}

void _HttpHeader::setServer(HttpHeaderServer s) {
    mHeaderValues->put(Server,s);
}

HttpHeaderWarning _HttpHeader::getWarning() {
    return Cast<HttpHeaderWarning>(mHeaderValues->get(Warning));
}

void _HttpHeader::setWarning(HttpHeaderWarning s) {
    mHeaderValues->put(Warning,s);
}

HttpHeaderAcceptCh _HttpHeader::getAcceptCh() {
    return Cast<HttpHeaderAcceptCh>(mHeaderValues->get(AcceptCh));
}

void _HttpHeader::setAcceptCh(HttpHeaderAcceptCh s) {
    mHeaderValues->put(AcceptCh,s);
}

HttpHeaderDnt _HttpHeader::getDnt() {
    return Cast<HttpHeaderDnt>(mHeaderValues->get(DNT));
}

void _HttpHeader::setDnt(HttpHeaderDnt s) {
    mHeaderValues->put(DNT,s);
}

HttpHeaderSaveData _HttpHeader::getSaveData() {
    return Cast<HttpHeaderSaveData>(mHeaderValues->get(SaveData));
}

void _HttpHeader::setSaveData(HttpHeaderSaveData s) {
    mHeaderValues->put(SaveData,s);
}

HttpHeaderSecFetchDest _HttpHeader::getSecFetchDest() {
    return Cast<HttpHeaderSecFetchDest>(mHeaderValues->get(SecFetchDest));
}

void _HttpHeader::setSecFetchDest(HttpHeaderSecFetchDest s) {
    mHeaderValues->put(SecFetchDest,s);
}

HttpHeaderSecFetchMode _HttpHeader::getSecFetchMode() {
    return Cast<HttpHeaderSecFetchMode>(mHeaderValues->get(SecFetchMode));
}

void _HttpHeader::setSecFetchMode(HttpHeaderSecFetchMode s) {
    mHeaderValues->put(SecFetchMode,s);
}

HttpHeaderSecFetchSite _HttpHeader::getSecFetchSite() {
    return Cast<HttpHeaderSecFetchSite>(mHeaderValues->get(SecFetchSite));
}

void _HttpHeader::setSecFetchSite(HttpHeaderSecFetchSite s) {
    mHeaderValues->put(SecFetchSite,s);
}

HttpHeaderSecFetchUser _HttpHeader::getSecFetchUser() {
    return Cast<HttpHeaderSecFetchUser>(mHeaderValues->get(SecFetchUser));
}

void _HttpHeader::setSecFetchUser(HttpHeaderSecFetchUser s) {
    mHeaderValues->put(SecFetchUser,s);
}

HttpHeaderSourceMap _HttpHeader::getSourceMap() {
    return Cast<HttpHeaderSourceMap>(mHeaderValues->get(SourceMap));
}

void _HttpHeader::setSourceMap(HttpHeaderSourceMap s) {
    mHeaderValues->put(SourceMap,s);
}

HttpHeaderServerTiming _HttpHeader::getServerTiming() {
    return Cast<HttpHeaderServerTiming>(mHeaderValues->get(ServerTiming));
}

void _HttpHeader::setServerTiming(HttpHeaderServerTiming s) {
    mHeaderValues->put(ServerTiming,s);
}


int _HttpHeader::findId(String s) {
    Integer v = idMaps->get(s->toLowerCase());
    return (v == nullptr)?-1:v->toValue();
}

String _HttpHeader::findName(int id) {
    return names->get(id);
}

String _HttpHeader::toString(int type) {
    //create method method.......
    StringBuffer header = createStringBuffer();

    switch(type) {
        case st(HttpPacket)::Request: {
            header->append(st(HttpMethod)::toString(mMethod),st(HttpText)::ContentSpace);
            header->append(createString("/"));
            if (mUrl != nullptr) {
                auto path = mUrl->getPath();
                if(path != nullptr) {
                    header->append(path);
                }
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
    }
    
    ForEveryOne(pair,mHeaderValues) {
        auto key = pair->getKey();
        if(key->equals(Version) || key->equals(Status)) {
            continue;
        } else if(key->equals(Link)) {
            auto links = Cast<ArrayList<HttpHeaderLink>>(pair->getValue());
            if(links != nullptr && links->size() != 0) {
                auto linkIterator = links->getIterator();
                while(linkIterator->hasValue()) {
                    header->append(st(HttpHeader)::Link,": ",linkIterator->getValue()->toString(),st(HttpText)::CRLF);
                    linkIterator->next();
                }
            }
        }else if(key->equals(CacheControl)) {
            String value = Cast<HttpHeaderCacheControl>(pair->getValue())->toString(mType);
            if(value != nullptr) {
                header->append(key, ": ",value,st(HttpText)::CRLF);
            }
        } else {
            header->append(key, ": ",pair->getValue()->toString(),st(HttpText)::CRLF);
        }
    }
    
    ForEveryOne(cookie,mCookies) {
        switch(type) {
            case st(HttpPacket)::Request:
                header->append(st(HttpHeader)::Cookie,": ",cookie->toString(type), st(HttpText)::CRLF);
            break;

            case st(HttpPacket)::Response:
                header->append(st(HttpHeader)::SetCookie,": ",cookie->toString(type), st(HttpText)::CRLF);
            break;
        }
    }

    return (header->size() == 0)?nullptr:header->toString(0, header->size() - 2);
}

MapIterator<String,Object> _HttpHeader::getIterator() {
    return mHeaderValues->getIterator();
}

} // namespace obotcha
