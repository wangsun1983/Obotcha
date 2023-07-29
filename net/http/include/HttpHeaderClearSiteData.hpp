#ifndef __OBOTCHA_HTTP_CLEAR_SITE_DATA_HPP__
#define __OBOTCHA_HTTP_CLEAR_SITE_DATA_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderClearSiteData) {

public:
    _HttpHeaderClearSiteData() = default;
    explicit _HttpHeaderClearSiteData(String);

    void load(String);

    String toString();

    bool isCache() const;
    bool isCookies() const;
    bool isExecutionContexts() const;
    bool isStorage() const;
    
    void setCache(bool);
    void setCookies(bool);
    void setExecutionContexts(bool);
    void setStorage(bool);

private:
    static const String Cache;
    static const String Cookies;
    static const String ExecutionContexts;
    static const String Storage;

    bool mCache = false;
    bool mCookies = false;
    bool mExecutionContexts = false;
    bool mStorage = false;

};

}
#endif
