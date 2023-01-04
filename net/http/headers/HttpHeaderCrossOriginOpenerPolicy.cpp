#include "HttpHeaderCrossOriginOpenerPolicy.hpp"

namespace obotcha {

const String _HttpHeaderCrossOriginOpenerPolicy::UnSafeNone = createString("unsafe-none");
const String _HttpHeaderCrossOriginOpenerPolicy::SameOrigin = createString("same-origin");
const String _HttpHeaderCrossOriginOpenerPolicy::SameOriginAllowPopups = createString("same-origin-allow-popups");

_HttpHeaderCrossOriginOpenerPolicy::_HttpHeaderCrossOriginOpenerPolicy() {
    mType = -1;
}

_HttpHeaderCrossOriginOpenerPolicy::_HttpHeaderCrossOriginOpenerPolicy(String s) {
    import(s);
}

void _HttpHeaderCrossOriginOpenerPolicy::import(String s) {
    auto policy = s->trim();
    if(policy->equalsIgnoreCase(UnSafeNone)) {
        mType = TypeUnSafeNone;
    } else if(policy->equalsIgnoreCase(SameOrigin)) {
        mType = TypeSameOrigin;
    } else if(policy->equalsIgnoreCase(SameOriginAllowPopups)) {
        mType = TypeSameOriginAllowPopups;
    }
}

bool _HttpHeaderCrossOriginOpenerPolicy::isUnSafeNone() {
    return mType == TypeUnSafeNone;
}

bool _HttpHeaderCrossOriginOpenerPolicy::isSameOrigin() {
    return mType == TypeSameOrigin;
}

bool _HttpHeaderCrossOriginOpenerPolicy::isSameOriginAllowPopups() {
    return mType == TypeSameOriginAllowPopups;
}

void _HttpHeaderCrossOriginOpenerPolicy::setAsUnSafeNone() {
    mType = TypeUnSafeNone;
}

void _HttpHeaderCrossOriginOpenerPolicy::setAsSameOrigin() {
    mType = TypeSameOrigin;
}

void _HttpHeaderCrossOriginOpenerPolicy::setAsSameOriginAllowPopups() {
    mType = TypeSameOriginAllowPopups;
}

String _HttpHeaderCrossOriginOpenerPolicy::toString() {
    switch(mType) {
        case TypeUnSafeNone:
            return UnSafeNone;

        case TypeSameOrigin:
            return SameOrigin;

        case TypeSameOriginAllowPopups:
            return SameOriginAllowPopups;
    }

    return nullptr;
}


}
