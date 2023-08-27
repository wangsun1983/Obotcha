#include "Log.hpp"
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

String _HttpMethod::toString(Id method) {
    switch (method) {
        case Id::Delete:
            return DeleteString;

        case Id::Get:
            return GetString;

        case Id::Head:
            return HeadString;

        case Id::Post:
            return PostString;

        case Id::Put:
            return PutString;

        case Id::Connect:
            return ConnectString;

        case Id::Options:
            return OptionsString;

        case Id::Trace:
            return TraceString;

        case Id::Copy:
            return CopyString;

        case Id::Lock:
            return LockString;

        case Id::Mkcol:
            return MkcolString;

        case Id::Move:
            return MoveString;

        case Id::PropFind:
            return PropFindString;

        case Id::PropPatch:
            return PropPatchString;

        case Id::Unlock:
            return UnlockString;

        case Id::Report:
            return ReportString;

        case Id::MkActivity:
            return MkActivityString;

        case Id::Checkout:
            return CheckoutString;

        case Id::Merge:
            return MergeString;

        case Id::Search:
            return SearchString;
            
        case Id::Msearch:
            return MsearchString;

        case Id::Notify:
            return NotifyString;

        case Id::Subscribe:
            return SubscribeString;

        case Id::UnSubscribe:
            return UnSubscribeString;

        case Id::Patch:
            return PatchString;

        case Id::Link:
            return LinkString;

        case Id::Purge:
            return PurgeString;

        case Id::Unlink:
            return UnlinkString;

        case Id::Source:
            return SourceString;

        case Id::Pri:
            return PriString;

        default:
            //do nothoing
            LOG(ERROR)<<"HttpMethod toString unknow method"<<static_cast<int>(method);
    }
}

_HttpMethod::Id _HttpMethod::toId(String method) {
    static std::once_flag s_flag;
    method = method->toUpperCase();
    std::call_once(s_flag, []() {
        mMethodNames = createHashMap<String,Integer>();
        mMethodNames->put(DeleteString,     createInteger(static_cast<int>(Id::Delete)));
        mMethodNames->put(GetString,        createInteger(static_cast<int>(Id::Get)));
        mMethodNames->put(HeadString,       createInteger(static_cast<int>(Id::Head)));
        mMethodNames->put(PostString,       createInteger(static_cast<int>(Id::Post)));
        mMethodNames->put(PutString,        createInteger(static_cast<int>(Id::Put)));
        mMethodNames->put(ConnectString,    createInteger(static_cast<int>(Id::Connect)));
        mMethodNames->put(OptionsString,    createInteger(static_cast<int>(Id::Options)));
        mMethodNames->put(TraceString,      createInteger(static_cast<int>(Id::Trace)));
        mMethodNames->put(CopyString,       createInteger(static_cast<int>(Id::Copy)));
        mMethodNames->put(LockString,       createInteger(static_cast<int>(Id::Lock)));
        mMethodNames->put(MkcolString,      createInteger(static_cast<int>(Id::Mkcol)));
        mMethodNames->put(MoveString,       createInteger(static_cast<int>(Id::Move)));
        mMethodNames->put(PropFindString,   createInteger(static_cast<int>(Id::PropFind)));
        mMethodNames->put(PropPatchString,  createInteger(static_cast<int>(Id::PropPatch)));
        mMethodNames->put(UnlockString,     createInteger(static_cast<int>(Id::Unlock)));
        mMethodNames->put(ReportString,     createInteger(static_cast<int>(Id::Report)));
        mMethodNames->put(MkActivityString, createInteger(static_cast<int>(Id::MkActivity)));
        mMethodNames->put(CheckoutString,   createInteger(static_cast<int>(Id::Checkout)));
        mMethodNames->put(MergeString,      createInteger(static_cast<int>(Id::Merge)));
        mMethodNames->put(MsearchString,    createInteger(static_cast<int>(Id::Msearch)));
        mMethodNames->put(NotifyString,     createInteger(static_cast<int>(Id::Notify)));
        mMethodNames->put(SubscribeString,  createInteger(static_cast<int>(Id::Subscribe)));
        mMethodNames->put(UnSubscribeString,createInteger(static_cast<int>(Id::UnSubscribe)));
        mMethodNames->put(PatchString,      createInteger(static_cast<int>(Id::Patch)));
        mMethodNames->put(PurgeString,      createInteger(static_cast<int>(Id::Purge)));
        mMethodNames->put(LinkString,       createInteger(static_cast<int>(Id::Link)));
        mMethodNames->put(SearchString,     createInteger(static_cast<int>(Id::Search)));
        mMethodNames->put(UnlinkString,     createInteger(static_cast<int>(Id::Unlink)));
        mMethodNames->put(SourceString,     createInteger(static_cast<int>(Id::Source)));
        mMethodNames->put(PriString,        createInteger(static_cast<int>(Id::Pri)));
    });

    auto val = mMethodNames->get(method);
    return (val != nullptr)?static_cast<Id>(val->toValue()):Id::Err;
}

} // namespace obotcha