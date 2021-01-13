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
    const static int Delete;
    const static int Get;
    const static int Head;
    const static int Post;
    const static int Put;
    /* pathological */
    const static int Connect;
    const static int Options;
    const static int Trace;
    /* webdav */
    const static int Copy;
    const static int Lock;
    const static int Mkcol;
    const static int Move;
    const static int PropFind;
    const static int PropPatch;
    const static int Unlock;
    /* subversion */
    const static int Report;
    const static int MkActivity;
    const static int CheckOut;
    const static int Merge;
    /* upnp */
    const static int Msearch;
    const static int Notify;
    const static int Subscribe;
    const static int UnSubscribe;
    /* RFC-5789 */
    const static int Patch;

    const static String DELETE;
    const static String GET;
    const static String PUT;
    const static String HEAD;
    const static String POST;
    const static String CONNECT;
    const static String OPTIONS;
    const static String TRACE;
    /* webdav */
    const static String COPY;
    const static String LOCK;
    const static String MKCOL;
    const static String MOVE;
    const static String PROPFIND;
    const static String PROPPATCH;
    const static String UNLOCK;
    /* subversion */
    const static String REPORT;
    const static String MKACTIVITY;
    const static String CHECKOUT;
    const static String MERGE;
    /* upnp */
    const static String MSEARCH;
    const static String NOTIFY;
    const static String SUBSCRIBE;
    const static String UNSUBSCRIBE;
    /* RFC-5789 */
    const static String PATCH;
    
    
    static String toString(int);
    int toInt(String method);

};

}
#endif
