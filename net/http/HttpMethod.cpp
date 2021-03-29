#include "HttpMethod.hpp"

namespace obotcha {

const String _HttpMethod::DeleteString = createString("DELETE");
const String _HttpMethod::GetString = createString("GET");
const String _HttpMethod::PutString = createString("PUT");
const String _HttpMethod::HeadString = createString("HEAD");
const String _HttpMethod::LockString = createString("LOCK");
const String _HttpMethod::PostString = createString("POST");
const String _HttpMethod::ConnectString = createString("CONNECT");
const String _HttpMethod::OptionsString = createString("OPTIONS");
const String _HttpMethod::TraceString = createString("TRACE");
const String _HttpMethod::CopyString = createString("COPY");
const String _HttpMethod::MkcolString = createString("MKCOL");
const String _HttpMethod::MoveString = createString("MOVE");
const String _HttpMethod::PropFindString = createString("PROPFIND");
const String _HttpMethod::PropPatchString = createString("PROPPATCH");
const String _HttpMethod::UnlockString = createString("UNLOCK");
const String _HttpMethod::ReportString = createString("REPORT");
const String _HttpMethod::MkActivityString = createString("MKACTIVITY");
const String _HttpMethod::CheckoutString = createString("CHECKOUT");
const String _HttpMethod::MergeString = createString("MERGE");
const String _HttpMethod::MsearchString = createString("M-SEARCH");
const String _HttpMethod::NotifyString = createString("NOTIFY");
const String _HttpMethod::SubscribeString = createString("SUBSCRIBE");
const String _HttpMethod::UnSubscribeString = createString("UNSUBSCRIBE");
const String _HttpMethod::PatchString = createString("PATCH");
const String _HttpMethod::PurgeString = createString("PURGE");
const String _HttpMethod::LinkString = createString("LINK");
const String _HttpMethod::SearchString = createString("SEARCH");
const String _HttpMethod::UnlinkString = createString("UNLINK");
const String _HttpMethod::SourceString = createString("SOURCE");

String _HttpMethod::toString(int method) {
    switch(method) {
        case Delete:
        return DeleteString;

        case Get:
        return GetString;

        case Head:
        return HeadString;

        case Post:
        return PostString;

        case Put:
        return PutString;

        case Connect:
        return ConnectString;

        case Options:
        return OptionsString;

        case Trace:
        return TraceString;

        case Copy:
        return CopyString;

        case Lock:
        return LockString;

        case Mkcol:
        return MkcolString;

        case Move:
        return MoveString;

        case PropFind:
        return PropFindString;

        case PropPatch:
        return PropPatchString;

        case Unlock:
        return UnlockString;

        case Report:
        return ReportString;

        case MkActivity:
        return MkActivityString;

        case Checkout:
        return CheckoutString;

        case Merge:
        return MergeString;

        case Msearch:
        return MsearchString;

        case Notify:
        return NotifyString;

        case Subscribe:
        return SubscribeString;

        case UnSubscribe:
        return UnSubscribeString;

        case Patch:
        return PatchString;

        case Link:
        return LinkString;

        case Purge:
        return PurgeString;

        case Unlink:
        return UnlinkString;

        case Source:
        return SourceString;
    }

    return nullptr;
}

int _HttpMethod::toInt(String method) {
    if(method->equals(GetString)) {
        return Get;
    } else if(method->equals(PutString)) {
        return Put;
    } else if(method->equals(PostString)) {
        return Post;
    } else if(method->equals(HeadString)) {
        return Head;
    } else if(method->equals(OptionsString)) {
        return Options;
    } else if(method->equals(PatchString)) {
        return Patch;
    } else if(method->equals(TraceString)) {
        return Trace;
    } else if(method->equals(ConnectString)) {
        return Connect;
    }
    //TODO

    return -1;
}

}