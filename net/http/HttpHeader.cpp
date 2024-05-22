#include "HttpHeader.hpp"
#include "HttpPacket.hpp"
#include "HttpText.hpp"
#include "HttpCookieParser.hpp"
#include "HttpMethod.hpp"
#include "HttpStatus.hpp"
#include "Log.hpp"
#include "IllegalArgumentException.hpp"
#include "StringBuffer.hpp"
#include "ForEveryOne.hpp"
#include "Inspect.hpp"

namespace obotcha {

HashMap<String,Integer> _HttpHeader::idMaps = HashMap<String,Integer>::New();
ArrayList<String> _HttpHeader::names = ArrayList<String>::New();

const String _HttpHeader::Method = String::New(":method");
const String _HttpHeader::Path = String::New(":path");
const String _HttpHeader::Scheme = String::New(":scheme");
const String _HttpHeader::Status = String::New(":status");
const String _HttpHeader::Protocol = String::New(":protocol");
const String _HttpHeader::Accept = String::New("accept");
const String _HttpHeader::AcceptCh = String::New("accept-ch");
const String _HttpHeader::AcceptPatch = String::New("accept-patch");
const String _HttpHeader::AcceptCharset = String::New("accept-charset");
const String _HttpHeader::AcceptDatetime = String::New("accept-datetime");
const String _HttpHeader::AcceptEncoding = String::New("accept-encoding");
const String _HttpHeader::AcceptLanguage = String::New("accept-language");
const String _HttpHeader::AcceptRanges = String::New("accept-ranges");
const String _HttpHeader::AccessControlAllowCredentials = String::New("access-control-allow-credentials");
const String _HttpHeader::AccessControlAllowHeaders = String::New("access-control-allow-headers");
const String _HttpHeader::AccessControlAllowMethods = String::New("access-control-allow-methods");
const String _HttpHeader::AccessControlAllowOrigin = String::New("access-control-allow-origin");
const String _HttpHeader::AccessControlExposeHeaders = String::New("access-control-expose-headers");
const String _HttpHeader::AccessControlMaxAge = String::New("access-control-max-age");
const String _HttpHeader::AccessControlRequestHeaders = String::New("access-control-request-headers");
const String _HttpHeader::AccessControlRequestMethod = String::New("access-control-request-method");
const String _HttpHeader::Age = String::New("age");
const String _HttpHeader::Allow = String::New("allow");
const String _HttpHeader::AltSvc = String::New("alt-svc");
const String _HttpHeader::Authorization = String::New("authorization");
const String _HttpHeader::CacheControl = String::New("cache-control");
const String _HttpHeader::Connection = String::New("connection");
const String _HttpHeader::ContentDisposition = String::New("content-disposition");
const String _HttpHeader::ContentEncoding = String::New("content-encoding");
const String _HttpHeader::ContentLanguage = String::New("content-language");
const String _HttpHeader::ContentLength = String::New("content-length");
const String _HttpHeader::ContentLocation = String::New("content-location");
const String _HttpHeader::ContentMD5 = String::New("content-md5");
const String _HttpHeader::ContentRange = String::New("content-range");
const String _HttpHeader::ContentSecurityPolicyReportOnly = String::New("content-security-policy-report-only");
const String _HttpHeader::ContentSecurityPolicy = String::New("content-security-policy");
const String _HttpHeader::ContentType = String::New("content-type");
const String _HttpHeader::Cookie = String::New("cookie");
const String _HttpHeader::CrossOriginEmbedderPolicy = String::New("cross-origin-embedder-policy");
const String _HttpHeader::CrossOriginOpenerPolicy = String::New("cross-origin-opener-policy");
const String _HttpHeader::CrossOriginResourcePolicy = String::New("cross-origin-resource-policy");
const String _HttpHeader::DNT = String::New("dnt");
const String _HttpHeader::Date = String::New("date");
const String _HttpHeader::ETag = String::New("etag");
const String _HttpHeader::Expect = String::New("expect");
const String _HttpHeader::ExpectCT = String::New("expect-ct");
const String _HttpHeader::Expires = String::New("expires");
const String _HttpHeader::From = String::New("from");
const String _HttpHeader::FrontEndHttps = String::New("front-end-https");
const String _HttpHeader::Host = String::New("host");
const String _HttpHeader::IfMatch = String::New("if-match");
const String _HttpHeader::IfModifiedSince = String::New("if-modified-since");
const String _HttpHeader::IfNoneMatch = String::New("if-none-match");
const String _HttpHeader::IfRange = String::New("if-range");
const String _HttpHeader::IfUnmodifiedSince = String::New("if-unmodified-since");
const String _HttpHeader::KeepAlive = String::New("keep-alive");
const String _HttpHeader::LastModified = String::New("last-modified");
const String _HttpHeader::Link = String::New("link");
const String _HttpHeader::Location = String::New("location");
const String _HttpHeader::MaxForwards = String::New("max-forwards");
const String _HttpHeader::Origin = String::New("origin");
const String _HttpHeader::P3P = String::New("psp");
const String _HttpHeader::Pragma = String::New("pragma");
const String _HttpHeader::ProxyAuthenticate = String::New("proxy-authenticate");
const String _HttpHeader::ProxyAuthorization = String::New("proxy-authorization");
const String _HttpHeader::ProxyConnection = String::New("proxy-connection");
const String _HttpHeader::Range = String::New("range");
const String _HttpHeader::Referer = String::New("referer");
const String _HttpHeader::RefererPolicy = String::New("referrer-policy");
const String _HttpHeader::Refresh = String::New("refresh");
const String _HttpHeader::RetryAfter = String::New("retry-after");
const String _HttpHeader::SecWebSocketKey = String::New("sec-websocket-key");
const String _HttpHeader::SecWebSocketAccept = String::New("sec-websocket-accept");
const String _HttpHeader::SaveData = String::New("save-data");
const String _HttpHeader::Server = String::New("server");
const String _HttpHeader::SetCookie = String::New("set-cookie");
const String _HttpHeader::SecTokenBinding = String::New("sec-token-binding");
const String _HttpHeader::SecFetchDest = String::New("sec-fetch-dest");
const String _HttpHeader::SecFetchMode = String::New("sec-fetch-mode");
const String _HttpHeader::SecFetchSite = String::New("sec-fetch-site");
const String _HttpHeader::SecFetchUser = String::New("sec-fetch-user");
const String _HttpHeader::StrictTransportSecurity = String::New("strict-transport-security");
const String _HttpHeader::TE = String::New("te");
const String _HttpHeader::Timestamp = String::New("timestamp");
const String _HttpHeader::Trailer = String::New("trailer");
const String _HttpHeader::TransferEncoding = String::New("transfer-encoding");
const String _HttpHeader::Upgrade = String::New("upgrade");
const String _HttpHeader::UserAgent = String::New("user-agent");
const String _HttpHeader::VIP = String::New("vip");
const String _HttpHeader::Vary = String::New("vary");
const String _HttpHeader::Via = String::New("via");
const String _HttpHeader::WWWAuthenticate = String::New("www-authenticate");
const String _HttpHeader::Warning = String::New("warning");
const String _HttpHeader::XAccelRedirect = String::New("x-accel-redirect");
const String _HttpHeader::XContentSecurityPolicyReportOnly = String::New("x-content-security-policy-report-only");
const String _HttpHeader::XContentTypeOptions = String::New("x-content-type-options");
const String _HttpHeader::XForwardedFor = String::New("x-forwarded-for");
const String _HttpHeader::XForwardedProto = String::New("x-forwarded-proto");
const String _HttpHeader::Forwarded = String::New("forwarded");
const String _HttpHeader::XFrameOptions = String::New("x-frame-options");
const String _HttpHeader::XPoweredBy = String::New("x-powerd-by");
const String _HttpHeader::XRealIP = String::New("x-real-ip");
const String _HttpHeader::XRequestedWith = String::New("x-requested-with");
const String _HttpHeader::XThriftProtocol = String::New("x-thrift-protocol");
const String _HttpHeader::XUACompatible = String::New("x-ua-compatible");
const String _HttpHeader::XWapProfile = String::New("x-wap-profile");
const String _HttpHeader::XXSSProtection = String::New("x-xss-protection");
const String _HttpHeader::SecWebSocketVersion = String::New("sec-websocket-version");
const String _HttpHeader::SecWebSocketExtensions = String::New("sec-websocket-extensions");
const String _HttpHeader::SecWebSocketOrigin = String::New("sec-websocket-origin");
const String _HttpHeader::SecWebSocketKey1 = String::New("sec-websocket-key1");
const String _HttpHeader::SecWebSocketKey2 = String::New("sec-websocket-key2");
const String _HttpHeader::SecWebSocketKey3 = String::New("sec-websocket-key3");
const String _HttpHeader::SecWebSocketProtocol = String::New("sec-websocket-protocol");
const String _HttpHeader::ServerTiming = String::New("server-timing");
const String _HttpHeader::SourceMap = String::New("sourcemap");
const String _HttpHeader::Digest = String::New("digest");
// Http2 authority
const String _HttpHeader::Authority = String::New(":authority");
const String _HttpHeader::ClearSiteData = String::New("clear-site-data");
const String _HttpHeader::Version = String::New("#version");

// Transfer-Encoding type
const String _HttpHeader::TransferChunked = String::New("chunked");

// Http connection
const String _HttpHeader::ConnectionClose = String::New("close");

#define INIT_HTTP_HEADER(HeaderString,HeaderType) \
    st(HttpHeader)::idMaps->put(HeaderString,Integer::New(static_cast<int>(HeaderType))); \
    st(HttpHeader)::names->add(HeaderString);

_HttpHeader::_HttpHeader(st(Net)::Protocol protocol):mProtocol(protocol) {
    static std::once_flag flag;
    std::call_once(flag, []() {
        INIT_HTTP_HEADER(Method,_HttpHeader::Id::Method)
        INIT_HTTP_HEADER(Path,_HttpHeader::Id::Path)
        INIT_HTTP_HEADER(Scheme,_HttpHeader::Id::Scheme)
        INIT_HTTP_HEADER(Status,_HttpHeader::Id::Status)
        INIT_HTTP_HEADER(Protocol,_HttpHeader::Id::Protocol)
        INIT_HTTP_HEADER(Accept,_HttpHeader::Id::Accept)
        INIT_HTTP_HEADER(AcceptCh,_HttpHeader::Id::AcceptCh)
        INIT_HTTP_HEADER(AcceptCharset,_HttpHeader::Id::AcceptCharset)
        INIT_HTTP_HEADER(AcceptPatch,_HttpHeader::Id::AcceptPatch)
        INIT_HTTP_HEADER(AcceptDatetime,_HttpHeader::Id::AcceptDatetime)
        INIT_HTTP_HEADER(AcceptEncoding,_HttpHeader::Id::AcceptEncoding)
        INIT_HTTP_HEADER(AcceptLanguage,_HttpHeader::Id::AcceptLanguage)
        INIT_HTTP_HEADER(AcceptRanges,_HttpHeader::Id::AcceptRanges)
        INIT_HTTP_HEADER(AccessControlAllowCredentials,_HttpHeader::Id::AccessControlAllowCredentials)
        INIT_HTTP_HEADER(AccessControlAllowHeaders,_HttpHeader::Id::AccessControlAllowHeaders)
        INIT_HTTP_HEADER(AccessControlAllowMethods,_HttpHeader::Id::AccessControlAllowMethods)
        INIT_HTTP_HEADER(AccessControlAllowOrigin,_HttpHeader::Id::AccessControlAllowOrigin)
        INIT_HTTP_HEADER(AccessControlExposeHeaders,_HttpHeader::Id::AccessControlExposeHeaders)
        INIT_HTTP_HEADER(AccessControlMaxAge,_HttpHeader::Id::AccessControlMaxAge)
        INIT_HTTP_HEADER(AccessControlRequestHeaders,_HttpHeader::Id::AccessControlRequestHeaders)
        INIT_HTTP_HEADER(AccessControlRequestMethod,_HttpHeader::Id::AccessControlRequestMethod)
        INIT_HTTP_HEADER(Age,_HttpHeader::Id::Age)
        INIT_HTTP_HEADER(Allow,_HttpHeader::Id::Allow)
        INIT_HTTP_HEADER(AltSvc,_HttpHeader::Id::AltSvc)
        INIT_HTTP_HEADER(Authorization,_HttpHeader::Id::Authorization)
        INIT_HTTP_HEADER(CacheControl,_HttpHeader::Id::CacheControl)
        INIT_HTTP_HEADER(Connection,_HttpHeader::Id::Connection)
        INIT_HTTP_HEADER(ContentDisposition,_HttpHeader::Id::ContentDisposition)
        INIT_HTTP_HEADER(ContentEncoding,_HttpHeader::Id::ContentEncoding)
        INIT_HTTP_HEADER(ContentLanguage,_HttpHeader::Id::ContentLanguage)
        INIT_HTTP_HEADER(ContentLength,_HttpHeader::Id::ContentLength)
        INIT_HTTP_HEADER(ContentLocation,_HttpHeader::Id::ContentLocation)
        INIT_HTTP_HEADER(ContentMD5,_HttpHeader::Id::ContentMD5)
        INIT_HTTP_HEADER(ContentRange,_HttpHeader::Id::ContentRange)
        INIT_HTTP_HEADER(ContentSecurityPolicyReportOnly,_HttpHeader::Id::ContentSecurityPolicyReportOnly)
        INIT_HTTP_HEADER(ContentSecurityPolicy,_HttpHeader::Id::ContentSecurityPolicy)
        INIT_HTTP_HEADER(ContentType,_HttpHeader::Id::ContentType)
        INIT_HTTP_HEADER(Cookie,_HttpHeader::Id::Cookie)
        INIT_HTTP_HEADER(CrossOriginEmbedderPolicy,_HttpHeader::Id::CrossOriginEmbedderPolicy)
        INIT_HTTP_HEADER(CrossOriginOpenerPolicy,_HttpHeader::Id::CrossOriginOpenerPolicy)
        INIT_HTTP_HEADER(CrossOriginResourcePolicy,_HttpHeader::Id::CrossOriginResourcePolicy)
        INIT_HTTP_HEADER(DNT,_HttpHeader::Id::DNT)
        INIT_HTTP_HEADER(Date,_HttpHeader::Id::Date)
        INIT_HTTP_HEADER(ETag,_HttpHeader::Id::ETag)
        INIT_HTTP_HEADER(Expect,_HttpHeader::Id::Expect)
        INIT_HTTP_HEADER(ExpectCT,_HttpHeader::Id::ExpectCT)
        INIT_HTTP_HEADER(Expires,_HttpHeader::Id::Expires)
        INIT_HTTP_HEADER(From,_HttpHeader::Id::From)
        INIT_HTTP_HEADER(FrontEndHttps,_HttpHeader::Id::FrontEndHttps)
        INIT_HTTP_HEADER(Host,_HttpHeader::Id::Host)
        INIT_HTTP_HEADER(IfMatch,_HttpHeader::Id::IfMatch)
        INIT_HTTP_HEADER(IfModifiedSince,_HttpHeader::Id::IfModifiedSince)
        INIT_HTTP_HEADER(IfNoneMatch,_HttpHeader::Id::IfNoneMatch)
        INIT_HTTP_HEADER(IfRange,_HttpHeader::Id::IfRange)
        INIT_HTTP_HEADER(IfUnmodifiedSince,_HttpHeader::Id::IfUnmodifiedSince)
        INIT_HTTP_HEADER(KeepAlive,_HttpHeader::Id::KeepAlive)
        INIT_HTTP_HEADER(LastModified,_HttpHeader::Id::LastModified)
        INIT_HTTP_HEADER(Link,_HttpHeader::Id::Link)
        INIT_HTTP_HEADER(Location,_HttpHeader::Id::Location)
        INIT_HTTP_HEADER(MaxForwards,_HttpHeader::Id::MaxForwards)
        INIT_HTTP_HEADER(Origin,_HttpHeader::Id::Origin)
        INIT_HTTP_HEADER(P3P,_HttpHeader::Id::P3P)
        INIT_HTTP_HEADER(Pragma,_HttpHeader::Id::Pragma)
        INIT_HTTP_HEADER(ProxyAuthenticate,_HttpHeader::Id::ProxyAuthenticate)
        INIT_HTTP_HEADER(ProxyAuthorization,_HttpHeader::Id::ProxyAuthorization)
        INIT_HTTP_HEADER(ProxyConnection,_HttpHeader::Id::ProxyConnection)
        INIT_HTTP_HEADER(Range,_HttpHeader::Id::Range)
        INIT_HTTP_HEADER(Referer,_HttpHeader::Id::Referer)
        INIT_HTTP_HEADER(RefererPolicy,_HttpHeader::Id::RefererPolicy)
        INIT_HTTP_HEADER(Refresh,_HttpHeader::Id::Refresh)
        INIT_HTTP_HEADER(RetryAfter,_HttpHeader::Id::RetryAfter)
        INIT_HTTP_HEADER(SaveData,_HttpHeader::Id::SaveData)
        INIT_HTTP_HEADER(SecWebSocketKey,_HttpHeader::Id::SecWebSocketKey)
        INIT_HTTP_HEADER(SecWebSocketAccept,_HttpHeader::Id::SecWebSocketAccept)
        INIT_HTTP_HEADER(Server,_HttpHeader::Id::Server)
        INIT_HTTP_HEADER(SetCookie,_HttpHeader::Id::SetCookie)
        INIT_HTTP_HEADER(SecTokenBinding,_HttpHeader::Id::SecTokenBinding)
        INIT_HTTP_HEADER(SecFetchDest,_HttpHeader::Id::SecFetchDest)
        INIT_HTTP_HEADER(SecFetchMode,_HttpHeader::Id::SecFetchMode)
        INIT_HTTP_HEADER(SecFetchSite,_HttpHeader::Id::SecFetchSite)
        INIT_HTTP_HEADER(SecFetchUser,_HttpHeader::Id::SecFetchUser)
        INIT_HTTP_HEADER(StrictTransportSecurity,_HttpHeader::Id::StrictTransportSecurity)
        INIT_HTTP_HEADER(TE,_HttpHeader::Id::TE)
        INIT_HTTP_HEADER(Timestamp,_HttpHeader::Id::Timestamp)
        INIT_HTTP_HEADER(Trailer,_HttpHeader::Id::Trailer)
        INIT_HTTP_HEADER(TransferEncoding,_HttpHeader::Id::TransferEncoding)
        INIT_HTTP_HEADER(Upgrade,_HttpHeader::Id::Upgrade)
        INIT_HTTP_HEADER(UserAgent,_HttpHeader::Id::UserAgent)
        INIT_HTTP_HEADER(VIP,_HttpHeader::Id::VIP)
        INIT_HTTP_HEADER(Vary,_HttpHeader::Id::Vary)
        INIT_HTTP_HEADER(Via,_HttpHeader::Id::Via)
        INIT_HTTP_HEADER(WWWAuthenticate,_HttpHeader::Id::WWWAuthenticate)
        INIT_HTTP_HEADER(Warning,_HttpHeader::Id::Warning)
        INIT_HTTP_HEADER(XAccelRedirect,_HttpHeader::Id::XAccelRedirect)
        INIT_HTTP_HEADER(XContentSecurityPolicyReportOnly,_HttpHeader::Id::XContentSecurityPolicyReportOnly)
        INIT_HTTP_HEADER(XContentTypeOptions,_HttpHeader::Id::XContentTypeOptions)
        INIT_HTTP_HEADER(XForwardedFor,_HttpHeader::Id::XForwardedFor)
        INIT_HTTP_HEADER(XForwardedProto,_HttpHeader::Id::XForwardedProto)
        INIT_HTTP_HEADER(Forwarded,_HttpHeader::Id::Forwarded)
        INIT_HTTP_HEADER(XFrameOptions,_HttpHeader::Id::XFrameOptions)
        INIT_HTTP_HEADER(XPoweredBy,_HttpHeader::Id::XPoweredBy)
        INIT_HTTP_HEADER(XRealIP,_HttpHeader::Id::XRealIP)
        INIT_HTTP_HEADER(XRequestedWith,_HttpHeader::Id::XRequestedWith)
        INIT_HTTP_HEADER(XThriftProtocol,_HttpHeader::Id::XThriftProtocol)
        INIT_HTTP_HEADER(XUACompatible,_HttpHeader::Id::XUACompatible)
        INIT_HTTP_HEADER(XWapProfile,_HttpHeader::Id::XWapProfile)
        INIT_HTTP_HEADER(XXSSProtection,_HttpHeader::Id::XXSSProtection)
        INIT_HTTP_HEADER(SecWebSocketVersion,_HttpHeader::Id::SecWebSocketVersion)
        INIT_HTTP_HEADER(SecWebSocketExtensions,_HttpHeader::Id::SecWebSocketExtensions)
        INIT_HTTP_HEADER(SecWebSocketOrigin,_HttpHeader::Id::SecWebSocketOrigin)
        INIT_HTTP_HEADER(SecWebSocketKey1,_HttpHeader::Id::SecWebSocketKey1)
        INIT_HTTP_HEADER(SecWebSocketKey2,_HttpHeader::Id::SecWebSocketKey2)
        INIT_HTTP_HEADER(SecWebSocketKey3,_HttpHeader::Id::SecWebSocketKey3)
        INIT_HTTP_HEADER(SecWebSocketProtocol,_HttpHeader::Id::SecWebSocketProtocol)
        INIT_HTTP_HEADER(ServerTiming,_HttpHeader::Id::ServerTiming)
        INIT_HTTP_HEADER(SourceMap,_HttpHeader::Id::SourceMap)
        INIT_HTTP_HEADER(Digest,_HttpHeader::Id::Digest)
        INIT_HTTP_HEADER(Authority,_HttpHeader::Id::Authority)
        INIT_HTTP_HEADER(ClearSiteData,_HttpHeader::Id::ClearSiteData)
        INIT_HTTP_HEADER(Version,_HttpHeader::Id::Version)
    });
    reset();
}
#undef INIT_HTTP_HEADER

void _HttpHeader::append(sp<_HttpHeader> h) {
    ForEveryOne(pairCookie,h->mCookies) {
        mCookies->add(pairCookie);
    }

    mHeaderValues->append(h->mHeaderValues);
}

void _HttpHeader::reset() {
    mCookies->clear();
    mHeaderValues->clear();
    
    setVersion(HttpHeaderVersion::New());
    mMethod = st(HttpMethod)::Id::Err;
    mResponseReason = nullptr;
    mResponseStatus = st(HttpStatus)::Ok;

    mType = st(Http)::PacketType::Request;
}

void _HttpHeader::set(String key, String value) {
    if(Integer id = idMaps->get(key->toLowerCase());id != nullptr) {
        auto type = static_cast<_HttpHeader::Id>(id->toValue());
        switch(type) {
            case _HttpHeader::Id::Authority: {
                setAuthority(value);
                return;
            }

            case _HttpHeader::Id::Path: {
                mUrl = HttpUrl::New();
                mUrl->load(value);
                return;
            }

            case _HttpHeader::Id::Method: {
                mMethod = st(HttpMethod)::ToId(value);
                return;
            }

            case _HttpHeader::Id::Scheme: {
                //TODO
                return;
            }

            case _HttpHeader::Id::Status: {
                mResponseStatus = value->toBasicInt();
                return;
            }

            case _HttpHeader::Id::Protocol: {
                //TODO
                return;
            }
            
            case _HttpHeader::Id::AcceptCharset:{
                auto v = HttpHeaderAcceptCharSet::New();
                v->load(value);
                setAcceptCharSet(v);
                return;
            }

            case _HttpHeader::Id::AcceptCh: {
                auto v = HttpHeaderAcceptCh::New();
                v->load(value);
                setAcceptCh(v);
                return;
            }

            case _HttpHeader::Id::Accept:{
                auto v = HttpHeaderAccept::New();
                v->load(value);
                setAccept(v);
                return;
            }

            case _HttpHeader::Id::AcceptEncoding:{
                auto v = HttpHeaderAcceptEncoding::New();
                v->load(value);
                setAcceptEncoding(v);
                return;
            }

            case _HttpHeader::Id::AcceptLanguage: {
                auto v = HttpHeaderAcceptLanguage::New();
                v->load(value);
                setAcceptLanguage(v);
                return;
            }

            case _HttpHeader::Id::TransferEncoding: {
                auto v = HttpHeaderTransferEncoding::New();
                v->load(value);
                setTransferEncoding(v);
                return;
            }

            case _HttpHeader::Id::AcceptPatch: {
                auto v = HttpHeaderAcceptPatch::New();
                v->load(value);
                setAcceptPatch(v);
                return;
            }

            case _HttpHeader::Id::Version: {
                auto v = HttpHeaderVersion::New();
                v->load(value);
                setVersion(v);
                return;
            }

            case _HttpHeader::Id::AccessControlAllowCredentials: {
                auto v = HttpHeaderAccessControlAllowCredentials::New();
                v->load(value);
                setAllowCredentials(v);
                return;
            }

            case _HttpHeader::Id::AccessControlAllowHeaders: {
                auto v = HttpHeaderAccessControlAllowHeaders::New();
                v->load(value);
                setAllowHeaders(v);
                return;
            }

            case _HttpHeader::Id::AccessControlAllowMethods: {
                auto v = HttpHeaderAccessControlAllowMethods::New();
                v->load(value);
                setAllowMethods(v);
                return;
            }

            case _HttpHeader::Id::AccessControlAllowOrigin: {
                auto v = HttpHeaderAccessControlAllowOrigin::New();
                v->load(value);
                setAllowOrigin(v);
                return;
            }

            case _HttpHeader::Id::AccessControlExposeHeaders: {
                auto v = HttpHeaderAccessControlExposeHeaders::New();
                v->load(value);
                setExposeHeaders(v);
                return;
            }
            
            case _HttpHeader::Id::AccessControlMaxAge: {
                auto v = HttpHeaderAccessControlMaxAge::New();
                v->load(value);
                setMaxAge(v);
                return;
            }

            case _HttpHeader::Id::AccessControlRequestHeaders: {
                auto v = HttpHeaderAccessControlRequestHeaders::New();
                v->load(value);
                setAccessControlReqeuestHeaders(v);
                return;
            }

            case _HttpHeader::Id::AccessControlRequestMethod: {
                auto v = HttpHeaderAccessControlRequestMethod::New();
                v->load(value);
                setAccessControlRequestMethod(v);
                return;
            }

            case _HttpHeader::Id::Age: {
                auto v = HttpHeaderAge::New();
                v->load(value);
                setAge(v);
                return;
            }

            case _HttpHeader::Id::Allow: {
                auto v = HttpHeaderAllow::New();
                v->load(value);
                setAllow(v);
                return;
            }

            case _HttpHeader::Id::Authorization: {
                auto v= HttpHeaderAuthorization::New();
                v->load(value);
                setAuthorization(v);
                return;
            }
            
            case _HttpHeader::Id::CacheControl: {
                auto v = HttpHeaderCacheControl::New();
                v->load(value);
                setCacheControl(v);
                return;
            }

            case _HttpHeader::Id::ClearSiteData: {
                auto v = HttpHeaderClearSiteData::New();
                v->load(value);
                setClearSiteData(v);
                return;
            }

            case _HttpHeader::Id::ContentDisposition: {
                auto v = HttpHeaderContentDisposition::New();
                v->load(value);
                setContentDisposition(v);
                return;
            }

            case _HttpHeader::Id::ContentEncoding: {
                auto v = HttpHeaderContentEncoding::New();
                v->load(value);
                setContentEncoding(v);
                return;
            }

            case _HttpHeader::Id::ContentLanguage: {
                auto v = HttpHeaderContentLanguage::New();
                v->load(value);
                setContentLanguage(v);
                return;
            }

            case _HttpHeader::Id::ContentLength: {
                auto v = HttpHeaderContentLength::New();
                v->load(value);
                setContentLength(v);
                return;
            }

            case _HttpHeader::Id::ContentLocation: {
                auto v = HttpHeaderContentLocation::New();
                v->load(value);
                setContentLocation(v);
                return;
            }

            case _HttpHeader::Id::ContentType: {
                auto v = HttpHeaderContentType::New();
                v->load(value);
                setContentType(v);
                return;
            }

            case _HttpHeader::Id::Forwarded: {
                auto v = HttpHeaderForwarded::New();
                v->load(value);
                setForwarded(v);
                return;
            }

            case _HttpHeader::Id::Connection: {
                auto v = HttpHeaderConnection::New();
                v->load(value);
                setConnection(v);
                return;
            }

            case _HttpHeader::Id::Digest: {
                auto v = HttpHeaderDigest::New();
                v->load(value);
                setDigest(v);
                return;
            }

            case _HttpHeader::Id::Host: {
                auto v = HttpHeaderHost::New();
                v->load(value);
                setHost(v);
                return;
            }

            case _HttpHeader::Id::KeepAlive: {
                auto v = HttpHeaderKeepAlive::New();
                v->load(value);
                setKeepAlive(v);
                return;
            }

            case _HttpHeader::Id::Link: {
                auto v = HttpHeaderLink::New(value);
                addLink(v);
                return;
            }

            case _HttpHeader::Id::IfMatch: {
                auto v = HttpHeaderMatch::New();
                v->load(value);
                setIfMatch(v);
                return;
            }

            case _HttpHeader::Id::IfNoneMatch: {
                auto v = HttpHeaderMatch::New();
                v->load(value);
                setIfNoneMatch(v);
                return;
            }

            case _HttpHeader::Id::RetryAfter: {
                auto v = HttpHeaderRetryAfter::New();
                v->load(value);
                setRetryAfter(v);
                return;
            }

            case _HttpHeader::Id::UserAgent: {
                auto v = HttpHeaderUserAgent::New();
                v->load(value);
                setUserAgent(v);
                return;
            }
            
            case _HttpHeader::Id::IfModifiedSince: {
                auto v = HttpHeaderIfModifiedSince::New();
                v->load(value);
                setIfModifiedSince(v);
                return;
            }

            case _HttpHeader::Id::IfRange: {
                auto v = HttpHeaderIfRange::New();
                v->load(value);
                setIfRange(v);
                return;
            }

            case _HttpHeader::Id::IfUnmodifiedSince: {
                auto v = HttpHeaderIfUnmodifiedSince::New();
                v->load(value);
                setIfUnmodifiedSince(v);
                return;
            }

            case _HttpHeader::Id::ProxyAuthenticate: {
                auto v = HttpHeaderProxyAuthenticate::New();
                v->load(value);
                setProxyAuthenticate(v);
                return;
            }

            case _HttpHeader::Id::ProxyAuthorization: {
                auto v = HttpHeaderProxyAuthorization::New();
                v->load(value);
                setProxyAuthorization(v);
                return;
            }
            
            case _HttpHeader::Id::StrictTransportSecurity: {
                auto v = HttpHeaderStrictTransportSecurity::New();
                v->load(value);
                setStrictTransportSecurity(v);
                return;
            }

            case _HttpHeader::Id::XFrameOptions: {
                auto v = HttpHeaderXFrameOptions::New();
                v->load(value);
                setXFrameOptions(v);
                return;
            }

            case _HttpHeader::Id::Upgrade: {
                auto v = HttpHeaderUpgrade::New();
                v->load(value);
                setUpgrade(v);
                return;
            }

            case _HttpHeader::Id::Cookie:
            case _HttpHeader::Id::SetCookie: {
                auto c = st(HttpCookieParser)::parse(value);
                if(mCookies == nullptr) {
                    mCookies = c;
                } else {
                    mCookies->add(c);
                }
                return;
            }

            case _HttpHeader::Id::SecWebSocketAccept: {
                auto v = HttpHeaderSecWebSocketAccept::New();
                v->load(value);
                setWebSocketAccept(v);
                return;
            }

            case _HttpHeader::Id::SecWebSocketKey: {
                auto v = HttpHeaderSecWebSocketKey::New();
                v->load(value);
                setWebSocketKey(v);
                return;
            }

            case _HttpHeader::Id::SecWebSocketVersion: {
                auto v = HttpHeaderSecWebSocketVersion::New();
                v->load(value);
                setWebSocketVersion(v);
                return;
            }

            case _HttpHeader::Id::ETag: {
                auto v = HttpHeaderETag::New();
                v->load(value);
                setETag(v);
                return;
            }

            case _HttpHeader::Id::XXSSProtection: {
                auto v = HttpHeaderXXssProtection::New();
                v->load(value);
                setXXssProtection(v);
                return;
            }

            case _HttpHeader::Id::LastModified: {
                auto v = HttpHeaderLastModified::New();
                v->load(value);
                setLastModified(v);
                return;
            }

            case _HttpHeader::Id::SecWebSocketExtensions: {
                auto v = HttpHeaderSecWebSocketExtensions::New();
                v->load(value);
                setWebSocketExtensions(v);
                return;
            }

            case _HttpHeader::Id::SecWebSocketOrigin: {
                auto v = HttpHeaderSecWebSocketOrigin::New();
                v->load(value);
                setWebSocketOrigin(v);
                return;
            }

            case _HttpHeader::Id::SecWebSocketKey1: {
                auto v = HttpHeaderSecWebSocketKey::New();
                v->load(value);
                setWebSocketKey1(v);
                return;
            }

            case _HttpHeader::Id::SecWebSocketKey2: {
                auto v = HttpHeaderSecWebSocketKey::New();
                v->load(value);
                setWebSocketKey2(v);
                return;
            }

            case _HttpHeader::Id::SecWebSocketKey3: {
                auto v = HttpHeaderSecWebSocketKey::New();
                v->load(value);
                setWebSocketKey3(v);
                return;
            }

            case _HttpHeader::Id::SecWebSocketProtocol: {
                auto v = HttpHeaderSecWebSocketProtocol::New();
                v->load(value);
                setWebSocketProtocol(v);
                return;
            }

            case _HttpHeader::Id::Origin: {
                auto v = HttpHeaderOrigin::New();
                v->load(value);
                setOrigin(v);
                return;
            }

            case _HttpHeader::Id::Pragma: {
                auto v = HttpHeaderPragma::New();
                v->load(value);
                setPragma(v);
                return;
            }

            case _HttpHeader::Id::AcceptRanges: {
                auto v = HttpHeaderAcceptRanges::New();
                v->load(value);
                setHttpHeaderAcceptRanges(v);
                return;
            }

            case _HttpHeader::Id::AltSvc: {
                auto v = HttpHeaderAltSvc::New();
                v->load(value);
                setAltSvc(v);
                return;
            }

            case _HttpHeader::Id::ContentRange: {
                auto v = HttpHeaderContentRange::New();
                v->load(value);
                setContentRange(v);
                return;
            }

            case _HttpHeader::Id::ContentSecurityPolicy: {
                auto v = HttpHeaderContentSecurityPolicy::New();
                v->load(value);
                setSecurityPolicy(v);
                return;
            }

            case _HttpHeader::Id::ContentSecurityPolicyReportOnly: {
                auto v = HttpHeaderContentSecurityPolicy::New();
                v->load(value);
                setSecurityPolicyReportOnly(v);
                return;
            }

            case _HttpHeader::Id::CrossOriginEmbedderPolicy: {
                auto v = HttpHeaderCrossOriginEmbedderPolicy::New();
                v->load(value);
                setCrossOriginEmbedderPolicy(v);
                return;
            }

            case _HttpHeader::Id::CrossOriginOpenerPolicy: {
                auto v = HttpHeaderCrossOriginOpenerPolicy::New();
                v->load(value);
                setCrossOriginOpenerPolicy(v);
                return;
            }

            case _HttpHeader::Id::CrossOriginResourcePolicy: {
                auto v = HttpHeaderCrossOriginResourcePolicy::New();
                v->load(value);
                setCrossOriginResourcePolicy(v);
                return;
            }

            case _HttpHeader::Id::Date: {
                auto v = HttpHeaderDate::New();
                v->load(value);
                setDate(v);
                return;
            }

            case _HttpHeader::Id::Expect: {
                auto v = HttpHeaderExpect::New();
                v->load(value);
                setExpect(v);
                return;
            }

            case _HttpHeader::Id::ExpectCT: {
                auto v = HttpHeaderExpectCT::New();
                v->load(value);
                setExpectCT(v);
                return;
            }

            case _HttpHeader::Id::Expires: {
                auto v = HttpHeaderExpires::New();
                v->load(value);
                setExpires(v);
                return;
            }

            case _HttpHeader::Id::From: {
                auto v = HttpHeaderFrom::New();
                v->load(value);
                setFrom(v);
                return;
            }

            case _HttpHeader::Id::Range: {
                auto v = HttpHeaderRange::New();
                v->load(value);
                setRange(v);
                return;
            }

            case _HttpHeader::Id::Referer: {
                auto v = HttpHeaderReferer::New();
                v->load(value);
                setReferer(v);
                return;
            }

            case _HttpHeader::Id::RefererPolicy: {
                auto v = HttpHeaderReferrerPolicy::New();
                v->load(value);
                setRefererPolicy(v);
                return;
            }

            case _HttpHeader::Id::Vary: {
                auto v = HttpHeaderVary::New();
                v->load(value);
                setVary(v);
                return;
            }

            case _HttpHeader::Id::Via: {
                auto v = HttpHeaderVia::New();
                v->load(value);
                setVia(v);
                return;
            }

            case _HttpHeader::Id::Server: {
                auto v = HttpHeaderServer::New();
                v->load(value);
                setServer(v);
                return;
            }

            case _HttpHeader::Id::Warning: {
                auto v = HttpHeaderWarning::New();
                v->load(value);
                setWarning(v);
                return;
            }

            case _HttpHeader::Id::DNT: {
                auto v = HttpHeaderDnt::New();
                v->load(value);
                setDnt(v);
                return;
            }

            case _HttpHeader::Id::SaveData: {
                auto v = HttpHeaderSaveData::New();
                v->load(value);
                setSaveData(v);
                return;
            }

            case _HttpHeader::Id::SecFetchDest: {
                auto v = HttpHeaderSecFetchDest::New();
                v->load(value);
                setSecFetchDest(v);
                return;
            }

            case _HttpHeader::Id::SecFetchMode: {
                auto v = HttpHeaderSecFetchMode::New();
                v->load(value);
                setSecFetchMode(v);
                return;
            }

            case _HttpHeader::Id::SecFetchSite: {
                auto v = HttpHeaderSecFetchSite::New();
                v->load(value);
                setSecFetchSite(v);
                return;
            }

            case _HttpHeader::Id::SecFetchUser: {
                auto v = HttpHeaderSecFetchUser::New();
                v->load(value);
                setSecFetchUser(v);
                return;
            }

            case _HttpHeader::Id::ServerTiming: {
                auto v = HttpHeaderServerTiming::New();
                v->load(value);
                setServerTiming(v);
                return;
            }

            case _HttpHeader::Id::SourceMap: {
                auto v = HttpHeaderSourceMap::New();
                v->load(value);
                setSourceMap(v);
                return;
            }

            default:{
                LOG(ERROR)<<"HttpHeader set unknown id"<<id->toValue()<<"name is "<<findName(type)->toChars();
            } break;
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

size_t _HttpHeader::size() { 
    return mHeaderValues->size(); 
}

st(HttpMethod)::Id _HttpHeader::getMethod() const { 
    return mMethod; 
}

void _HttpHeader::setMethod(st(HttpMethod)::Id v) { 
    mMethod = v; 
}

HttpUrl _HttpHeader::getUrl() { 
    return mUrl; 
}

void _HttpHeader::setUrl(HttpUrl u) { 
    mUrl = u; 
}

int _HttpHeader::getResponseStatus() const { 
    return mResponseStatus; 
}

void _HttpHeader::setResponseStatus(int s) { 
    mResponseStatus = s;
}

String _HttpHeader::getResponseReason() const { 
    return mResponseReason; 
}

bool _HttpHeader::setResponseReason(String s) { 
    Inspect(!st(HttpStatus)::isValid(s),false)
    mResponseReason = s; 
    return true;
}

st(Http)::PacketType _HttpHeader::getType() const { 
    return mType; 
}

void _HttpHeader::setType(st(Http)::PacketType v) { 
    mType = v; 
}

st(Net)::Protocol _HttpHeader::getProtocol() const {
    return mProtocol;
}

void _HttpHeader::setProtocol(st(Net)::Protocol protocol) {
    mProtocol = protocol;
}

void _HttpHeader::addCookie(HttpCookie c) { 
    mCookies->add(c); 
}

ArrayList<HttpCookie> _HttpHeader::getCookies() { 
    return mCookies; 
}

//Authority
String _HttpHeader::getAuthority() const {
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
        links = ArrayList<HttpHeaderLink>::New();
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

HttpHeaderETag _HttpHeader::getETag() {
    return Cast<HttpHeaderETag>(mHeaderValues->get(ETag));
}

void _HttpHeader::setETag(HttpHeaderETag tag) {
    mHeaderValues->put(ETag,tag);
}

HttpHeaderXXssProtection _HttpHeader::getXXssProtection() {
    return Cast<HttpHeaderXXssProtection>(mHeaderValues->get(XXSSProtection));
}

void _HttpHeader::setXXssProtection(HttpHeaderXXssProtection v) {
    mHeaderValues->put(XXSSProtection,v);
}

HttpHeaderLastModified _HttpHeader::getLastModified() {
    return Cast<HttpHeaderLastModified>(mHeaderValues->get(LastModified));
}

void _HttpHeader::setLastModified(HttpHeaderLastModified modified_time) {
    mHeaderValues->put(LastModified,modified_time);
}

HttpHeaderServerTiming _HttpHeader::getServerTiming() {
    return Cast<HttpHeaderServerTiming>(mHeaderValues->get(ServerTiming));
}

void _HttpHeader::setServerTiming(HttpHeaderServerTiming s) {
    mHeaderValues->put(ServerTiming,s);
}


_HttpHeader::Id _HttpHeader::findId(String s) {
    Integer v = idMaps->get(s->toLowerCase());
    return (v == nullptr)?_HttpHeader::Id::Err:
                         static_cast<_HttpHeader::Id>(v->toValue());
}

String _HttpHeader::findName(_HttpHeader::Id id) {
    return names->get(static_cast<int>(id));
}

String _HttpHeader::toString(st(Http)::PacketType type) {
    //create method method.......
    StringBuffer header = StringBuffer::New();

    switch(type) {
        case st(Http)::PacketType::Request: {
            header->append(st(HttpMethod)::ToString(mMethod),st(HttpText)::ContentSpace);
            header->append(String::New("/"));
            if (mUrl != nullptr) {
                auto path = mUrl->getPath();
                if(path != nullptr) {
                    header->append(path);
                }
            }
            header->append(st(HttpText)::ContentSpace,getVersion()->toString(),st(HttpText)::CRLF);
            break;
        }

        case st(Http)::PacketType::Response: {
            header->append(getVersion()->toString(),st(HttpText)::ContentSpace,String::New(mResponseStatus));
            if (mResponseReason != nullptr) {
                header->append(st(HttpText)::ContentSpace,mResponseReason,st(HttpText)::CRLF);
            } else {
                header->append(st(HttpText)::ContentSpace,st(HttpStatus)::toString(mResponseStatus),st(HttpText)::CRLF);
            }
            break;
        }

        default:
            Trigger(IllegalArgumentException,"no support")
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
            case st(Http)::PacketType::Request:
                header->append(st(HttpHeader)::Cookie,": ",cookie->toString(type), st(HttpText)::CRLF);
            break;

            case st(Http)::PacketType::Response:
                header->append(st(HttpHeader)::SetCookie,": ",cookie->toString(type), st(HttpText)::CRLF);
            break;

            default:
                LOG(ERROR)<<"HttpHeader to string,unknow request type:"<<static_cast<int>(type);
            break;
        }
    }

    return (header->size() == 0)?nullptr:header->toString(0, header->size() - 2);
}

MapIterator<String,Object> _HttpHeader::getIterator() {
    return mHeaderValues->getIterator();
}

} // namespace obotcha
