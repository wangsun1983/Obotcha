#include "HttpHeaderCrossOriginResourcePolicy.hpp"

namespace obotcha {

const String _HttpHeaderCrossOriginResourcePolicy::SameSite = createString("same-site");
const String _HttpHeaderCrossOriginResourcePolicy::SameOrigin = createString("same-origin");
const String _HttpHeaderCrossOriginResourcePolicy::CrossOrigin = createString("cross-origin");

_HttpHeaderCrossOriginResourcePolicy::_HttpHeaderCrossOriginResourcePolicy() {
    mType = -1;
}

_HttpHeaderCrossOriginResourcePolicy::_HttpHeaderCrossOriginResourcePolicy(String s) {
    import(s);
}

void _HttpHeaderCrossOriginResourcePolicy::import(String s) {
    auto policy = s->trim();
    if(policy->equalsIgnoreCase(SameSite)) {
        mType = TypeSameSite;
    } else if(policy->equalsIgnoreCase(SameOrigin)) {
        mType = TypeSameOrigin;
    } else if(policy->equalsIgnoreCase(CrossOrigin)) {
        mType = TypeCrossOrigin;
    }
}

bool _HttpHeaderCrossOriginResourcePolicy::isSameSite() {
    return mType == TypeSameSite;
}

bool _HttpHeaderCrossOriginResourcePolicy::isSameOrigin() {
    return mType == TypeSameOrigin;
}

bool _HttpHeaderCrossOriginResourcePolicy::isCrossOrigin() {
    return mType == TypeCrossOrigin;
}

void _HttpHeaderCrossOriginResourcePolicy::setAsSameSite() {
    mType = TypeSameSite;
}

void _HttpHeaderCrossOriginResourcePolicy::setAsSameOrigin() {
    mType = TypeSameOrigin;
}

void _HttpHeaderCrossOriginResourcePolicy::setAsCrossOrigin() {
    mType = TypeCrossOrigin;
}

String _HttpHeaderCrossOriginResourcePolicy::toString() {
    switch(mType) {
        case TypeCrossOrigin:
            return CrossOrigin;

        case TypeSameOrigin:
            return SameOrigin;

        case TypeSameSite:
            return SameSite;
    }

    return nullptr;
}

}
