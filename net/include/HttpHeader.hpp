#ifndef __OBOTCHA_HTTP_HEADER_HPP__
#define __OBOTCHA_HTTP_HEADER_HPP__

#include <map>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "HashMap.hpp"
#include "HttpCookie.hpp"
#include "HttpHeaderCacheControl.hpp"
#include "HttpContentType.hpp"
#include "HttpVersion.hpp"
#include "HttpUrl.hpp"
#include "HttpHeaderLink.hpp"
#include "HttpHeaderAcceptEncoding.hpp"
#include "HttpHeaderAcceptLanguage.hpp"
#include "HttpHeaderAcceptCharSet.hpp"
#include "HttpHeaderAccept.hpp"
#include "HttpHeaderAcceptPatch.hpp"
#include "HttpStrictTransportSecurity.hpp"
#include "HttpProxyAuthorization.hpp"
#include "HttpProxyAuthenticate.hpp"
#include "HttpXFrameOptions.hpp"
#include "HttpForwarded.hpp"
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
#include "HttpContentLocation.hpp"
#include "HttpHeaderConnection.hpp"
#include "HttpHeaderHost.hpp"
#include "HttpHeaderKeepAlive.hpp"
#include "HttpHeaderMatch.hpp"
#include "HttpHeaderMatch.hpp"
#include "HttpHeaderRetryAfter.hpp"
#include "HttpHeaderUserAgent.hpp"
#include "HttpIfModifiedSince.hpp"
#include "HttpIfRange.hpp"
#include "HttpIfUnmodifiedSince.hpp"
#include "HttpTransferEncoding.hpp"
#include "HttpHeaderUpgrade.hpp"
#include "HttpSecWebSocketAccept.hpp" 
#include "HttpSecWebSocketKey.hpp" 
#include "HttpSecWebSocketProtocol.hpp"
#include "HttpSecWebSocketVersion.hpp"
#include "HttpSecWebSocketExtensions.hpp"
#include "HttpSecWebSocketOrigin.hpp"
#include "HttpHeaderOrigin.hpp"
#include "HttpHeaderPragma.hpp"
#include "HttpHeaderAcceptRanges.hpp"
#include "HttpHeaderAltSvc.hpp"
#include "HttpContentRange.hpp"
#include "HttpContentSecurityPolicy.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeader) {

public:
    ////-------- defination ---------////
    const static String Method;
    const static String Path;
    const static String Scheme;
    const static String Status;
    const static String Protocol;
    const static String Accept;
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
    const static String DNT;
    const static String Date;
    const static String ETag;
    const static String Expect;
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
    const static String Refresh;
    const static String RetryAfter;
    const static String SecWebSocketKey;
    const static String SecWebSocketAccept;
    const static String Server;
    const static String SetCookie;
    const static String SecTokenBinding;
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
    const static String Digest;
    //Transfer-Encoding type
    const static String TransferChunked;

    //http connection
    const static String ConnectionClose;

    enum type{
        TypeMethod = 0,
        TypePath,
        TypeScheme,
        TypeStatus,
        TypeProtocol,
        TypeAccept,
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
        TypeDNT,
        TypeDate,
        TypeETag,
        TypeExpect,
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
        TypeRefresh,
        TypeRetryAfter,
        TypeSecWebSocketKey,
        TypeSecWebSocketAccept,
        TypeServer,
        TypeSetCookie,
        TypeSecTokenBinding,
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
        TypeDigest,
    };

    ////-------- function -------////
    _HttpHeader();

    void addHttpHeader(sp<_HttpHeader>);
    
    void reset();
    
    void set(String header,String value);
    
    String get(String);

    MapIterator<String,String> getIterator();

    void addCookie(HttpCookie);
    ArrayList<HttpCookie> getCookies();

    //HttpHeaderAcceptCharSet
    HttpHeaderAcceptCharSet getAcceptCharSet();
    void setAcceptCharSet(HttpHeaderAcceptCharSet);

    //HttpHeaderAccept
    HttpHeaderAccept getAccept();
    void setAccept(HttpHeaderAccept);

    //HttpHeaderAcceptEncoding
    HttpHeaderAcceptEncoding getAcceptEncoding();
    void setAcceptEncoding(HttpHeaderAcceptEncoding);

    //HttpHeaderAcceptLanguage
    HttpHeaderAcceptLanguage getAcceptLanguage();
    void setAcceptLanguage(HttpHeaderAcceptLanguage);

    //HttpHeaderAcceptPatch
    HttpHeaderAcceptPatch getAcceptPatch();
    void setAcceptPatch(HttpHeaderAcceptPatch);

    //HttpHeaderAccessControlAllowCredentials
    HttpHeaderAccessControlAllowCredentials getAllowCredentials();
    void setAllowCredentials(HttpHeaderAccessControlAllowCredentials);

    //HttpHeaderAccessControlAllowHeaders
    HttpHeaderAccessControlAllowHeaders getAllowHeaders();
    void setAllowHeaders(HttpHeaderAccessControlAllowHeaders);

    //HttpHeaderAccessControlAllowMethods
    HttpHeaderAccessControlAllowMethods getAllowMethods();
    void setAllowMethods(HttpHeaderAccessControlAllowMethods);

    //HttpHeaderAccessControlAllowOrigin
    HttpHeaderAccessControlAllowOrigin getAllowOrigin();
    void setAllowOrigin(HttpHeaderAccessControlAllowOrigin);

    //HttpHeaderAccessControlExposeHeaders
    HttpHeaderAccessControlExposeHeaders getExposeHeaders();
    void setExposeHeaders(HttpHeaderAccessControlExposeHeaders);

    //HttpHeaderAccessControlMaxAge
    HttpHeaderAccessControlMaxAge getMaxAge();
    void setMaxAge(HttpHeaderAccessControlMaxAge);

    //HttpHeaderAccessControlRequestHeaders
    HttpHeaderAccessControlRequestHeaders getRequestHeaders();
    void setReqeuestHeaders(HttpHeaderAccessControlRequestHeaders);

    //HttpHeaderAccessControlRequestMethod
    HttpHeaderAccessControlRequestMethod getRequestMethod();
    void setRequestMethod(HttpHeaderAccessControlRequestMethod);

    //HttpHeaderAge
    HttpHeaderAge getAge();
    void setAge(HttpHeaderAge);

    //HttpHeaderAllow
    HttpHeaderAllow getAllow();
    void setAllow(HttpHeaderAllow);

    //HttpHeaderAuthorization
    HttpHeaderAuthorization getAuthorization();
    void setAuthorization(HttpHeaderAuthorization);

    //HttpHeaderCacheControl
    HttpHeaderCacheControl getCacheControl();
    void setCacheControl(HttpHeaderCacheControl);

    //HttpHeaderClearSiteData
    HttpHeaderClearSiteData getClearSiteData();
    void setClearSiteData(HttpHeaderClearSiteData);

    //HttpHeaderContentDisposition
    HttpHeaderContentDisposition getContentDisposition();
    void setContentDisposition(HttpHeaderContentDisposition);

    //HttpHeaderContentEncoding
    HttpHeaderContentEncoding getContentEncoding();
    void setContentEncoding(HttpHeaderContentEncoding);

    //HttpHeaderContentLanguage
    HttpHeaderContentLanguage getContentLanguage();
    void setContentLanguage(HttpHeaderContentLanguage);

    //HttpHeaderContentLength
    HttpHeaderContentLength getContentLength();
    void setContentLength(HttpHeaderContentLength);

    //HttpContentLocation
    HttpContentLocation getContentLocation();
    void setContentLocation(HttpContentLocation);

    //HttpContentType
    HttpContentType getContentType();
    void setContentType(HttpContentType);

    //HttpForwarded
    HttpForwarded getForwarded();
    void setForwarded(HttpForwarded);

    //HttpHeaderConnection
    HttpHeaderConnection getConnection();
    void setConnection(HttpHeaderConnection);

    //HttpHeaderDigest
    HttpHeaderDigest getDigest();
    void setDigest(HttpHeaderDigest);

    //HttpHeaderHost
    HttpHeaderHost getHost();
    void setHost(HttpHeaderHost);

    //HttpHeaderKeepAlive
    HttpHeaderKeepAlive getKeepAlive();
    void setKeepAlive(HttpHeaderKeepAlive);

    //ArrayList<HttpHeaderLink>
    ArrayList<HttpHeaderLink> getLinks();
    void setLinks(ArrayList<HttpHeaderLink>);
    void addLink(HttpHeaderLink);

    //IfMatch
    HttpHeaderMatch getIfMatch();
    void setIfMatch(HttpHeaderMatch);

    //IfNoneMatch
    HttpHeaderMatch getIfNoneMatch();
    void setIfNoneMatch(HttpHeaderMatch);

    //HttpHeaderRetryAfter
    HttpHeaderRetryAfter getRetryAfter();
    void setRetryAfter(HttpHeaderRetryAfter);

    //HttpHeaderUserAgent
    HttpHeaderUserAgent getUserAgent();
    void setUserAgent(HttpHeaderUserAgent);

    //HttpIfModifiedSince
    HttpIfModifiedSince getIfModifiedSince();
    void setIfModifiedSince(HttpIfModifiedSince);

    //HttpIfRange
    HttpIfRange getIfRange();
    void setIfRange(HttpIfRange);

    //HttpIfUnmodifiedSince
    HttpIfUnmodifiedSince getIfUnmodifiedSince();
    void setIfUnmodifiedSince(HttpIfUnmodifiedSince);

    //HttpProxyAuthenticate
    void setProxyAuthenticate(HttpProxyAuthenticate);
    HttpProxyAuthenticate getProxyAuthenticate();

    //HttpProxyAuthorization
    void setProxyAuthorization(HttpProxyAuthorization);
    HttpProxyAuthorization getProxyAuthorization();

    //HttpStrictTransportSecurity
    void setStrictTransportSecurity(HttpStrictTransportSecurity);
    HttpStrictTransportSecurity getStrictTransportSecurity();

    //HttpVersion
    HttpVersion getVersion();
    void setVersion(HttpVersion);

    //HttpXFrameOptions
    void setXFrameOptions(HttpXFrameOptions);
    HttpXFrameOptions getXFrameOptions();

    //TransferEncoding
    void setTransferEncoding(HttpTransferEncoding);
    HttpTransferEncoding getTransferEncoding();

    //Upgrade
    void setUpgrade(HttpHeaderUpgrade);
    HttpHeaderUpgrade getUpgrade();

    //HttpSecWebSocketKey
    void setWebSocketAccept(HttpSecWebSocketAccept);
    HttpSecWebSocketAccept getWebSocketAccept();

    //HttpSecWebSocketKey 
    void setWebSocketKey(HttpSecWebSocketKey);
    HttpSecWebSocketKey getWebSocketKey();

    //HttpSecWebSocketProtocol 
    void setWebSocketProtocol(HttpSecWebSocketProtocol);
    HttpSecWebSocketProtocol getWebSocketProtocol();

    //HttpSecWebSocketKey 
    void setWebSocketKey1(HttpSecWebSocketKey);
    HttpSecWebSocketKey getWebSocketKey1();

    //HttpSecWebSocketKey 
    void setWebSocketKey2(HttpSecWebSocketKey);
    HttpSecWebSocketKey getWebSocketKey2();

    //HttpSecWebSocketKey 
    void setWebSocketKey3(HttpSecWebSocketKey);
    HttpSecWebSocketKey getWebSocketKey3();

    //HttpSecWebSocketVersion mWebSocketVersion;
    void setWebSocketVersion(HttpSecWebSocketVersion s);
    HttpSecWebSocketVersion getWebSocketVersion();
    
    //HttpSecWebSocketExtensions mWebSocketExtensions;
    void setWebSocketExtensions(HttpSecWebSocketExtensions s);
    HttpSecWebSocketExtensions getWebSocketExtensions();

    //HttpSecWebSocketOrigin
    void setWebSocketOrigin(HttpSecWebSocketOrigin s);
    HttpSecWebSocketOrigin getWebSocketOrigin();

    //HttpHeaderOrigin
    void setOrigin(HttpHeaderOrigin s);
    HttpHeaderOrigin getOrigin();

    //HttpHeaderPragma
    void setPragma(HttpHeaderPragma s);
    HttpHeaderPragma getPragma();

    //HttpHeaderAcceptRanges
    void setHttpHeaderAcceptRanges(HttpHeaderAcceptRanges s);
    HttpHeaderAcceptRanges getAcceptRanges();

    //HttpHeaderAltSvc
    void setAltSvc(HttpHeaderAltSvc s);
    HttpHeaderAltSvc getAltSvc();

    //HttpContentRange
    void setContentRange(HttpContentRange);
    HttpContentRange getContentRange();

    //HttpContentSecurityPolicy
    void setSecurityPolicy(HttpContentSecurityPolicy);
    HttpContentSecurityPolicy getSecurityPolicy();

    void setSecurityPolicyReportOnly(HttpContentSecurityPolicy);
    HttpContentSecurityPolicy getSecurityPolicyReportOnly();

    String toString(int);

    static int findId(String);
    static String findString(int);

    int getMethod();
    void setMethod(int);

    HttpUrl getUrl();
    void setUrl(HttpUrl);

    int getResponseStatus();
    void setResponseStatus(int);

    String getResponseReason();
    void setResponseReason(String);

    int getType();
    void setType(int);

    int size();
    
    enum Type {
        Request = 100,
        Response
    };

private:

    HashMap<String,String> mValues;

    //http header member 
    HttpHeaderAcceptCharSet mAcceptCharSet;

    HttpHeaderAccept mAccept;

    HttpHeaderAcceptEncoding mAcceptEncoding;

    HttpHeaderAcceptLanguage mAcceptLanguage;

    HttpHeaderAcceptPatch mAcceptPatch;

    HttpHeaderAccessControlAllowCredentials mAllowCredentials;

    HttpHeaderAccessControlAllowHeaders mAllowHeaders;

    HttpHeaderAccessControlAllowMethods mAllowMethods;

    HttpHeaderAccessControlAllowOrigin mAllowOrigin;

    HttpHeaderAccessControlExposeHeaders mExposeHeaders;

    HttpHeaderAccessControlMaxAge mMaxAge;

    HttpHeaderAccessControlRequestHeaders mRequestHeaders;
    
    HttpHeaderAccessControlRequestMethod mRequestMethod;

    HttpHeaderAge mAge;

    HttpHeaderAllow mAllow;

    HttpHeaderAuthorization mAuthorization;

    HttpHeaderCacheControl mCacheControl;

    HttpHeaderClearSiteData mClearSiteData;

    HttpHeaderContentDisposition mContentDisposition;

    HttpHeaderContentEncoding mContentEncoding;

    HttpHeaderContentLanguage mContentLanguage;

    HttpHeaderContentLength mContentLength;

    HttpContentLocation mContentLocation;

    HttpContentType mContentType;

    HttpForwarded mForwarded;

    HttpHeaderConnection mConnection;

    HttpHeaderDigest mHeaderDigest;

    HttpHeaderHost mHost;

    HttpHeaderKeepAlive mKeepAlive;

    ArrayList<HttpHeaderLink> mLinks;

    HttpHeaderMatch mIfMatch;

    HttpHeaderMatch mIfNoneMatch;

    HttpHeaderRetryAfter mRetryAfter;

    HttpHeaderUserAgent mUserAgent;

    HttpIfModifiedSince mIfModifiedSince;

    HttpIfRange mIfRange;

    HttpIfUnmodifiedSince mIfUnmodifiedSince;
    
    HttpProxyAuthenticate mProxyAuthenticate;

    HttpProxyAuthorization mProxyAuthorization;

    HttpStrictTransportSecurity mTransportSecurity;

    HttpVersion mVersion;

    HttpXFrameOptions mXFrameOptions;

    HttpTransferEncoding mTransferEncoding;

    HttpHeaderUpgrade mUpgrade;

    HttpSecWebSocketAccept mWebSocketAccept;
    HttpSecWebSocketKey mWebSocketKey;
    HttpSecWebSocketProtocol mWebSocketProtocol;

    HttpSecWebSocketKey mWebSocketKey1;
    HttpSecWebSocketKey mWebSocketKey2;
    HttpSecWebSocketKey mWebSocketKey3;

    HttpSecWebSocketVersion mWebSocketVersion;
    HttpSecWebSocketExtensions mWebSocketExtensions;
    HttpSecWebSocketOrigin mWebSocketOrigin;

    HttpHeaderOrigin mOrigin;
    HttpHeaderPragma mPragma;

    HttpHeaderAcceptRanges mAcceptRanges;

    HttpHeaderAltSvc mAltSvc;
    
    HttpContentRange mContentRange;

    HttpContentSecurityPolicy mSecurityPolicy;
    HttpContentSecurityPolicy mSecurityPolicyReportOnly;
    /////

    ArrayList<HttpCookie> mCookies;

    HttpUrl mUrl;

    int mType;

    int mMethod;

    int mResponseStatus;

    String mResponseReason;

    static HashMap<String,Integer> idMaps;
    static ArrayList<String> names;
};

}
#endif
