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

namespace obotcha {

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
    const static String CrossOriginEmbederPolicy;
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
    };

    ////-------- function -------////
    _HttpHeader(int protocol = st(NetProtocol)::Http);

    void addHttpHeader(sp<_HttpHeader>);
    
    void reset();
    
    void set(String header,String value);
    
    String get(String);

    //MapIterator<String,String> getIterator();
    ListIterator<Pair<String,String>> getIterator();

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

    //HttpHeaderContentLocation
    HttpHeaderContentLocation getContentLocation();
    void setContentLocation(HttpHeaderContentLocation);

    //HttpHeaderContentType
    HttpHeaderContentType getContentType();
    void setContentType(HttpHeaderContentType);

    //HttpHeaderForwarded
    HttpHeaderForwarded getForwarded();
    void setForwarded(HttpHeaderForwarded);

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

    //HttpHeaderIfModifiedSince
    HttpHeaderIfModifiedSince getIfModifiedSince();
    void setIfModifiedSince(HttpHeaderIfModifiedSince);

    //HttpHeaderIfRange
    HttpHeaderIfRange getIfRange();
    void setIfRange(HttpHeaderIfRange);

    //HttpHeaderIfUnmodifiedSince
    HttpHeaderIfUnmodifiedSince getIfUnmodifiedSince();
    void setIfUnmodifiedSince(HttpHeaderIfUnmodifiedSince);

    //HttpHeaderProxyAuthenticate
    void setProxyAuthenticate(HttpHeaderProxyAuthenticate);
    HttpHeaderProxyAuthenticate getProxyAuthenticate();

    //HttpHeaderProxyAuthorization
    void setProxyAuthorization(HttpHeaderProxyAuthorization);
    HttpHeaderProxyAuthorization getProxyAuthorization();

    //HttpHeaderStrictTransportSecurity
    void setStrictTransportSecurity(HttpHeaderStrictTransportSecurity);
    HttpHeaderStrictTransportSecurity getStrictTransportSecurity();

    //HttpHeaderVersion
    HttpHeaderVersion getVersion();
    void setVersion(HttpHeaderVersion);

    //HttpHeaderXFrameOptions
    void setXFrameOptions(HttpHeaderXFrameOptions);
    HttpHeaderXFrameOptions getXFrameOptions();

    //TransferEncoding
    void setTransferEncoding(HttpHeaderTransferEncoding);
    HttpHeaderTransferEncoding getTransferEncoding();

    //Upgrade
    void setUpgrade(HttpHeaderUpgrade);
    HttpHeaderUpgrade getUpgrade();

    //HttpHeaderSecWebSocketKey
    void setWebSocketAccept(HttpHeaderSecWebSocketAccept);
    HttpHeaderSecWebSocketAccept getWebSocketAccept();

    //HttpHeaderSecWebSocketKey 
    void setWebSocketKey(HttpHeaderSecWebSocketKey);
    HttpHeaderSecWebSocketKey getWebSocketKey();

    //HttpHeaderSecWebSocketProtocol 
    void setWebSocketProtocol(HttpHeaderSecWebSocketProtocol);
    HttpHeaderSecWebSocketProtocol getWebSocketProtocol();

    //HttpHeaderSecWebSocketKey 
    void setWebSocketKey1(HttpHeaderSecWebSocketKey);
    HttpHeaderSecWebSocketKey getWebSocketKey1();

    //HttpHeaderSecWebSocketKey 
    void setWebSocketKey2(HttpHeaderSecWebSocketKey);
    HttpHeaderSecWebSocketKey getWebSocketKey2();

    //HttpHeaderSecWebSocketKey 
    void setWebSocketKey3(HttpHeaderSecWebSocketKey);
    HttpHeaderSecWebSocketKey getWebSocketKey3();

    //HttpHeaderSecWebSocketVersion mWebSocketVersion;
    void setWebSocketVersion(HttpHeaderSecWebSocketVersion s);
    HttpHeaderSecWebSocketVersion getWebSocketVersion();
    
    //HttpHeaderSecWebSocketExtensions mWebSocketExtensions;
    void setWebSocketExtensions(HttpHeaderSecWebSocketExtensions s);
    HttpHeaderSecWebSocketExtensions getWebSocketExtensions();

    //HttpHeaderSecWebSocketOrigin
    void setWebSocketOrigin(HttpHeaderSecWebSocketOrigin s);
    HttpHeaderSecWebSocketOrigin getWebSocketOrigin();

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

    //HttpHeaderContentRange
    void setContentRange(HttpHeaderContentRange);
    HttpHeaderContentRange getContentRange();

    //HttpHeaderContentSecurityPolicy
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
    void setData(HttpHeaderDate);

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
    void setSecFetchData(HttpHeaderSecFetchDest);

    HttpHeaderSecFetchMode getSecFetchMode();
    void setSecFetchMode(HttpHeaderSecFetchMode);

    HttpHeaderSecFetchSite getSecFetchSite();
    void setSecFetchSite(HttpHeaderSecFetchSite);

    HttpHeaderSecFetchUser getSecFetchUser();
    void setSecFetchUser(HttpHeaderSecFetchUser);

    HttpHeaderSourceMap getSourceMap();
    void setSourceMap(HttpHeaderSourceMap);

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

    String getAuthority();
    void setAuthority(String);

    int getType();
    void setType(int);

    int getProtocol();
    void setProtocol(int);

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

    HttpHeaderContentLocation mContentLocation;

    HttpHeaderContentType mContentType;

    HttpHeaderForwarded mForwarded;

    HttpHeaderConnection mConnection;

    HttpHeaderDigest mHeaderDigest;

    HttpHeaderHost mHost;

    HttpHeaderKeepAlive mKeepAlive;

    ArrayList<HttpHeaderLink> mLinks;

    HttpHeaderMatch mIfMatch;

    HttpHeaderMatch mIfNoneMatch;

    HttpHeaderRetryAfter mRetryAfter;

    HttpHeaderUserAgent mUserAgent;

    HttpHeaderIfModifiedSince mIfModifiedSince;

    HttpHeaderIfRange mIfRange;

    HttpHeaderIfUnmodifiedSince mIfUnmodifiedSince;
    
    HttpHeaderProxyAuthenticate mProxyAuthenticate;

    HttpHeaderProxyAuthorization mProxyAuthorization;

    HttpHeaderStrictTransportSecurity mTransportSecurity;

    HttpHeaderVersion mVersion;

    HttpHeaderXFrameOptions mXFrameOptions;

    HttpHeaderTransferEncoding mTransferEncoding;

    HttpHeaderUpgrade mUpgrade;

    HttpHeaderSecWebSocketAccept mWebSocketAccept;
    HttpHeaderSecWebSocketKey mWebSocketKey;
    HttpHeaderSecWebSocketProtocol mWebSocketProtocol;

    HttpHeaderSecWebSocketKey mWebSocketKey1;
    HttpHeaderSecWebSocketKey mWebSocketKey2;
    HttpHeaderSecWebSocketKey mWebSocketKey3;

    HttpHeaderSecWebSocketVersion mWebSocketVersion;
    HttpHeaderSecWebSocketExtensions mWebSocketExtensions;
    HttpHeaderSecWebSocketOrigin mWebSocketOrigin;

    HttpHeaderOrigin mOrigin;
    HttpHeaderPragma mPragma;

    HttpHeaderAcceptRanges mAcceptRanges;

    HttpHeaderAltSvc mAltSvc;
    
    HttpHeaderContentRange mContentRange;

    HttpHeaderContentSecurityPolicy mSecurityPolicy;
    HttpHeaderContentSecurityPolicy mSecurityPolicyReportOnly;

    HttpHeaderCrossOriginEmbedderPolicy mCrossOriginEmbedderPolicy;
    HttpHeaderCrossOriginOpenerPolicy mCrossOriginOpenerPolicy;
    HttpHeaderCrossOriginResourcePolicy mCrossOriginResourcePolicy;

    HttpHeaderDate mDate;

    HttpHeaderExpect mExpect;

    HttpHeaderExpectCT mExpectCT;

    HttpHeaderExpires mExpires;

    HttpHeaderFrom mFrom;

    HttpHeaderRange mRange;

    HttpHeaderReferer mReferer;

    HttpHeaderReferrerPolicy mRefererPolicy;

    HttpHeaderVary mVary;

    HttpHeaderVia mVia;

    HttpHeaderServer mHeaderServer;

    HttpHeaderWarning mWarning;

    HttpHeaderAcceptCh mAcceptCh;

    HttpHeaderDnt mDnt;
    HttpHeaderSaveData mSaveData;
    HttpHeaderSecFetchDest mFetchDest;
    HttpHeaderSecFetchMode mFetchMode;
    HttpHeaderSecFetchSite mFetchSite;
    HttpHeaderSecFetchUser mFetchUser;
    HttpHeaderServerTiming mServerTiming;
    HttpHeaderSourceMap mSourceMap;
    
    String mAuthority;
    /////

    ArrayList<HttpCookie> mCookies;

    HttpUrl mUrl;

    int mType;

    int mProtocol;

    int mMethod;

    int mResponseStatus;

    String mResponseReason;

    static HashMap<String,Integer> idMaps;
    static ArrayList<String> names;
};

}
#endif
