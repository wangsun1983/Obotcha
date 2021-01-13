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

const String _HttpMethod::DELETE = createString("DELETE");
const String _HttpMethod::GET = createString("GET");
const String _HttpMethod::PUT = createString("PUT");
const String _HttpMethod::HEAD = createString("HEAD");
const String _HttpMethod::LOCK = createString("LOCK");
const String _HttpMethod::POST = createString("POST");
const String _HttpMethod::CONNECT = createString("CONNECT");
const String _HttpMethod::OPTIONS = createString("OPTIONS");
const String _HttpMethod::TRACE = createString("TRACE");
const String _HttpMethod::COPY = createString("COPY");
const String _HttpMethod::MKCOL = createString("MKCOL");
const String _HttpMethod::MOVE = createString("MOVE");
const String _HttpMethod::PROPFIND = createString("PROPFIND");
const String _HttpMethod::PROPPATCH = createString("PROPPATCH");
const String _HttpMethod::UNLOCK = createString("UNLOCK");
const String _HttpMethod::REPORT = createString("REPORT");
const String _HttpMethod::MKACTIVITY = createString("MKACTIVITY");
const String _HttpMethod::CHECKOUT = createString("CHECKOUT");
const String _HttpMethod::MERGE = createString("MERGE");
const String _HttpMethod::MSEARCH = createString("MSEARCH");
const String _HttpMethod::NOTIFY = createString("NOTIFY");
const String _HttpMethod::SUBSCRIBE = createString("SUBSCRIBE");
const String _HttpMethod::UNSUBSCRIBE = createString("UNSUBSCRIBE");
const String _HttpMethod::PATCH = createString("PATCH");

String _HttpMethod::toString(int method) {
    switch(method) {
        case Delete:
        return DELETE;

        case Get:
        return GET;

        case Head:
        return HEAD;

        case Post:
        return POST;

        case Put:
        return PUT;

        case Connect:
        return CONNECT;

        case Options:
        return OPTIONS;

        case Trace:
        return TRACE;

        case Copy:
        return COPY;

        case Lock:
        return LOCK;

        case Mkcol:
        return MKCOL;

        case Move:
        return MOVE;

        case PropFind:
        return PROPFIND;

        case PropPatch:
        return PROPPATCH;

        case Unlock:
        return UNLOCK;

        case Report:
        return REPORT;

        case MkActivity:
        return MKACTIVITY;

        case CheckOut:
        return CHECKOUT;

        case Merge:
        return MERGE;

        case Msearch:
        return MSEARCH;

        case Notify:
        return NOTIFY;

        case Subscribe:
        return SUBSCRIBE;

        case UnSubscribe:
        return UNSUBSCRIBE;

        case Patch:
        return PATCH;
    }

    return nullptr;
}

int _HttpMethod::toInt(String method) {
    if(method->equals(GET)) {
        return Get;
    } else if(method->equals(PUT)) {
        return Put;
    } else if(method->equals(POST)) {
        return Post;
    } else if(method->equals(HEAD)) {
        return Head;
    } else if(method->equals(OPTIONS)) {
        return Options;
    } else if(method->equals(PATCH)) {
        return Patch;
    } else if(method->equals(TRACE)) {
        return Trace;
    } else if(method->equals(CONNECT)) {
        return Connect;
    }

    return -1;
}

}