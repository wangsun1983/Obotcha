#include "Object.hpp"
#include "StrongPointer.hpp"

#include "HttpMethodParser.hpp"
#include "HttpHeader.hpp"

namespace obotcha {

int _HttpMethodParser::doParse(String method) {
    const char *p = method->toChars();
    switch(p[0]) {
        case 'D':{
            if(method->equals(st(HttpHeader)::MethodDelete)){
                return st(HttpHeader)::DELETE;
            }
            return -1;
        }

        case 'G': {
            if(method->equals(st(HttpHeader)::MethodGet)){
                return st(HttpHeader)::GET;
            }
            return -1;
        }

        case 'H': {
            if(method->equals(st(HttpHeader)::MethodHead)){
                return st(HttpHeader)::HEAD;
            }
            return -1;
        }

        case 'P': {
            if(method->equals(st(HttpHeader)::MethodPost)){
                return st(HttpHeader)::POST;
            } else if(method->equals(st(HttpHeader)::MethodPut)){
                return st(HttpHeader)::PUT;
            } else if(method->equals(st(HttpHeader)::MethodPatch)){
                return st(HttpHeader)::PATCH;
            } else if(method->equals(st(HttpHeader)::MethodPropFind)){
                return st(HttpHeader)::PROPFIND;
            } else if(method->equals(st(HttpHeader)::MethodPropPatch)){
                return st(HttpHeader)::PROPPATCH;
            }
            return -1;
        }

        case 'C': {
            if(method->equals(st(HttpHeader)::MethodConnect)){
                return st(HttpHeader)::CONNECT;
            } else if(method->equals(st(HttpHeader)::MethodCopy)){
                return st(HttpHeader)::COPY;
            } else if(method->equals(st(HttpHeader)::MethodCheckOut)){
                return st(HttpHeader)::CHECKOUT;
            }
            return -1;
        }

        case 'O': {
            if(method->equals(st(HttpHeader)::MethodOptions)){
                return st(HttpHeader)::OPTIONS;
            }
            return -1;
        }

        case 'T': {
            if(method->equals(st(HttpHeader)::MethodTrace)){
                return st(HttpHeader)::TRACE;
            }
            return -1;
        }

        case 'L': {
            if(method->equals(st(HttpHeader)::MethodLock)){
                return st(HttpHeader)::LOCK;
            }
            return -1;
        }

        case 'M': {
            if(method->equals(st(HttpHeader)::MethodMkCol)){
                return st(HttpHeader)::MKCOL;
            } else if(method->equals(st(HttpHeader)::MethodMove)){
                return st(HttpHeader)::MOVE;
            } else if(method->equals(st(HttpHeader)::MethodMkActivity)){
                return st(HttpHeader)::MKACTIVITY;
            } else if(method->equals(st(HttpHeader)::MethodMerge)){
                return st(HttpHeader)::MERGE;
            } else if(method->equals(st(HttpHeader)::MethodMSearch)){
                return st(HttpHeader)::MSEARCH;
            }
            return -1;
        }

        case 'U': {
            if(method->equals(st(HttpHeader)::MethodUnlock)){
                return st(HttpHeader)::UNLOCK;
            }
            return -1;
        }

        case 'R': {
            if(method->equals(st(HttpHeader)::MethodReport)){
                return st(HttpHeader)::REPORT;
            }
            return -1;
        }

        case 'N': {
            if(method->equals(st(HttpHeader)::MethodNotify)){
                return st(HttpHeader)::NOTIFY;
            }
            return -1;
        }

        case 'S': {
            if(method->equals(st(HttpHeader)::MethodSubscribe)){
                return st(HttpHeader)::SUBSCRIBE;
            }
            return -1;
        }
    }
    return -1;
}

String _HttpMethodParser::doParse(int method) {
    switch(method) {
        case st(HttpHeader)::DELETE: return st(HttpHeader)::MethodDelete;
        case st(HttpHeader)::GET: return st(HttpHeader)::MethodGet;
        case st(HttpHeader)::HEAD: return st(HttpHeader)::MethodHead;
        case st(HttpHeader)::POST: return st(HttpHeader)::MethodPost;
        case st(HttpHeader)::PUT: return st(HttpHeader)::MethodPut;
        case st(HttpHeader)::CONNECT: return st(HttpHeader)::MethodConnect;
        case st(HttpHeader)::OPTIONS: return st(HttpHeader)::MethodOptions;
        case st(HttpHeader)::TRACE: return st(HttpHeader)::MethodTrace;
        case st(HttpHeader)::COPY: return st(HttpHeader)::MethodCopy;
        case st(HttpHeader)::LOCK: return st(HttpHeader)::MethodLock;
        case st(HttpHeader)::MKCOL: return st(HttpHeader)::MethodMkCol;
        case st(HttpHeader)::MOVE: return st(HttpHeader)::MethodMove;
        case st(HttpHeader)::PROPFIND: return st(HttpHeader)::MethodPropFind;
        case st(HttpHeader)::PROPPATCH: return st(HttpHeader)::MethodPropPatch;
        case st(HttpHeader)::UNLOCK: return st(HttpHeader)::MethodUnlock;
        case st(HttpHeader)::REPORT: return st(HttpHeader)::MethodReport;
        case st(HttpHeader)::MKACTIVITY: return st(HttpHeader)::MethodMkActivity;
        case st(HttpHeader)::CHECKOUT: return st(HttpHeader)::MethodCheckOut;
        case st(HttpHeader)::MERGE: return st(HttpHeader)::MethodMerge;
        case st(HttpHeader)::MSEARCH: return st(HttpHeader)::MethodMSearch;
        case st(HttpHeader)::NOTIFY: return st(HttpHeader)::MethodNotify;
        case st(HttpHeader)::SUBSCRIBE: return st(HttpHeader)::MethodSubscribe;
        case st(HttpHeader)::UNSUBSCRIBE: return st(HttpHeader)::MethodUnSubscribe;
        case st(HttpHeader)::PATCH: return st(HttpHeader)::MethodPatch;
    }

    return nullptr;
}

}
