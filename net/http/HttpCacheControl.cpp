#include "HttpCacheControl.hpp"
#include "HttpHeader.hpp"
#include "HttpHeaderContentParser.hpp"

namespace obotcha {

const String _HttpCacheControl::NoCache = createString("no-cache");
const String _HttpCacheControl::NoStore = createString("no-store");
const String _HttpCacheControl::MaxAge = createString("max-age");
const String _HttpCacheControl::SMaxAge = createString("s-maxage");
const String _HttpCacheControl::CachePrivate = createString("private");
const String _HttpCacheControl::CachePublic = createString("public");
const String _HttpCacheControl::MustRevalidate =
    createString("must-revalidate");
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
    mHeaderValue = nullptr;
}

_HttpCacheControl::_HttpCacheControl(String value) {
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
    import(value);
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
    if (value != nullptr) {
        int pos = 0;
        while (pos < value->size()) {
            int tokenStart = pos;
            pos = st(HttpHeaderContentParser)::skipUntil(value, pos,
                                                         createString("=,;"));
            String directive =
                value->subString(tokenStart, pos - tokenStart)->trim();
            String parameter;

            if (pos == value->size() || value->charAt(pos) == ',' ||
                value->charAt(pos) == ';') {
                pos++; // consume ',' or ';' (if necessary)
                parameter = nullptr;
            } else {
                pos++; // consume '='
                pos = st(HttpHeaderContentParser)::skipWhitespace(value, pos);
                // quoted string
                if (pos < value->size() && value->charAt(pos) == '\"') {
                    pos++; // consume '"' open quote
                    int parameterStart = pos;
                    pos = st(HttpHeaderContentParser)::skipUntil(
                        value, pos, createString("\""));
                    parameter = value->subString(parameterStart, pos);
                    pos++; // consume '"' close quote (if necessary)
                    // unquoted string
                } else {
                    int parameterStart = pos;
                    pos = st(HttpHeaderContentParser)::skipUntil(
                        value, pos, createString(",;"));
                    parameter =
                        value->subString(parameterStart, (pos - parameterStart))
                            ->trim();
                    pos++;
                }
            }

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
        }
    }
}

void _HttpCacheControl::import(sp<_HttpHeader> headers) {
    //bool canUseHeaderValue = true;
    String value = headers->getValue(st(HttpHeader)::CacheControl);
    import(value);
}

String _HttpCacheControl::toString() {
    String result = createString("");
    if (mNoCache) {
        result = result->append("no-cache, ");
    }

    if (mNoStore) {
        result = result->append("no-store, ");
    }

    if (mMaxAgeSeconds != -1) {
        result = result->append("max-age=", createString(mMaxAgeSeconds), ", ");
    }

    if (mSMaxAgeSeconds != -1) {
        result =
            result->append("s-maxage=", createString(mSMaxAgeSeconds), ", ");
    }

    if (mIsPrivate) {
        result = result->append("private, ");
    }

    if (mIsPublic) {
        result = result->append("public, ");
    }

    if (mMustRevalidate) {
        result = result->append("must-revalidate, ");
    }

    if (mMaxStaleSeconds != -1) {
        result =
            result->append("max-stale=", createString(mMaxStaleSeconds), ", ");
    }

    if (mMinFreshSeconds != -1) {
        result =
            result->append("min-fresh=", createString(mMinFreshSeconds), ", ");
    }

    if (mOnlyIfCached) {
        result = result->append("only-if-cached, ");
    }

    if (mNoTransform) {
        result = result->append("no-transform, ");
    }

    if (result->size() == 0) {
        return createString("");
    }

    return result->subString(0, result->size() - 2);
}

} // namespace obotcha
