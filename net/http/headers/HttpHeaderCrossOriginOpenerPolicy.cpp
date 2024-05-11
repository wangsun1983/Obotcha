#include "HttpHeaderCrossOriginOpenerPolicy.hpp"
#include "Log.hpp"

namespace obotcha {

const String _HttpHeaderCrossOriginOpenerPolicy::UnSafeNone = String::New("unsafe-none");
const String _HttpHeaderCrossOriginOpenerPolicy::SameOrigin = String::New("same-origin");
const String _HttpHeaderCrossOriginOpenerPolicy::SameOriginAllowPopups = String::New("same-origin-allow-popups");

_HttpHeaderCrossOriginOpenerPolicy::_HttpHeaderCrossOriginOpenerPolicy(String s) {
    load(s);
}

void _HttpHeaderCrossOriginOpenerPolicy::load(String s) {
    auto policy = s->trim();
    if(policy->equalsIgnoreCase(UnSafeNone)) {
        mType = TypeUnSafeNone;
    } else if(policy->equalsIgnoreCase(SameOrigin)) {
        mType = TypeSameOrigin;
    } else if(policy->equalsIgnoreCase(SameOriginAllowPopups)) {
        mType = TypeSameOriginAllowPopups;
    }
}

bool _HttpHeaderCrossOriginOpenerPolicy::isUnSafeNone() const {
    return mType == TypeUnSafeNone;
}

bool _HttpHeaderCrossOriginOpenerPolicy::isSameOrigin() const {
    return mType == TypeSameOrigin;
}

bool _HttpHeaderCrossOriginOpenerPolicy::isSameOriginAllowPopups() const {
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
        
        default:
            LOG(ERROR)<<"HttpHeaderCrossOriginOpenerPolicy,toString unknow type is "<<mType;
            return nullptr;
    }
}


}
