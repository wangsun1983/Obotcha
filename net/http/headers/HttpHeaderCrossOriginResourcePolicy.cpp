#include "HttpHeaderCrossOriginResourcePolicy.hpp"
#include "Log.hpp"

namespace obotcha {

const String _HttpHeaderCrossOriginResourcePolicy::SameSite = String::New("same-site");
const String _HttpHeaderCrossOriginResourcePolicy::SameOrigin = String::New("same-origin");
const String _HttpHeaderCrossOriginResourcePolicy::CrossOrigin = String::New("cross-origin");

_HttpHeaderCrossOriginResourcePolicy::_HttpHeaderCrossOriginResourcePolicy(String s) {
    load(s);
}

void _HttpHeaderCrossOriginResourcePolicy::load(String s) {
    auto policy = s->trim();
    if(policy->equalsIgnoreCase(SameSite)) {
        mType = TypeSameSite;
    } else if(policy->equalsIgnoreCase(SameOrigin)) {
        mType = TypeSameOrigin;
    } else if(policy->equalsIgnoreCase(CrossOrigin)) {
        mType = TypeCrossOrigin;
    }
}

bool _HttpHeaderCrossOriginResourcePolicy::isSameSite() const {
    return mType == TypeSameSite;
}

bool _HttpHeaderCrossOriginResourcePolicy::isSameOrigin() const {
    return mType == TypeSameOrigin;
}

bool _HttpHeaderCrossOriginResourcePolicy::isCrossOrigin() const {
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
        
        default:
            LOG(ERROR)<<"HttpHeaderCrossOriginResourcePolicy,toString unknow type:"<<mType;
            return nullptr;
    }
}

}
