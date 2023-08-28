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
HashMap<int,String> _HttpMethod::mMethodIds = nullptr;

String _HttpMethod::toString(Id method) {
    if(mMethodIds == nullptr) {
        init();
    }
    
    return mMethodIds->get(static_cast<int>(method));
}

_HttpMethod::Id _HttpMethod::toId(String method) {
    method = method->toUpperCase();
    if(mMethodNames == nullptr) {
        init();
    }

    auto val = mMethodNames->get(method);
    return (val != nullptr)?static_cast<Id>(val->toValue()):Id::Err;
}

void _HttpMethod::init() {
    static std::once_flag s_flag;

#define METHOD_MAP_SETUP(str,id) \
    mMethodNames->put(str,createInteger(id));\
    mMethodIds->put(id,str);

    std::call_once(s_flag, []() {
        mMethodNames = createHashMap<String,Integer>();
        mMethodIds = createHashMap<int,String>();
        METHOD_MAP_SETUP(DeleteString,     static_cast<int>(Id::Delete))
        METHOD_MAP_SETUP(GetString,        static_cast<int>(Id::Get))
        METHOD_MAP_SETUP(HeadString,       static_cast<int>(Id::Head))
        METHOD_MAP_SETUP(PostString,       static_cast<int>(Id::Post))
        METHOD_MAP_SETUP(PutString,        static_cast<int>(Id::Put))
        METHOD_MAP_SETUP(ConnectString,    static_cast<int>(Id::Connect))
        METHOD_MAP_SETUP(OptionsString,    static_cast<int>(Id::Options))
        METHOD_MAP_SETUP(TraceString,      static_cast<int>(Id::Trace))
        METHOD_MAP_SETUP(CopyString,       static_cast<int>(Id::Copy))
        METHOD_MAP_SETUP(LockString,       static_cast<int>(Id::Lock))
        METHOD_MAP_SETUP(MkcolString,      static_cast<int>(Id::Mkcol))
        METHOD_MAP_SETUP(MoveString,       static_cast<int>(Id::Move))
        METHOD_MAP_SETUP(PropFindString,   static_cast<int>(Id::PropFind))
        METHOD_MAP_SETUP(PropPatchString,  static_cast<int>(Id::PropPatch))
        METHOD_MAP_SETUP(UnlockString,     static_cast<int>(Id::Unlock))
        METHOD_MAP_SETUP(ReportString,     static_cast<int>(Id::Report))
        METHOD_MAP_SETUP(MkActivityString, static_cast<int>(Id::MkActivity))
        METHOD_MAP_SETUP(CheckoutString,   static_cast<int>(Id::Checkout))
        METHOD_MAP_SETUP(MergeString,      static_cast<int>(Id::Merge))
        METHOD_MAP_SETUP(MsearchString,    static_cast<int>(Id::Msearch))
        METHOD_MAP_SETUP(NotifyString,     static_cast<int>(Id::Notify))
        METHOD_MAP_SETUP(SubscribeString,  static_cast<int>(Id::Subscribe))
        METHOD_MAP_SETUP(UnSubscribeString,static_cast<int>(Id::UnSubscribe))
        METHOD_MAP_SETUP(PatchString,      static_cast<int>(Id::Patch))
        METHOD_MAP_SETUP(PurgeString,      static_cast<int>(Id::Purge))
        METHOD_MAP_SETUP(LinkString,       static_cast<int>(Id::Link))
        METHOD_MAP_SETUP(SearchString,     static_cast<int>(Id::Search))
        METHOD_MAP_SETUP(UnlinkString,     static_cast<int>(Id::Unlink))
        METHOD_MAP_SETUP(SourceString,     static_cast<int>(Id::Source))
        METHOD_MAP_SETUP(PriString,        static_cast<int>(Id::Pri))
    });

#undef METHOD_MAP_SETUP


}

} // namespace obotcha