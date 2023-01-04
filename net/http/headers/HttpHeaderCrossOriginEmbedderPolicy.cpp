#include "HttpHeaderCrossOriginEmbedderPolicy.hpp"

namespace obotcha {

const String _HttpHeaderCrossOriginEmbedderPolicy::UnSafeNone = createString("unsafe-none");
const String _HttpHeaderCrossOriginEmbedderPolicy::RequireCorp = createString("require-corp");

_HttpHeaderCrossOriginEmbedderPolicy::_HttpHeaderCrossOriginEmbedderPolicy() {
    mType = -1;
}

_HttpHeaderCrossOriginEmbedderPolicy::_HttpHeaderCrossOriginEmbedderPolicy(String s) {
    import(s);
}

void _HttpHeaderCrossOriginEmbedderPolicy::import(String s) {
    auto policy = s->trim();
    if(policy->equalsIgnoreCase(UnSafeNone)) {
        mType = TypeUnSafeNone;
    } else if(policy->equalsIgnoreCase(RequireCorp)) {
        mType = TypeRequireCorp;
    }
}

bool _HttpHeaderCrossOriginEmbedderPolicy::isUnSafeNone() {
    return mType == TypeUnSafeNone;
}

bool _HttpHeaderCrossOriginEmbedderPolicy::isRequireCorp() {
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
    }

    return nullptr;
}


}
