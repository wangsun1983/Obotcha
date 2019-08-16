#ifndef __HTTP_PACKET_HPP__
#define __HTTP_PACKET_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HttpHeader.hpp"
#include "ByteArray.hpp"
#include "HttpCookie.hpp"

namespace obotcha {

/* Request Methods */
enum HttpMethodType { 
    HttpMethodDelete = HTTP_DELETE,
    HttpMethodGet = HTTP_GET,
    HttpMethodHead = HTTP_HEAD,
    HttpMethodPost = HTTP_POST,
    HttpMethodPut = HTTP_PUT,
    /* pathological */
    HttpMethodConnect = HTTP_CONNECT,
    HttpMethodOptions = HTTP_OPTIONS,
    HttpMethodTrace = HTTP_TRACE,
    /* webdav */
    HttpMethodCopy = HTTP_COPY,
    HttpMethodLock = HTTP_LOCK,
    HttpMethodMkcol = HTTP_MKCOL,
    HttpMethodMove = HTTP_MOVE,
    HttpMethodPropFind = HTTP_PROPFIND,
    HttpMethodPropPatch = HTTP_PROPPATCH,
    HttpMethodUnlock = HTTP_UNLOCK,
    /* subversion */
    HttpMethodReport = HTTP_REPORT,
    HttpMethodMkActivity = HTTP_MKACTIVITY,
    HttpMethodCheckOut = HTTP_CHECKOUT,
    HttpMethodMerge = HTTP_MERGE,
    /* upnp */
    HttpMethodMsearch = HTTP_MSEARCH,
    HttpMethodNotify = HTTP_NOTIFY,
    HttpMethodSubscribe = HTTP_SUBSCRIBE,
    HttpMethodUnSubscribe = HTTP_UNSUBSCRIBE,
    /* RFC-5789 */
    HttpMethodPatch = HTTP_PATCH,
};

enum HTTP_RESPONSE_STATUS {
    HTTP_RESPONSE_CONTINUE = 100,
 	HTTP_RESPONSE_SWITCHING_PROTOCLS = 101,
 	HTTP_RESPONSE_OK = 200,
 	HTTP_RESPONSE_CREATED = 201,
 	HTTP_RESPONSE_ACCEPTED = 202,
 	HTTP_RESPONSE_NON_AUTHORITATIVE_INFORMATION = 203,
 	HTTP_RESPONSE_NO_CONTENT = 204,
 	HTTP_RESPONSE_RESET_CONTENT = 205,
 	HTTP_RESPONSE_PARTIAL_CONTENT = 206,
 	HTTP_RESPONSE_MULTIPLE_CHOICES = 300,
 	HTTP_RESPONSE_MOVED_PERMANENTLY = 301,
 	HTTP_RESPONSE_FOUND = 302,
 	HTTP_RESPONSE_SEE_OTHER = 303,
 	HTTP_RESPONSE_NOT_MODIFIED = 304,
 	HTTP_RESPONSE_USE_PROXY = 305,
 	HTTP_RESPONSE_TEMPORARY_REDIRECT = 306,
 	HTTP_RESPONSE_BAD_REQUEST = 400,
 	HTTP_RESPONSE_UNAUTHORIZED = 401,
 	HTTP_RESPONSE_PAYMENT_REQUIRED = 402,
 	HTTP_RESPONSE_FORBIDDEN = 403,
 	HTTP_RESPONSE_NOT_FOUND = 404,
 	HTTP_RESPONSE_METHOD_NOT_ALLOWED = 405,
 	HTTP_RESPONSE_NOT_ACCEPTABLE = 406,
 	HTTP_RESPONSE_PROXY_AUTHENTICATION_REQUIRED = 407,
 	HTTP_RESPONSE_REQUEST_TIME_TOU = 408,
 	HTTP_RESPONSE_CONFLICT = 409,
 	HTTP_RESPONSE_GONE = 410,
 	HTTP_RESPONSE_LENGTH_REQUIRED = 411,
 	HTTP_RESPONSE_PRECONDITION_FAILED = 412,
 	HTTP_RESPONSE_REQUEST_ENTITY_TO_LARGE = 413,
 	HTTP_RESPONSE_REQUEST_URI_TOO_LARGE = 414,
 	HTTP_RESPONSE_UNSUPPORTED_MEDIA_TYPE = 415,
 	HTTP_RESPONSE_REQUESTED_RANGE_NOT_SATISFIABLE = 416,
 	HTTP_RESPONSE_EXPECTATION_FAILED = 417,
 	HTTP_RESPONSE_INTERNAL_SERVER_ERROR = 500,
 	HTTP_RESPONSE_NOT_IMPLEMENTED = 501,
    HTTP_RESPONSE_BAD_GATEWAY = 502,
 	HTTP_RESPONSE_SERVICE_UNAVAILABLE = 503,
 	HTTP_RESPONSE_GATEWAY_TIME_OUT = 504,
 	HTTP_RESPONSE_VERSION_NOT_SUPPORTED = 505,
};


DECLARE_SIMPLE_CLASS(HttpPacket) {

public:
    _HttpPacket();
    
    void setHeader(HttpHeader);
    
    HttpHeader getHeader();

    void setBody(ByteArray);
    
    void setUrl(String);
    
    String getUrl();

    void setReason(String);
    
    String getReason();

    void setMethod(int);

    int getMethod();

    void setMajorVersion(int);

    int getMajorVersion();

    void setMinorVersion(int);

    int getMinorVersion();

    int getStatusCode();

    void setStatusCode(int);

    String getStatusString(int);

    String genHttpRequest();

    String genHttpResponse();

private:
    String mUrl;
    
    HttpHeader mHeader;
    
    HttpCookie mCookie;

    ByteArray mBody;

    String mReason;

    int mMethod;

    int mMajorVer;

    int mMinorVer;

    int mStatusCode;

};

}
#endif
