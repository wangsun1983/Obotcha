#include "HttpHeaderCrossOriginEmbedderPolicy.hpp"
#include "Log.hpp"

namespace obotcha {

const String _HttpHeaderCrossOriginEmbedderPolicy::UnSafeNone = createString("unsafe-none");
const String _HttpHeaderCrossOriginEmbedderPolicy::RequireCorp = createString("require-corp");

_HttpHeaderCrossOriginEmbedderPolicy::_HttpHeaderCrossOriginEmbedderPolicy(String s) {
    load(s);
}

void _HttpHeaderCrossOriginEmbedderPolicy::load(String s) {
    auto policy = s->trim();
    if(policy->equalsIgnoreCase(UnSafeNone)) {
        mType = TypeUnSafeNone;
    } else if(policy->equalsIgnoreCase(RequireCorp)) {
        mType = TypeRequireCorp;
    }
}

bool _HttpHeaderCrossOriginEmbedderPolicy::isUnSafeNone() const {
    return mType == TypeUnSafeNone;
}

bool _HttpHeaderCrossOriginEmbedderPolicy::isRequireCorp() const {
    return mType == TypeRequireCorp;
}

void _HttpHeaderCrossOriginEmbedderPolicy::setAsUnSafeNone() {
    mType = TypeUnSafeNone;
}

void _HttpHeaderCrossOriginEmbedderPolicy::setAsRequireCorp() {
    mType = TypeRequireCorp;
}

String _HttpHeaderCrossOriginEmbedderPolicy::toString() {
    switch(mType) {
        case TypeUnSafeNone:
            return UnSafeNone;
        case TypeRequireCorp:
            return RequireCorp;
        
        default:
            LOG(ERROR)<<"HttpHeaderCrossOriginEmbedderPolicy toString,unknow type:"
                      << mType;
            return nullptr;
    }
}


}
