#ifndef __OBOTCHA_HTTP_METHOD_HPP__
#define __OBOTCHA_HTTP_METHOD_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "HttpHeader.hpp"
#include "ByteArray.hpp"
#include "HttpCookie.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpMethod) {

public:
    enum ID {
        Delete = 0,
        Get,
        Head,
        Post,
        Put,
        /* pathological */
        Connect,
        Options,
        Trace,
        /* webdav */
        Copy,
        Lock,
        Mkcol,
        Move,
        PropFind,
        PropPatch,
        Unlock,
        /* subversion */
        Report,
        MkActivity,
        Checkout,
        Merge,
        /* upnp */
        Msearch,
        Notify,
        Subscribe,
        UnSubscribe,
        /* RFC-5789 */
        Patch,
        Purge,
        Link,
        Search,
        Unlink,
        Source
    };

    const static String DeleteString;
    const static String GetString;
    const static String PutString;
    const static String HeadString;
    const static String PostString;
    const static String ConnectString;
    const static String OptionsString;
    const static String TraceString;
    /* webdav */
    const static String CopyString;
    const static String LockString;
    const static String MkcolString;
    const static String MoveString;
    const static String PropFindString;
    const static String PropPatchString;
    const static String UnlockString;
    /* subversion */
    const static String ReportString;
    const static String MkActivityString;
    const static String CheckoutString;
    const static String MergeString;
    /* upnp */
    const static String MsearchString;
    const static String NotifyString;
    const static String SubscribeString;
    const static String UnSubscribeString;
    /* RFC-5789 */
    const static String PatchString;
    const static String PurgeString;
    const static String LinkString;
    const static String SearchString;
    const static String UnlinkString;
    const static String SourceString;
    
    static String toString(int);
    int toInt(String method);

};

}
#endif
