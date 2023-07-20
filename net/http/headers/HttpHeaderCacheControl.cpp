#include "HttpHeaderCacheControl.hpp"
#include "HttpHeader.hpp"
#include "HttpHeaderContentParser.hpp"
#include "HttpText.hpp"
#include "HttpPacket.hpp"
#include "StringBuffer.hpp"

namespace obotcha {

const String _HttpHeaderCacheControl::NoCache = createString("no-cache");
const String _HttpHeaderCacheControl::NoStore = createString("no-store");
const String _HttpHeaderCacheControl::MaxAge = createString("max-age");
const String _HttpHeaderCacheControl::SMaxAge = createString("s-maxage");
const String _HttpHeaderCacheControl::CachePrivate = createString("private");
const String _HttpHeaderCacheControl::CachePublic = createString("public");
const String _HttpHeaderCacheControl::MustRevalidate = createString("must-revalidate");
const String _HttpHeaderCacheControl::MaxStale = createString("max-stale");
const String _HttpHeaderCacheControl::MinFresh = createString("min-fresh");
const String _HttpHeaderCacheControl::OnlyIfCached = createString("only-if-cached");
const String _HttpHeaderCacheControl::NotTransform = createString("no-transform");

_HttpHeaderCacheControl::_HttpHeaderCacheControl() {
    mNoCache = false;
    mNoStore = false;
    mMaxAgeSeconds = -1;
    mSMaxAgeSeconds = -1;
    mState = State::NotSet;
    mMustRevalidate = false;
    mMaxStaleSeconds = -1;
    mMinFreshSeconds = -1;
    mOnlyIfCached = false;
    mNoTransform = false;
}

_HttpHeaderCacheControl::_HttpHeaderCacheControl(String s):_HttpHeaderCacheControl() {
    load(s);
}

bool _HttpHeaderCacheControl::noCache() { 
    return this->mNoCache; 
}

bool _HttpHeaderCacheControl::noStore() { 
    return this->mNoStore; 
}

int _HttpHeaderCacheControl::maxAgeSeconds() { 
    return this->mMaxAgeSeconds; 
}

int _HttpHeaderCacheControl::sMaxAgeSeconds() { 
    return this->mSMaxAgeSeconds; 
}

bool _HttpHeaderCacheControl::isPrivate() { 
    return mState == State::Private; 
}

bool _HttpHeaderCacheControl::isPublic() { 
    return mState == State::Public;
}

bool _HttpHeaderCacheControl::mustRevalidate() { 
    return this->mMustRevalidate; 
}

int _HttpHeaderCacheControl::maxStaleSeconds() { 
    return this->mMaxStaleSeconds; 
}

int _HttpHeaderCacheControl::minFreshSeconds() { 
    return this->mMinFreshSeconds; 
}

bool _HttpHeaderCacheControl::onlyIfCached() { 
    return this->mOnlyIfCached;
}

bool _HttpHeaderCacheControl::noTransform() { 
    return this->mNoTransform; 
}

void _HttpHeaderCacheControl::load(String value) {
    st(HttpHeaderContentParser)::load(value,[this](String directive,String parameter) {
        if (NoCache->equalsIgnoreCase(directive)) {
            mNoCache = true;
        } else if (NoStore->equalsIgnoreCase(directive)) {
            mNoStore = true;
        } else if (MaxAge->equalsIgnoreCase(directive)) {
            mMaxAgeSeconds =
                st(HttpHeaderContentParser)::parseSeconds(parameter, -1);
        } else if (SMaxAge->equalsIgnoreCase(directive)) {
            mSMaxAgeSeconds =
                st(HttpHeaderContentParser)::parseSeconds(parameter, -1);
        } else if (CachePrivate->equalsIgnoreCase(directive)) {
            mState = State::Private;
        } else if (CachePublic->equalsIgnoreCase(directive)) {
            mState = State::Public;
        } else if (MustRevalidate->equalsIgnoreCase(directive)) {
            mMustRevalidate = true;
        } else if (MaxStale->equalsIgnoreCase(directive)) {
            mMaxStaleSeconds = st(HttpHeaderContentParser)::parseSeconds(
                parameter, st(Integer)::MAX_VALUE);
        } else if (MinFresh->equalsIgnoreCase(directive)) {
            mMinFreshSeconds =
                st(HttpHeaderContentParser)::parseSeconds(parameter, -1);
        } else if (OnlyIfCached->equalsIgnoreCase(directive)) {
            mOnlyIfCached = true;
        } else if (NotTransform->equalsIgnoreCase(directive)) {
            mNoTransform = true;
        }
    });
}

void _HttpHeaderCacheControl::setNoCache(bool v) {
    this->mNoCache = v;
}

void _HttpHeaderCacheControl::setNoStore(bool v) {
    this->mNoStore = v;
}

void _HttpHeaderCacheControl::setMaxAgeSeconds(int v) {
    this->mMaxAgeSeconds = v;
}

void _HttpHeaderCacheControl::setSMaxAgeSeconds(int v) {
    this->mSMaxAgeSeconds = v;
}

void _HttpHeaderCacheControl::setPrivate() {
    mState = State::Private;
}

void _HttpHeaderCacheControl::setPublic() {
    mState = State::Public;
}

void _HttpHeaderCacheControl::setMustRevalidate(bool v) {
    this->mMustRevalidate = v;
}

void _HttpHeaderCacheControl::setMaxStaleSeconds(int v) {
    this->mMaxStaleSeconds = v;
}

void _HttpHeaderCacheControl::setMinFreshSeconds(int v) {
    this->mMinFreshSeconds = v;
}

void _HttpHeaderCacheControl::setOnlyIfCached(bool v) {
    this->mOnlyIfCached = v;
}

void _HttpHeaderCacheControl::setNoTransform(bool v) {
    this->mNoTransform = v;
}

String _HttpHeaderCacheControl::toString(int type) {
    StringBuffer result = createStringBuffer();

    if(mNoCache) {
        result->append(NoCache,",");
    }

    if (mNoStore) {
        result->append(NoStore,",");
    }

    if(mMaxAgeSeconds != -1) {
        result->append(MaxAge,"=",createString(mMaxAgeSeconds),",");
    }

    if(mMaxStaleSeconds != -1) {
        result->append(MaxStale,"=",createString(mMaxStaleSeconds),",");
    }

    if(mMinFreshSeconds!= -1 && type == st(HttpPacket)::Request) {
        result->append(MaxStale,"=",createString(mMaxStaleSeconds),",");
    }

    if(mOnlyIfCached && type == st(HttpPacket)::Request) {
        result->append(OnlyIfCached,",");
    }

    if(mNoTransform) {
        result->append(NotTransform,",");
    }

    if(mState == State::Public && type == st(HttpPacket)::Response) {
        result->append(CachePublic,",");
    }
    
    if(mState == State::Private && type == st(HttpPacket)::Response) {
        result->append(CachePrivate,",");
    }

    if(mMustRevalidate && type == st(HttpPacket)::Response) {
        result->append(MustRevalidate,",");
    }

    if(mSMaxAgeSeconds != -1 && type == st(HttpPacket)::Response) {
        result->append(SMaxAge,"=",createString(mSMaxAgeSeconds),",");
    }

    if(result->size() > 0) {
        return result->toString(0,result->size() - 1);
    }

    return nullptr;
}

} // namespace obotcha
