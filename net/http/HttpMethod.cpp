#include <mutex>

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
const String _HttpMethod::PriString = createString("PRI");

HashMap<String,Integer> _HttpMethod::mMethodNames = nullptr;

String _HttpMethod::toString(int method) {
    switch (method) {
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

        case Search:
            return SearchString;
            
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

        case Pri:
            return PriString;
    }

    return nullptr;
}

int _HttpMethod::toId(String method) {
    static std::once_flag s_flag;
    method = method->toUpperCase();
    std::call_once(s_flag, []() {
        mMethodNames = createHashMap<String,Integer>();
        mMethodNames->put(DeleteString,     createInteger(Delete));
        mMethodNames->put(GetString,        createInteger(Get));
        mMethodNames->put(HeadString,       createInteger(Head));
        mMethodNames->put(PostString,       createInteger(Post));
        mMethodNames->put(PutString,        createInteger(Put));
        mMethodNames->put(ConnectString,    createInteger(Connect));
        mMethodNames->put(OptionsString,    createInteger(Options));
        mMethodNames->put(TraceString,      createInteger(Trace));
        mMethodNames->put(CopyString,       createInteger(Copy));
        mMethodNames->put(LockString,       createInteger(Lock));
        mMethodNames->put(MkcolString,      createInteger(Mkcol));
        mMethodNames->put(MoveString,       createInteger(Move));
        mMethodNames->put(PropFindString,   createInteger(PropFind));
        mMethodNames->put(PropPatchString,  createInteger(PropPatch));
        mMethodNames->put(UnlockString,     createInteger(Unlock));
        mMethodNames->put(ReportString,     createInteger(Report));
        mMethodNames->put(MkActivityString, createInteger(MkActivity));
        mMethodNames->put(CheckoutString,   createInteger(Checkout));
        mMethodNames->put(MergeString,      createInteger(Merge));
        mMethodNames->put(MsearchString,    createInteger(Msearch));
        mMethodNames->put(NotifyString,     createInteger(Notify));
        mMethodNames->put(SubscribeString,  createInteger(Subscribe));
        mMethodNames->put(UnSubscribeString,createInteger(UnSubscribe));
        mMethodNames->put(PatchString,      createInteger(Patch));
        mMethodNames->put(PurgeString,      createInteger(Purge));
        mMethodNames->put(LinkString,       createInteger(Link));
        mMethodNames->put(SearchString,     createInteger(Search));
        mMethodNames->put(UnlinkString,     createInteger(Unlink));
        mMethodNames->put(SourceString,     createInteger(Source));
        mMethodNames->put(PriString,        createInteger(Pri));
    });

    auto val = mMethodNames->get(method);
    return (val != nullptr)?val->toValue():-1;
}

} // namespace obotcha