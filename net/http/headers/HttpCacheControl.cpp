#include "HttpCacheControl.hpp"
#include "HttpHeader.hpp"
#include "HttpHeaderContentParser.hpp"
#include "HttpProtocol.hpp"
#include "HttpText.hpp"

namespace obotcha {

const String _HttpCacheControl::NoCache = createString("no-cache");
const String _HttpCacheControl::NoStore = createString("no-store");
const String _HttpCacheControl::MaxAge = createString("max-age");
const String _HttpCacheControl::SMaxAge = createString("s-maxage");
const String _HttpCacheControl::CachePrivate = createString("private");
const String _HttpCacheControl::CachePublic = createString("public");
const String _HttpCacheControl::MustRevalidate = createString("must-revalidate");
const String _HttpCacheControl::MaxStale = createString("max-stale");
const String _HttpCacheControl::MinFresh = createString("min-fresh");
const String _HttpCacheControl::OnlyIfCached = createString("only-if-cached");
const String _HttpCacheControl::NotTransform = createString("no-transform");

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
}

_HttpCacheControl::_HttpCacheControl(String s):_HttpCacheControl() {
    import(s);
}

bool _HttpCacheControl::noCache() { return this->mNoCache; }

bool _HttpCacheControl::noStore() { return this->mNoStore; }

int _HttpCacheControl::maxAgeSeconds() { return this->mMaxAgeSeconds; }

int _HttpCacheControl::sMaxAgeSeconds() { return this->mSMaxAgeSeconds; }

bool _HttpCacheControl::isPrivate() { return this->mIsPrivate; }

bool _HttpCacheControl::isPublic() { return this->mIsPublic; }

bool _HttpCacheControl::mustRevalidate() { return this->mMustRevalidate; }

int _HttpCacheControl::maxStaleSeconds() { return this->mMaxStaleSeconds; }

int _HttpCacheControl::minFreshSeconds() { return this->mMinFreshSeconds; }

bool _HttpCacheControl::onlyIfCached() { return this->mOnlyIfCached; }

bool _HttpCacheControl::noTransform() { return this->mNoTransform; }

void _HttpCacheControl::import(String value) {
    st(HttpHeaderContentParser)::import(value,[this](String directive,String parameter) {
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
            mIsPrivate = true;
        } else if (CachePublic->equalsIgnoreCase(directive)) {
            mIsPublic = true;
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

void _HttpCacheControl::setNoCache(bool v) {
    this->mNoCache = v;
}

void _HttpCacheControl::setNoStore(bool v) {
    this->mNoStore = v;
}

void _HttpCacheControl::setMaxAgeSeconds(int v) {
    this->mMaxAgeSeconds = v;
}

void _HttpCacheControl::setSMaxAgeSeconds(int v) {
    this->mSMaxAgeSeconds = v;
}

void _HttpCacheControl::setPrivate() {
    this->mIsPrivate = true;
    this->mIsPublic = false;
}

void _HttpCacheControl::setPublic() {
    this->mIsPrivate = false;
    this->mIsPublic = true;
}

void _HttpCacheControl::setMustRevalidate(bool v) {
    this->mMustRevalidate = v;
}

void _HttpCacheControl::setMaxStaleSeconds(int v) {
    this->mMaxStaleSeconds = v;
}

void _HttpCacheControl::setMinFreshSeconds(int v) {
    this->mMinFreshSeconds = v;
}

void _HttpCacheControl::setOnlyIfCached(bool v) {
    this->mOnlyIfCached = v;
}

void _HttpCacheControl::setNoTransform(bool v) {
    this->mNoTransform = v;
}


String _HttpCacheControl::toString(int type) {
    String result = createString("");

    if(mNoCache) {
        result = result->append(NoCache,",");
    }

    if (mNoStore) {
        result = result->append(NoStore,",");
    }

    if(mMaxAgeSeconds != -1) {
        result = result->append(MaxAge,"=",createString(mMaxAgeSeconds),",");
    }

    if(mMaxStaleSeconds != -1) {
        result = result->append(MaxStale,"=",createString(mMaxStaleSeconds),",");
    }

    if(mMinFreshSeconds!= -1 && type == st(HttpProtocol)::HttpRequest) {
        result = result->append(MaxStale,"=",createString(mMaxStaleSeconds),",");
    }

    if(mOnlyIfCached && type == st(HttpProtocol)::HttpRequest) {
        result = result->append(OnlyIfCached,",");
    }

    if(mNoTransform) {
        result = result->append(NotTransform,",");
    }

    if(mIsPublic && type == st(HttpProtocol)::HttpResponse) {
        result = result->append(CachePublic,",");
    }
    
    if(mIsPrivate && type == st(HttpProtocol)::HttpResponse) {
        result = result->append(CachePrivate,",");
    }

    if(mMustRevalidate && type == st(HttpProtocol)::HttpResponse) {
        result = result->append(MustRevalidate,",");
    }

    if(mSMaxAgeSeconds != -1 && type == st(HttpProtocol)::HttpResponse) {
        result = result->append(SMaxAge,"=",createString(mSMaxAgeSeconds),",");
    }

    if(result->size() > 0) {
        return result->subString(0,result->size() - 1);
    }

    return result;
}

} // namespace obotcha
