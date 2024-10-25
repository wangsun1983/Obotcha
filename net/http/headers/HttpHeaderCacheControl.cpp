#include "HttpHeaderCacheControl.hpp"
#include "HttpHeaderContentParser.hpp"
#include "StringBuffer.hpp"

namespace obotcha {

const String _HttpHeaderCacheControl::NoCache = String::New("no-cache");
const String _HttpHeaderCacheControl::NoStore = String::New("no-store");
const String _HttpHeaderCacheControl::MaxAge = String::New("max-age");
const String _HttpHeaderCacheControl::SMaxAge = String::New("s-maxage");
const String _HttpHeaderCacheControl::CachePrivate = String::New("private");
const String _HttpHeaderCacheControl::CachePublic = String::New("public");
const String _HttpHeaderCacheControl::MustRevalidate = String::New("must-revalidate");
const String _HttpHeaderCacheControl::MaxStale = String::New("max-stale");
const String _HttpHeaderCacheControl::MinFresh = String::New("min-fresh");
const String _HttpHeaderCacheControl::OnlyIfCached = String::New("only-if-cached");
const String _HttpHeaderCacheControl::NotTransform = String::New("no-transform");

_HttpHeaderCacheControl::_HttpHeaderCacheControl(String s) {
    load(s);
}

bool _HttpHeaderCacheControl::noCache() const { 
    return this->mNoCache; 
}

bool _HttpHeaderCacheControl::noStore() const { 
    return this->mNoStore; 
}

int _HttpHeaderCacheControl::maxAgeSeconds() const { 
    return this->mMaxAgeSeconds; 
}

int _HttpHeaderCacheControl::sMaxAgeSeconds() const { 
    return this->mSMaxAgeSeconds; 
}

bool _HttpHeaderCacheControl::isPrivate() const { 
    return mState == State::Private; 
}

bool _HttpHeaderCacheControl::isPublic() const { 
    return mState == State::Public;
}

bool _HttpHeaderCacheControl::mustRevalidate() const { 
    return this->mMustRevalidate; 
}

int _HttpHeaderCacheControl::maxStaleSeconds() const { 
    return this->mMaxStaleSeconds; 
}

int _HttpHeaderCacheControl::minFreshSeconds() const { 
    return this->mMinFreshSeconds; 
}

bool _HttpHeaderCacheControl::onlyIfCached() const { 
    return this->mOnlyIfCached;
}

bool _HttpHeaderCacheControl::noTransform() const { 
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
                parameter, st(Integer)::kMaxValue);
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

String _HttpHeaderCacheControl::toString(st(Http)::PacketType type) {
    StringBuffer result = StringBuffer::New();

    if(mNoCache) {
        result->append(NoCache,",");
    }

    if (mNoStore) {
        result->append(NoStore,",");
    }

    if(mMaxAgeSeconds != -1) {
        result->append(MaxAge,"=",String::New(mMaxAgeSeconds),",");
    }

    if(mMaxStaleSeconds != -1) {
        result->append(MaxStale,"=",String::New(mMaxStaleSeconds),",");
    }

    if(mMinFreshSeconds!= -1 && type == st(Http)::PacketType::Request) {
        result->append(MaxStale,"=",String::New(mMaxStaleSeconds),",");
    }

    if(mOnlyIfCached && type == st(Http)::PacketType::Request) {
        result->append(OnlyIfCached,",");
    }

    if(mNoTransform) {
        result->append(NotTransform,",");
    }

    if(mState == State::Public && type == st(Http)::PacketType::Response) {
        result->append(CachePublic,",");
    }
    
    if(mState == State::Private && type == st(Http)::PacketType::Response) {
        result->append(CachePrivate,",");
    }

    if(mMustRevalidate && type == st(Http)::PacketType::Response) {
        result->append(MustRevalidate,",");
    }

    if(mSMaxAgeSeconds != -1 && type == st(Http)::PacketType::Response) {
        result->append(SMaxAge,"=",String::New(mSMaxAgeSeconds),",");
    }

    if(result->size() > 0) {
        return result->toString(0,result->size() - 1);
    }

    return nullptr;
}

} // namespace obotcha
