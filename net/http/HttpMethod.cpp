#include "HttpMethod.hpp"

namespace obotcha {

const int _HttpMethod::Delete = HTTP_DELETE;

const int _HttpMethod::Get = HTTP_GET;
const int _HttpMethod::Head = HTTP_HEAD;
const int _HttpMethod::Post = HTTP_POST;
const int _HttpMethod::Put = HTTP_PUT;
/* pathological */
const int _HttpMethod::Connect = HTTP_CONNECT;
const int _HttpMethod::Options = HTTP_OPTIONS;
const int _HttpMethod::Trace = HTTP_TRACE;
/* webdav */
const int _HttpMethod::Copy = HTTP_COPY;
const int _HttpMethod::Lock = HTTP_LOCK;
const int _HttpMethod::Mkcol = HTTP_MKCOL;
const int _HttpMethod::Move = HTTP_MOVE;
const int _HttpMethod::PropFind = HTTP_PROPFIND;
const int _HttpMethod::PropPatch = HTTP_PROPPATCH;
const int _HttpMethod::Unlock = HTTP_UNLOCK;
/* subversion */
const int _HttpMethod::Report = HTTP_REPORT;
const int _HttpMethod::MkActivity = HTTP_MKACTIVITY;
const int _HttpMethod::CheckOut = HTTP_CHECKOUT;
const int _HttpMethod::Merge = HTTP_MERGE;
/* upnp */
const int _HttpMethod::Msearch = HTTP_MSEARCH;
const int _HttpMethod::Notify = HTTP_NOTIFY;
const int _HttpMethod::Subscribe = HTTP_SUBSCRIBE;
const int _HttpMethod::UnSubscribe = HTTP_UNSUBSCRIBE;
/* RFC-5789 */
const int _HttpMethod::Patch = HTTP_PATCH;

const String _HttpMethod::GetMethodString = createString("GET");
const String _HttpMethod::DeleteMethodString = createString("DELETE");
const String _HttpMethod::PostMethodString = createString("POST");
const String _HttpMethod::PutMethodString = createString("PUT");

String _HttpMethod::toString(int method) {
    switch(method) {
        case Get:
        return GetMethodString;

        case Delete:
        return DeleteMethodString;

        case Post:
        return PostMethodString;

        case Put:
        return PutMethodString;
    }

    return nullptr;
}


}