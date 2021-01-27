#ifndef __OBOTCHA_HTTP_CACHE_CONTROL_HPP__
#define __OBOTCHA_HTTP_CACHE_CONTROL_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"

namespace obotcha {

class _HttpHeader;

DECLARE_SIMPLE_CLASS(HttpCacheControl) {

public:
    _HttpCacheControl();
    _HttpCacheControl(String);
    /**
     * In a response, this field's name "no-cache" is misleading. It doesn't
     * prevent us from caching the response; it only means we have to validate the
     * response with the origin server before returning it. We can do this with a
     * conditional GET.
     *
     * <p>In a request, it means do not use a cache to satisfy the request.
     */
    bool noCache();
    
    /** If true, this response should not be cached. */
    bool noStore();

    /**
     * The duration past the response's served date that it can be served without
     * validation.
     */
    int maxAgeSeconds();

    /**
     * The "s-maxage" directive is the max age for shared caches. Not to be
     * confused with "max-age" for non-shared caches, As in Firefox and Chrome,
     * this directive is not honored by this cache.
     */
    int sMaxAgeSeconds();

    bool isPrivate();

    bool isPublic();

    bool mustRevalidate();

    int maxStaleSeconds();

    int minFreshSeconds();

    /**
     * This field's name "only-if-cached" is misleading. It actually means "do
     * not use the network". It is set by a client who only wants to make a
     * request if it can be fully satisfied by the cache. Cached responses that
     * would require validation (ie. conditional gets) are not permitted if this
     * header is set.
     */
    bool onlyIfCached();

    bool noTransform();

    void import(sp<_HttpHeader> headers);
    void import(String value);

    String toString();

    static const String NoCache;
    static const String NoStore;
    static const String MaxAge;
    static const String SMaxAge;
    static const String CachePrivate;
    static const String CachePublic;
    static const String MustRevalidate;
    static const String MaxStale;
    static const String MinFresh;
    static const String OnlyIfCached;
    static const String NotTransform;

private:
    bool mNoCache;
    bool mNoStore;
    int mMaxAgeSeconds;
    int mSMaxAgeSeconds;
    bool mIsPrivate;
    bool mIsPublic;
    bool mMustRevalidate;
    int mMaxStaleSeconds;
    int mMinFreshSeconds;
    bool mOnlyIfCached;
    bool mNoTransform;
    String mHeaderValue;
};

}
#endif
