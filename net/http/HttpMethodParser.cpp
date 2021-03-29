#include "Object.hpp"
#include "StrongPointer.hpp"

#include "HttpMethodParser.hpp"
#include "HttpMethod.hpp"

namespace obotcha {

int _HttpMethodParser::doParse(String m) {
    const char *p = m->toChars();
    for(int i = 0;i < m->size();i++) {
        if((*p <= 'Z' && *p >= 'A') || (*p <= 'z' && *p >= 'a')) {
            break;
        }
        p++;
    }

    String method = createString(p);
    switch(p[0]) {
        case 'D':{
            if(method->equals(st(HttpMethod)::DeleteString)){
                return st(HttpMethod)::Delete;
            }
            return -1;
        }

        case 'G': {
            if(method->equals(st(HttpMethod)::GetString)){
                return st(HttpMethod)::Get;
            }
            return -1;
        }

        case 'H': {
            if(method->equals(st(HttpMethod)::HeadString)){
                return st(HttpMethod)::Head;
            }
            return -1;
        }

        case 'P': {
            if(method->equals(st(HttpMethod)::PostString)){
                return st(HttpMethod)::Post;
            } else if(method->equals(st(HttpMethod)::PutString)){
                return st(HttpMethod)::Put;
            } else if(method->equals(st(HttpMethod)::PatchString)){
                return st(HttpMethod)::Patch;
            } else if(method->equals(st(HttpMethod)::PropFindString)){
                return st(HttpMethod)::PropFind;
            } else if(method->equals(st(HttpMethod)::PropPatchString)){
                return st(HttpMethod)::PropPatch;
            } else if(method->equals(st(HttpMethod)::PurgeString)){
                return st(HttpMethod)::Purge;
            }
            return -1;
        }

        case 'C': {
            if(method->equals(st(HttpMethod)::ConnectString)){
                return st(HttpMethod)::Connect;
            } else if(method->equals(st(HttpMethod)::CopyString)){
                return st(HttpMethod)::Copy;
            } else if(method->equals(st(HttpMethod)::CheckoutString)){
                return st(HttpMethod)::Checkout;
            }
            return -1;
        }

        case 'O': {
            if(method->equals(st(HttpMethod)::OptionsString)){
                return st(HttpMethod)::Options;
            }
            return -1;
        }

        case 'T': {
            if(method->equals(st(HttpMethod)::TraceString)){
                return st(HttpMethod)::Trace;
            }
            return -1;
        }

        case 'L': {
            if(method->equals(st(HttpMethod)::LockString)){
                return st(HttpMethod)::Lock;
            } else if(method->equals(st(HttpMethod)::LinkString)){
                return st(HttpMethod)::Link;
            }
            return -1;
        }

        case 'M': {
            if(method->equals(st(HttpMethod)::MkcolString)){
                return st(HttpMethod)::Mkcol;
            } else if(method->equals(st(HttpMethod)::MoveString)){
                return st(HttpMethod)::Move;
            } else if(method->equals(st(HttpMethod)::MkActivityString)){
                return st(HttpMethod)::MkActivity;
            } else if(method->equals(st(HttpMethod)::MergeString)){
                return st(HttpMethod)::Merge;
            } else if(method->equals(st(HttpMethod)::MsearchString)){
                return st(HttpMethod)::Msearch;
            }
            return -1;
        }

        case 'U': {
            if(method->equals(st(HttpMethod)::UnlockString)){
                return st(HttpMethod)::Unlock;
            } else if(method->equals(st(HttpMethod)::UnlinkString)) {
                return st(HttpMethod)::Unlink;
            }
            return -1;
        }

        case 'R': {
            if(method->equals(st(HttpMethod)::ReportString)){
                return st(HttpMethod)::Report;
            }
            return -1;
        }

        case 'N': {
            if(method->equals(st(HttpMethod)::NotifyString)){
                return st(HttpMethod)::Notify;
            }
            return -1;
        }

        case 'S': {
            if(method->equals(st(HttpMethod)::SubscribeString)){
                return st(HttpMethod)::Subscribe;
            } else if(method->equals(st(HttpMethod)::SearchString)){
                return st(HttpMethod)::Search;
            } else if(method->equals(st(HttpMethod)::SourceString)) {
                return st(HttpMethod)::Source;
            }
            return -1;
        }
    }
    return -1;
}

String _HttpMethodParser::doParse(int method) {
    switch(method) {
        case st(HttpMethod)::Delete: return st(HttpMethod)::DeleteString;
        case st(HttpMethod)::Get: return st(HttpMethod)::GetString;
        case st(HttpMethod)::Head: return st(HttpMethod)::HeadString;
        case st(HttpMethod)::Post: return st(HttpMethod)::PostString;
        case st(HttpMethod)::Put: return st(HttpMethod)::PutString;
        case st(HttpMethod)::Connect: return st(HttpMethod)::ConnectString;
        case st(HttpMethod)::Options: return st(HttpMethod)::OptionsString;
        case st(HttpMethod)::Trace: return st(HttpMethod)::TraceString;
        case st(HttpMethod)::Copy: return st(HttpMethod)::CopyString;
        case st(HttpMethod)::Lock: return st(HttpMethod)::LockString;
        case st(HttpMethod)::Mkcol: return st(HttpMethod)::MkcolString;
        case st(HttpMethod)::Move: return st(HttpMethod)::MoveString;
        case st(HttpMethod)::PropFind: return st(HttpMethod)::PropFindString;
        case st(HttpMethod)::PropPatch: return st(HttpMethod)::PropPatchString;
        case st(HttpMethod)::Unlock: return st(HttpMethod)::UnlockString;
        case st(HttpMethod)::Report: return st(HttpMethod)::ReportString;
        case st(HttpMethod)::MkActivity: return st(HttpMethod)::MkActivityString;
        case st(HttpMethod)::Checkout: return st(HttpMethod)::CheckoutString;
        case st(HttpMethod)::Merge: return st(HttpMethod)::MergeString;
        case st(HttpMethod)::Msearch: return st(HttpMethod)::MsearchString;
        case st(HttpMethod)::Notify: return st(HttpMethod)::NotifyString;
        case st(HttpMethod)::Subscribe: return st(HttpMethod)::SubscribeString;
        case st(HttpMethod)::UnSubscribe: return st(HttpMethod)::UnSubscribeString;
        case st(HttpMethod)::Patch: return st(HttpMethod)::PatchString;
        case st(HttpMethod)::Purge: return st(HttpMethod)::PurgeString;
        case st(HttpMethod)::Link: return st(HttpMethod)::LinkString;
        case st(HttpMethod)::Search: return st(HttpMethod)::SearchString;
        case st(HttpMethod)::Unlink: return st(HttpMethod)::UnlinkString;
        case st(HttpMethod)::Source: return st(HttpMethod)::SourceString;
    }

    return nullptr;
}

}
