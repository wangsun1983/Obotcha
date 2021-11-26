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

String _HttpMethod::toString(int method) {
    return findString(method);
}

String _HttpMethod::findString(int method) {
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

int _HttpMethod::findId(String m) {
    const char *p = m->toChars();
    for (int i = 0; i < m->size(); i++) {
        if ((*p <= 'Z' && *p >= 'A') || (*p <= 'z' && *p >= 'a')) {
            break;
        }
        p++;
    }

    String method = createString(p);
    switch (p[0]) {
    case 'D': {
        if (method->equals(st(HttpMethod)::DeleteString)) {
            return st(HttpMethod)::Delete;
        }
        return -1;
    }

    case 'G': {
        if (method->equals(st(HttpMethod)::GetString)) {
            return st(HttpMethod)::Get;
        }
        return -1;
    }

    case 'H': {
        if (method->equals(st(HttpMethod)::HeadString)) {
            return st(HttpMethod)::Head;
        }
        return -1;
    }

    case 'P': {
        if (method->equals(st(HttpMethod)::PostString)) {
            return st(HttpMethod)::Post;
        } else if (method->equals(st(HttpMethod)::PutString)) {
            return st(HttpMethod)::Put;
        } else if (method->equals(st(HttpMethod)::PatchString)) {
            return st(HttpMethod)::Patch;
        } else if (method->equals(st(HttpMethod)::PropFindString)) {
            return st(HttpMethod)::PropFind;
        } else if (method->equals(st(HttpMethod)::PropPatchString)) {
            return st(HttpMethod)::PropPatch;
        } else if (method->equals(st(HttpMethod)::PurgeString)) {
            return st(HttpMethod)::Purge;
        } else if (method->equals(st(HttpMethod)::PriString)) {
            return st(HttpMethod)::Pri;
        }
        return -1;
    }

    case 'C': {
        if (method->equals(st(HttpMethod)::ConnectString)) {
            return st(HttpMethod)::Connect;
        } else if (method->equals(st(HttpMethod)::CopyString)) {
            return st(HttpMethod)::Copy;
        } else if (method->equals(st(HttpMethod)::CheckoutString)) {
            return st(HttpMethod)::Checkout;
        }
        return -1;
    }

    case 'O': {
        if (method->equals(st(HttpMethod)::OptionsString)) {
            return st(HttpMethod)::Options;
        }
        return -1;
    }

    case 'T': {
        if (method->equals(st(HttpMethod)::TraceString)) {
            return st(HttpMethod)::Trace;
        }
        return -1;
    }

    case 'L': {
        if (method->equals(st(HttpMethod)::LockString)) {
            return st(HttpMethod)::Lock;
        } else if (method->equals(st(HttpMethod)::LinkString)) {
            return st(HttpMethod)::Link;
        }
        return -1;
    }

    case 'M': {
        if (method->equals(st(HttpMethod)::MkcolString)) {
            return st(HttpMethod)::Mkcol;
        } else if (method->equals(st(HttpMethod)::MoveString)) {
            return st(HttpMethod)::Move;
        } else if (method->equals(st(HttpMethod)::MkActivityString)) {
            return st(HttpMethod)::MkActivity;
        } else if (method->equals(st(HttpMethod)::MergeString)) {
            return st(HttpMethod)::Merge;
        } else if (method->equals(st(HttpMethod)::MsearchString)) {
            return st(HttpMethod)::Msearch;
        }
        return -1;
    }

    case 'U': {
        if (method->equals(st(HttpMethod)::UnlockString)) {
            return st(HttpMethod)::Unlock;
        } else if (method->equals(st(HttpMethod)::UnlinkString)) {
            return st(HttpMethod)::Unlink;
        }
        return -1;
    }

    case 'R': {
        if (method->equals(st(HttpMethod)::ReportString)) {
            return st(HttpMethod)::Report;
        }
        return -1;
    }

    case 'N': {
        if (method->equals(st(HttpMethod)::NotifyString)) {
            return st(HttpMethod)::Notify;
        }
        return -1;
    }

    case 'S': {
        if (method->equals(st(HttpMethod)::SubscribeString)) {
            return st(HttpMethod)::Subscribe;
        } else if (method->equals(st(HttpMethod)::SearchString)) {
            return st(HttpMethod)::Search;
        } else if (method->equals(st(HttpMethod)::SourceString)) {
            return st(HttpMethod)::Source;
        }
        return -1;
    }
    }
    return -1;
}

} // namespace obotcha