#ifndef __HTTP_PACKET_HPP__
#define __HTTP_PACKET_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HttpHeader.hpp"
#include "ByteArray.hpp"

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

    String genHttpString();

    

private:
    String mUrl;
    
    HttpHeader mHeader;
    
    ByteArray mBody;

    String mReason;

    int mMethod;

    int mMajorVer;

    int mMinorVer;

    int mStatusCode;

};

}
#endif
