#ifndef __OBOTCHA_HTTP_METHOD_HPP__
#define __OBOTCHA_HTTP_METHOD_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HttpHeader.hpp"
#include "ByteArray.hpp"
#include "HttpCookie.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpMethod) {

public:

    const static int Delete = HTTP_DELETE;

    const static int Get = HTTP_GET;
    const static int Head = HTTP_HEAD;
    const static int Post = HTTP_POST;
    const static int Put = HTTP_PUT;
    /* pathological */
    const static int Connect = HTTP_CONNECT;
    const static int Options = HTTP_OPTIONS;
    const static int Trace = HTTP_TRACE;
    /* webdav */
    const static int Copy = HTTP_COPY;
    const static int Lock = HTTP_LOCK;
    const static int Mkcol = HTTP_MKCOL;
    const static int Move = HTTP_MOVE;
    const static int PropFind = HTTP_PROPFIND;
    const static int PropPatch = HTTP_PROPPATCH;
    const static int Unlock = HTTP_UNLOCK;
    /* subversion */
    const static int Report = HTTP_REPORT;
    const static int MkActivity = HTTP_MKACTIVITY;
    const static int CheckOut = HTTP_CHECKOUT;
    const static int Merge = HTTP_MERGE;
    /* upnp */
    const static int Msearch = HTTP_MSEARCH;
    const static int Notify = HTTP_NOTIFY;
    const static int Subscribe = HTTP_SUBSCRIBE;
    const static int UnSubscribe = HTTP_UNSUBSCRIBE;
    /* RFC-5789 */
    const static int Patch = HTTP_PATCH;

    const static String GetMethodString;
    const static String DeleteMethodString;
    const static String PostMethodString;
    const static String PutMethodString;
    
    static String toString(int);

};

}
#endif
