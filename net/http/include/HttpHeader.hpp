#ifndef __OBOTCHA_HTTP_HEADER_HPP__
#define __OBOTCHA_HTTP_HEADER_HPP__

#include "Object.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "HashMap.hpp"
#include "HttpCookie.hpp"
#include "HttpHeaderCacheControl.hpp"
#include "HttpHeaderContentType.hpp"
#include "HttpHeaderVersion.hpp"
#include "HttpUrl.hpp"
#include "HttpHeaderLink.hpp"
#include "HttpHeaderAcceptEncoding.hpp"
#include "HttpHeaderAcceptLanguage.hpp"
#include "HttpHeaderAcceptCharSet.hpp"
#include "HttpHeaderAccept.hpp"
#include "HttpHeaderAcceptPatch.hpp"
#include "HttpHeaderStrictTransportSecurity.hpp"
#include "HttpHeaderProxyAuthorization.hpp"
#include "HttpHeaderProxyAuthenticate.hpp"
#include "HttpHeaderXFrameOptions.hpp"
#include "HttpHeaderForwarded.hpp"
#include "HttpHeaderContentDisposition.hpp"
#include "HttpHeaderDigest.hpp"
#include "HttpHeaderAuthorization.hpp"
#include "HttpHeaderAccessControlAllowCredentials.hpp"
#include "HttpHeaderAccessControlAllowHeaders.hpp"
#include "HttpHeaderAccessControlAllowMethods.hpp"
#include "HttpHeaderAccessControlAllowOrigin.hpp"
#include "HttpHeaderAccessControlExposeHeaders.hpp"
#include "HttpHeaderAccessControlMaxAge.hpp"
#include "HttpHeaderAccessControlRequestHeaders.hpp"
#include "HttpHeaderAccessControlRequestMethod.hpp"
#include "HttpHeaderAge.hpp"
#include "HttpHeaderAllow.hpp"
#include "HttpHeaderClearSiteData.hpp"
#include "HttpHeaderContentEncoding.hpp"
#include "HttpHeaderContentLanguage.hpp"
#include "HttpHeaderContentLength.hpp"
#include "HttpHeaderContentLocation.hpp"
#include "HttpHeaderConnection.hpp"
#include "HttpHeaderHost.hpp"
#include "HttpHeaderKeepAlive.hpp"
#include "HttpHeaderMatch.hpp"
#include "HttpHeaderRetryAfter.hpp"
#include "HttpHeaderUserAgent.hpp"
#include "HttpHeaderIfModifiedSince.hpp"
#include "HttpHeaderIfRange.hpp"
#include "HttpHeaderIfUnmodifiedSince.hpp"
#include "HttpHeaderTransferEncoding.hpp"
#include "HttpHeaderUpgrade.hpp"
#include "HttpHeaderSecWebSocketAccept.hpp" 
#include "HttpHeaderSecWebSocketKey.hpp" 
#include "HttpHeaderSecWebSocketProtocol.hpp"
#include "HttpHeaderSecWebSocketVersion.hpp"
#include "HttpHeaderSecWebSocketExtensions.hpp"
#include "HttpHeaderSecWebSocketOrigin.hpp"
#include "HttpHeaderOrigin.hpp"
#include "HttpHeaderPragma.hpp"
#include "HttpHeaderAcceptRanges.hpp"
#include "HttpHeaderAltSvc.hpp"
#include "HttpHeaderContentRange.hpp"
#include "HttpHeaderContentSecurityPolicy.hpp"
#include "HttpHeaderCrossOriginEmbedderPolicy.hpp"
#include "HttpHeaderCrossOriginOpenerPolicy.hpp"
#include "HttpHeaderCrossOriginResourcePolicy.hpp"
#include "HttpHeaderDate.hpp"
#include "HttpHeaderExpect.hpp"
#include "HttpHeaderExpectCT.hpp"
#include "HttpHeaderExpires.hpp"
#include "HttpHeaderFrom.hpp"
#include "HttpHeaderRange.hpp"
#include "HttpHeaderReferer.hpp"
#include "HttpHeaderReferrerPolicy.hpp"
#include "HttpHeaderVary.hpp"
#include "HttpHeaderVia.hpp"
#include "HttpHeaderServer.hpp"
#include "HttpHeaderWarning.hpp"
#include "HttpHeaderAcceptCh.hpp"
#include "HttpHeaderSaveData.hpp"
#include "HttpHeaderSecFetchMode.hpp"
#include "HttpHeaderSecFetchDest.hpp"
#include "HttpHeaderSecFetchSite.hpp"
#include "HttpHeaderSecFetchUser.hpp"
#include "HttpHeaderServerTiming.hpp"
#include "HttpHeaderSourceMap.hpp"
#include "HttpHeaderDnt.hpp"
#include "NetProtocol.hpp"
#include "ArrayList.hpp"
#include "Pair.hpp"
#include "HashMap.hpp"

namespace obotcha {

//reference
//https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Cross-Origin-Opener-Policy

DECLARE_CLASS(HttpHeader) {

public:
    ////-------- defination ---------////
    //http2 pseudo header
    const static String Method;
    const static String Path;
    const static String Scheme;
    const static String Status;
    const static String Protocol;

    //regular http header
    const static String Accept;
    const static String AcceptCh;
    const static String AcceptCharset;
    const static String AcceptPatch;
    const static String AcceptDatetime;
    const static String AcceptEncoding;
    const static String AcceptLanguage;
    const static String AcceptRanges;
    const static String AccessControlAllowCredentials;
    const static String AccessControlAllowHeaders;
    const static String AccessControlAllowMethods;
    const static String AccessControlAllowOrigin;
    const static String AccessControlExposeHeaders;
    const static String AccessControlMaxAge;
    const static String AccessControlRequestHeaders;
    const static String AccessControlRequestMethod;
    const static String Age;
    const static String Allow;
    const static String AltSvc;
    const static String Authorization;
    const static String CacheControl;
    const static String Connection;
    const static String ContentDisposition;
    const static String ContentEncoding;
    const static String ContentLanguage;
    const static String ContentLength;
    const static String ContentLocation;
    const static String ContentMD5;
    const static String ContentRange;
    const static String ContentSecurityPolicyReportOnly;
    const static String ContentSecurityPolicy;
    const static String ContentType;
    const static String Cookie;
    const static String CrossOriginEmbedderPolicy;
    const static String CrossOriginOpenerPolicy;
    const static String CrossOriginResourcePolicy;
    const static String DNT;
    const static String Date;
    const static String ETag;
    const static String Expect;
    const static String ExpectCT;
    const static String Expires;
    const static String From;
    const static String FrontEndHttps;
    const static String Host;
    const static String IfMatch;
    const static String IfModifiedSince;
    const static String IfNoneMatch;
    const static String IfRange;
    const static String IfUnmodifiedSince;
    const static String KeepAlive;
    const static String LastModified;
    const static String Link;
    const static String Location;
    const static String MaxForwards;
    const static String Origin;
    const static String P3P;
    const static String Pragma;
    const static String ProxyAuthenticate;
    const static String ProxyAuthorization;
    const static String ProxyConnection;
    const static String Range;
    const static String Referer;
    const static String RefererPolicy;
    const static String Refresh;
    const static String RetryAfter;
    const static String SaveData;
    const static String SecWebSocketKey;
    const static String SecWebSocketAccept;
    const static String Server;
    const static String SetCookie;
    const static String SecTokenBinding;
    const static String SecFetchDest;
    const static String SecFetchMode;
    const static String SecFetchSite;
    const static String SecFetchUser;
    const static String StrictTransportSecurity;
    const static String TE;
    const static String Timestamp;
    const static String Trailer;
    const static String TransferEncoding;
    const static String Upgrade;
    const static String UserAgent;
    const static String VIP;
    const static String Vary;
    const static String Via;
    const static String WWWAuthenticate;
    const static String Warning;
    const static String XAccelRedirect;
    const static String XContentSecurityPolicyReportOnly;
    const static String XContentTypeOptions;
    const static String XForwardedFor;
    const static String XForwardedProto;
    const static String Forwarded;
    const static String XFrameOptions;
    const static String XPoweredBy;
    const static String XRealIP;
    const static String XRequestedWith;
    const static String XThriftProtocol;
    const static String XUACompatible;
    const static String XWapProfile;
    const static String XXSSProtection;
    const static String SecWebSocketVersion;
    const static String SecWebSocketExtensions;
    const static String SecWebSocketOrigin;
    const static String SecWebSocketKey1;
    const static String SecWebSocketKey2;
    const static String SecWebSocketKey3;
    const static String SecWebSocketProtocol;
    const static String ServerTiming;
    const static String SourceMap;
    const static String Digest;
    //Transfer-Encoding type
    const static String TransferChunked;

    //http connection
    const static String ConnectionClose;

    //http2 authority
    const static String Authority;

    const static String ClearSiteData;
    const static String Version;

    enum type{
        TypeMethod = 0,
        TypePath,
        TypeScheme,
        TypeStatus,
        TypeProtocol,
        TypeAccept,
        TypeAcceptCh,
        TypeAcceptCharset,
        TypeAcceptPatch,
        TypeAcceptDatetime,
        TypeAcceptEncoding,
        TypeAcceptLanguage,
        TypeAcceptRanges,
        TypeAccessControlAllowCredentials,
        TypeAccessControlAllowHeaders,
        TypeAccessControlAllowMethods,
        TypeAccessControlAllowOrigin,
        TypeAccessControlExposeHeaders,
        TypeAccessControlMaxAge,
        TypeAccessControlRequestHeaders,
        TypeAccessControlRequestMethod,
        TypeAge,
        TypeAllow,
        TypeAltSvc,
        TypeAuthorization,
        TypeCacheControl,
        TypeConnection,
        TypeContentDisposition,
        TypeContentEncoding,
        TypeContentLanguage,
        TypeContentLength,
        TypeContentLocation,
        TypeContentMD5,
        TypeContentRange,
        TypeContentSecurityPolicyReportOnly,
        TypeContentSecurityPolicy,
        TypeContentType,
        TypeCookie,
        TypeCrossOriginEmbedderPolicy,
        TypeCrossOriginOpenerPolicy,
        TypeCrossOriginResourcePolicy,
        TypeDNT,
        TypeDate,
        TypeETag,
        TypeExpect,
        TypeExpectCT,
        TypeExpires,
        TypeFrom,
        TypeFrontEndHttps,
        TypeHost,
        TypeIfMatch,
        TypeIfModifiedSince,
        TypeIfNoneMatch,
        TypeIfRange,
        TypeIfUnmodifiedSince,
        TypeKeepAlive,
        TypeLastModified,
        TypeLink,
        TypeLocation,
        TypeMaxForwards,
        TypeOrigin,
        TypeP3P,
        TypePragma,
        TypeProxyAuthenticate,
        TypeProxyAuthorization,
        TypeProxyConnection,
        TypeRange,
        TypeReferer,
        TypeRefererPolicy,
        TypeRefresh,
        TypeRetryAfter,
        TypeSaveData,
        TypeSecWebSocketKey,
        TypeSecWebSocketAccept,
        TypeServer,
        TypeSetCookie,
        TypeSecTokenBinding,
        TypeSecFetchDest,
        TypeSecFetchMode,
        TypeSecFetchSite,
        TypeSecFetchUser,
        TypeStrictTransportSecurity,
        TypeTE,
        TypeTimestamp,
        TypeTrailer,
        TypeTransferEncoding,
        TypeUpgrade,
        TypeUserAgent,
        TypeVIP,
        TypeVary,
        TypeVia,
        TypeWWWAuthenticate,
        TypeWarning,
        TypeXAccelRedirect,
        TypeXContentSecurityPolicyReportOnly,
        TypeXContentTypeOptions,
        TypeXForwardedFor,
        TypeXForwardedProto,
        TypeForwarded,
        TypeXFrameOptions,
        TypeXPoweredBy,
        TypeXRealIP,
        TypeXRequestedWith,
        TypeXThriftProtocol,
        TypeXUACompatible,
        TypeXWapProfile,
        TypeXXSSProtection,
        TypeSecWebSocketVersion,
        TypeSecWebSocketExtensions,
        TypeSecWebSocketOrigin,
        TypeSecWebSocketKey1,
        TypeSecWebSocketKey2,
        TypeSecWebSocketKey3,
        TypeSecWebSocketProtocol,
        TypeServerTiming,
        TypeSourceMap,
        TypeDigest,
        TypeAuthority,
        //clearSite
        TypeClearSiteData,
        TypeVersion
    };

    ////-------- function -------////
    explicit _HttpHeader(int protocol = st(NetProtocol)::Http);

    void append(sp<_HttpHeader>);
    
    void reset();
    
    void set(String header,String value);
    
    String get(String);

    MapIterator<String,Object> getIterator();
    void addCookie(HttpCookie);
    ArrayList<HttpCookie> getCookies();

    HttpHeaderAcceptCharSet getAcceptCharSet();
    void setAcceptCharSet(HttpHeaderAcceptCharSet);

    HttpHeaderAccept getAccept();
    void setAccept(HttpHeaderAccept);

    HttpHeaderAcceptEncoding getAcceptEncoding();
    void setAcceptEncoding(HttpHeaderAcceptEncoding);

    HttpHeaderAcceptLanguage getAcceptLanguage();
    void setAcceptLanguage(HttpHeaderAcceptLanguage);

    HttpHeaderAcceptPatch getAcceptPatch();
    void setAcceptPatch(HttpHeaderAcceptPatch);

    HttpHeaderAccessControlAllowCredentials getAllowCredentials();
    void setAllowCredentials(HttpHeaderAccessControlAllowCredentials);

    HttpHeaderAccessControlAllowHeaders getAllowHeaders();
    void setAllowHeaders(HttpHeaderAccessControlAllowHeaders);

    HttpHeaderAccessControlAllowMethods getAllowMethods();
    void setAllowMethods(HttpHeaderAccessControlAllowMethods);

    HttpHeaderAccessControlAllowOrigin getAllowOrigin();
    void setAllowOrigin(HttpHeaderAccessControlAllowOrigin);

    HttpHeaderAccessControlExposeHeaders getExposeHeaders();
    void setExposeHeaders(HttpHeaderAccessControlExposeHeaders);

    HttpHeaderAccessControlMaxAge getMaxAge();
    void setMaxAge(HttpHeaderAccessControlMaxAge);

    HttpHeaderAccessControlRequestHeaders getAccessControlRequestHeaders();
    void setAccessControlReqeuestHeaders(HttpHeaderAccessControlRequestHeaders);

    HttpHeaderAccessControlRequestMethod getAccessControlRequestMethod();
    void setAccessControlRequestMethod(HttpHeaderAccessControlRequestMethod);

    HttpHeaderAge getAge();
    void setAge(HttpHeaderAge);

    HttpHeaderAllow getAllow();
    void setAllow(HttpHeaderAllow);

    HttpHeaderAuthorization getAuthorization();
    void setAuthorization(HttpHeaderAuthorization);

    HttpHeaderCacheControl getCacheControl();
    void setCacheControl(HttpHeaderCacheControl);

    HttpHeaderClearSiteData getClearSiteData();
    void setClearSiteData(HttpHeaderClearSiteData);

    HttpHeaderContentDisposition getContentDisposition();
    void setContentDisposition(HttpHeaderContentDisposition);

    HttpHeaderContentEncoding getContentEncoding();
    void setContentEncoding(HttpHeaderContentEncoding);

    HttpHeaderContentLanguage getContentLanguage();
    void setContentLanguage(HttpHeaderContentLanguage);

    HttpHeaderContentLength getContentLength();
    void setContentLength(HttpHeaderContentLength);

    HttpHeaderContentLocation getContentLocation();
    void setContentLocation(HttpHeaderContentLocation);

    HttpHeaderContentType getContentType();
    void setContentType(HttpHeaderContentType);

    HttpHeaderForwarded getForwarded();
    void setForwarded(HttpHeaderForwarded);

    HttpHeaderConnection getConnection();
    void setConnection(HttpHeaderConnection);

    HttpHeaderDigest getDigest();
    void setDigest(HttpHeaderDigest);

    HttpHeaderHost getHost();
    void setHost(HttpHeaderHost);

    HttpHeaderKeepAlive getKeepAlive();
    void setKeepAlive(HttpHeaderKeepAlive);

    ArrayList<HttpHeaderLink> getLinks();
    void setLinks(ArrayList<HttpHeaderLink>);
    void addLink(HttpHeaderLink);

    HttpHeaderMatch getIfMatch();
    void setIfMatch(HttpHeaderMatch);

    HttpHeaderMatch getIfNoneMatch();
    void setIfNoneMatch(HttpHeaderMatch);

    HttpHeaderRetryAfter getRetryAfter();
    void setRetryAfter(HttpHeaderRetryAfter);

    HttpHeaderUserAgent getUserAgent();
    void setUserAgent(HttpHeaderUserAgent);

    HttpHeaderIfModifiedSince getIfModifiedSince();
    void setIfModifiedSince(HttpHeaderIfModifiedSince);

    HttpHeaderIfRange getIfRange();
    void setIfRange(HttpHeaderIfRange);

    HttpHeaderIfUnmodifiedSince getIfUnmodifiedSince();
    void setIfUnmodifiedSince(HttpHeaderIfUnmodifiedSince);

    void setProxyAuthenticate(HttpHeaderProxyAuthenticate);
    HttpHeaderProxyAuthenticate getProxyAuthenticate();

    void setProxyAuthorization(HttpHeaderProxyAuthorization);
    HttpHeaderProxyAuthorization getProxyAuthorization();

    void setStrictTransportSecurity(HttpHeaderStrictTransportSecurity);
    HttpHeaderStrictTransportSecurity getStrictTransportSecurity();

    HttpHeaderVersion getVersion();
    void setVersion(HttpHeaderVersion);

    void setXFrameOptions(HttpHeaderXFrameOptions);
    HttpHeaderXFrameOptions getXFrameOptions();

    void setTransferEncoding(HttpHeaderTransferEncoding);
    HttpHeaderTransferEncoding getTransferEncoding();

    void setUpgrade(HttpHeaderUpgrade);
    HttpHeaderUpgrade getUpgrade();

    void setWebSocketAccept(HttpHeaderSecWebSocketAccept);
    HttpHeaderSecWebSocketAccept getWebSocketAccept();

    void setWebSocketKey(HttpHeaderSecWebSocketKey);
    HttpHeaderSecWebSocketKey getWebSocketKey();

    void setWebSocketProtocol(HttpHeaderSecWebSocketProtocol);
    HttpHeaderSecWebSocketProtocol getWebSocketProtocol();

    void setWebSocketKey1(HttpHeaderSecWebSocketKey);
    HttpHeaderSecWebSocketKey getWebSocketKey1();

    void setWebSocketKey2(HttpHeaderSecWebSocketKey);
    HttpHeaderSecWebSocketKey getWebSocketKey2();

    void setWebSocketKey3(HttpHeaderSecWebSocketKey);
    HttpHeaderSecWebSocketKey getWebSocketKey3();

    void setWebSocketVersion(HttpHeaderSecWebSocketVersion s);
    HttpHeaderSecWebSocketVersion getWebSocketVersion();
    
    void setWebSocketExtensions(HttpHeaderSecWebSocketExtensions s);
    HttpHeaderSecWebSocketExtensions getWebSocketExtensions();

    void setWebSocketOrigin(HttpHeaderSecWebSocketOrigin s);
    HttpHeaderSecWebSocketOrigin getWebSocketOrigin();

    void setOrigin(HttpHeaderOrigin s);
    HttpHeaderOrigin getOrigin();

    void setPragma(HttpHeaderPragma s);
    HttpHeaderPragma getPragma();

    void setHttpHeaderAcceptRanges(HttpHeaderAcceptRanges s);
    HttpHeaderAcceptRanges getAcceptRanges();

    void setAltSvc(HttpHeaderAltSvc s);
    HttpHeaderAltSvc getAltSvc();

    void setContentRange(HttpHeaderContentRange);
    HttpHeaderContentRange getContentRange();

    void setSecurityPolicy(HttpHeaderContentSecurityPolicy);
    HttpHeaderContentSecurityPolicy getSecurityPolicy();

    void setSecurityPolicyReportOnly(HttpHeaderContentSecurityPolicy);
    HttpHeaderContentSecurityPolicy getSecurityPolicyReportOnly();

    HttpHeaderCrossOriginEmbedderPolicy getCrossOriginEmbedderPolicy();
    void setCrossOriginEmbedderPolicy(HttpHeaderCrossOriginEmbedderPolicy);

    HttpHeaderCrossOriginOpenerPolicy getCrossOriginOpenerPolicy();
    void setCrossOriginOpenerPolicy(HttpHeaderCrossOriginOpenerPolicy);

    HttpHeaderCrossOriginResourcePolicy getCrossOriginResourcePolicy();
    void setCrossOriginResourcePolicy(HttpHeaderCrossOriginResourcePolicy);

    HttpHeaderDate getDate();
    void setDate(HttpHeaderDate);

    HttpHeaderExpect getExpect();
    void setExpect(HttpHeaderExpect);

    HttpHeaderExpectCT getExpectCT();
    void setExpectCT(HttpHeaderExpectCT);

    HttpHeaderExpires getExpires();
    void setExpires(HttpHeaderExpires);

    HttpHeaderFrom getFrom();
    void setFrom(HttpHeaderFrom);

    HttpHeaderRange getRange();
    void setRange(HttpHeaderRange);

    HttpHeaderReferer getReferer();
    void setReferer(HttpHeaderReferer);

    HttpHeaderReferrerPolicy getRefererPolicy();
    void setRefererPolicy(HttpHeaderReferrerPolicy);

    HttpHeaderVary getVary();
    void setVary(HttpHeaderVary);

    HttpHeaderVia getVia();
    void setVia(HttpHeaderVia);

    HttpHeaderServer getServer();
    void setServer(HttpHeaderServer);

    HttpHeaderWarning getWarning();
    void setWarning(HttpHeaderWarning);

    HttpHeaderAcceptCh getAcceptCh();
    void setAcceptCh(HttpHeaderAcceptCh);

    HttpHeaderDnt getDnt();
    void setDnt(HttpHeaderDnt);

    HttpHeaderSaveData getSaveData();
    void setSaveData(HttpHeaderSaveData);
    
    HttpHeaderSecFetchDest getSecFetchDest();
    void setSecFetchDest(HttpHeaderSecFetchDest);

    HttpHeaderSecFetchMode getSecFetchMode();
    void setSecFetchMode(HttpHeaderSecFetchMode);

    HttpHeaderSecFetchSite getSecFetchSite();
    void setSecFetchSite(HttpHeaderSecFetchSite);

    HttpHeaderSecFetchUser getSecFetchUser();
    void setSecFetchUser(HttpHeaderSecFetchUser);

    HttpHeaderSourceMap getSourceMap();
    void setSourceMap(HttpHeaderSourceMap);

    HttpHeaderServerTiming getServerTiming();
    void setServerTiming(HttpHeaderServerTiming s);

    String toString(int);

    static int findId(String);
    static String findName(int);

    int getMethod() const;
    void setMethod(int);

    HttpUrl getUrl();
    void setUrl(HttpUrl);

    int getResponseStatus() const;
    void setResponseStatus(int);

    String getResponseReason() const;
    bool setResponseReason(String);

    String getAuthority() const;
    void setAuthority(String);

    int getType() const;
    void setType(int);

    int getProtocol() const;
    //NetProtocol
    void setProtocol(int);

    int size();
    
    enum Type {
        Request = 100,
        Response
    };

private:
    static HashMap<String,Integer> idMaps;
    static ArrayList<String> names;

    HashMap<String,Object> mHeaderValues = createHashMap<String,Object>();
    ArrayList<HttpCookie> mCookies = createArrayList<HttpCookie>();
    HttpUrl mUrl;
    int mType;
    int mProtocol;
    int mMethod;
    int mResponseStatus;
    String mResponseReason;
};

}
#endif
