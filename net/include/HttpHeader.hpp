#ifndef __OBOTCHA_HTTP_HEADER_HPP__
#define __OBOTCHA_HTTP_HEADER_HPP__

#include <map>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "HashMap.hpp"
#include "HttpCookie.hpp"
#include "HttpCacheControl.hpp"
#include "HttpContentType.hpp"
#include "HttpVersion.hpp"
#include "HttpUrl.hpp"
#include "HttpHeaderLink.hpp"
#include "HttpAcceptEncoding.hpp"
#include "HttpAcceptLanguage.hpp"
#include "HttpAcceptCharSet.hpp"
#include "HttpAccept.hpp"
#include "HttpAcceptPatch.hpp"
#include "HttpStrictTransportSecurity.hpp"
#include "HttpProxyAuthorization.hpp"
#include "HttpProxyAuthenticate.hpp"
#include "HttpXFrameOptions.hpp"
#include "HttpForwarded.hpp"
#include "HttpContentDisposition.hpp"
#include "HttpHeaderDigest.hpp"
#include "HttpAuthorization.hpp"

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

    //void updateCacheControl();
    HttpCacheControl getCacheControl();
    void setCacheControl(HttpCacheControl);
    
    //void setContentType(String);
    void setContentType(HttpContentType);
    HttpContentType getContentType();

    void addHeaderLink(HttpHeaderLink);
    ArrayList<HttpHeaderLink> getHeaderLinks();

    void setAcceptEncoding(HttpAcceptEncoding);
    HttpAcceptEncoding getAcceptEncoding();

    void setAcceptLanguage(HttpAcceptLanguage);
    HttpAcceptLanguage getAcceptLanguage();

    void setAcceptCharSet(HttpAcceptCharSet);
    HttpAcceptCharSet getAcceptCharSet();

    void setAcceptPatch(HttpAcceptPatch);
    HttpAcceptPatch getAcceptPatch();

    void setAccept(HttpAccept);
    HttpAccept getAccept();

    void setStrictTransportSecurity(HttpStrictTransportSecurity);
    HttpStrictTransportSecurity getStrictTransportSecurity();

    void setProxyAuthorization(HttpProxyAuthorization);
    HttpProxyAuthorization getProxyAuthorization();

    void setProxyAuthenticate(HttpProxyAuthenticate);
    HttpProxyAuthenticate getProxyAuthenticate();

    void setXFrameOptions(HttpXFrameOptions);
    HttpXFrameOptions getXFrameOptions();

    void setForwarded(HttpForwarded);
    HttpForwarded getForwarded();

    void setContentDisposition(HttpContentDisposition);
    HttpContentDisposition getContentDisposition();

    void setHeaderDigest(HttpHeaderDigest);
    HttpHeaderDigest getHeaderDigest();

    void setAuthorization(HttpAuthorization);
    HttpAuthorization getAuthorization();

    String toString(int);

    int getMethod();
    void setMethod(int);

    HttpUrl getUrl();
    void setUrl(HttpUrl);

    HttpVersion getVersion();
    void setVersion(HttpVersion);

    int getResponseStatus();
    void setResponseStatus(int);

    String getResponseReason();
    void setResponseReason(String);

    int getContentLength();
    void setContentLength(int);

    String getConnection();
    void setConnection(String);

    int getType();
    void setType(int);

    int size();
    
    enum Type {
        Request = 100,
        Response
    };

private:

    HashMap<String,String> mValues;

    ArrayList<HttpCookie> mCookies;

    ArrayList<HttpHeaderLink> mLinks;

    HttpCacheControl mCacheControl;

    HttpContentType mContentType;

    HttpAcceptEncoding mAcceptEncoding;

    HttpAcceptLanguage mAcceptLanguage;

    HttpAcceptCharSet mAcceptCharSet;

    HttpAcceptPatch mAcceptPatch;

    HttpAccept mAccept;

    HttpStrictTransportSecurity mTransportSecurity;

    HttpProxyAuthorization mProxyAuthorization;

    HttpProxyAuthenticate mProxyAuthenticate;

    HttpXFrameOptions mXFrameOptions;

    HttpForwarded mForwarded;

    HttpContentDisposition mContentDisposition;

    HttpHeaderDigest mHeaderDigest;

    HttpAuthorization mAuthorization;

    HttpVersion mVersion;

    HttpUrl mUrl;

    int mType;

    int mMethod;

    int mResponseStatus;

    String mResponseReason;

    int mContentLength;

    String mConnection;

    static HashMap<String,Integer> idMaps;
};

}
#endif
