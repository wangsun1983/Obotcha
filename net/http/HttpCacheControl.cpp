#include "HttpCacheControl.hpp"

namespace obotcha {

_HttpCacheControl::_HttpCacheControl() {
    mNoCache = false;
    mNoStore = false;
    mMaxAgeSeconds = -1;
    mSMaxAgeSeconds = -1;
    mIsPrivate = false;
    mIsPublic = false;
    mMustRevalidate = false;
    mMaxStaleSeconds = -1;
    mMinFreshSeconds = -1;
    mOnlyIfCached = false;
    mNoTransform = false;
    mHeaderValue = nullptr;
}

bool _HttpCacheControl::noCache() {
    return this->mNoCache;
}
    
bool _HttpCacheControl::noStore() {
    return this->mNoStore;
}

int _HttpCacheControl::maxAgeSeconds() {
    return this->mMaxAgeSeconds;
}

int _HttpCacheControl::sMaxAgeSeconds() {
    return this->mSMaxAgeSeconds;
}

bool _HttpCacheControl::isPrivate() {
    return this->mIsPrivate;
}

bool _HttpCacheControl::isPublic() {
    return this->mIsPublic;
}

bool _HttpCacheControl::mustRevalidate() {
    return this->mMustRevalidate;
}

int _HttpCacheControl::maxStaleSeconds() {
    return this->mMaxStaleSeconds;
}

int _HttpCacheControl::minFreshSeconds() {
    return this->mMinFreshSeconds;
}

bool _HttpCacheControl::onlyIfCached() {
    return this->mOnlyIfCached;
}

bool _HttpCacheControl::noTransform() {
    return this->mNoTransform;
}

void _HttpCacheControl::import(sp<_HttpHeader> headers) {
    
}

}
