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

    const static String GetMethodString;
    const static String DeleteMethodString;
    const static String PostMethodString;
    const static String PutMethodString;
    
    static String toString(int);

};

}
#endif
