#ifndef __OBOTCHA_HTTP_CLEAR_SITE_DATA_HPP__
#define __OBOTCHA_HTTP_CLEAR_SITE_DATA_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderClearSiteData) {

public:
    _HttpHeaderClearSiteData();
    explicit _HttpHeaderClearSiteData(String);

    void load(String);

    String toString();

    bool isCache();
    bool isCookies();
    bool isExecutionContexts();
    bool isStorage();
    
    void setCache(bool);
    void setCookies(bool);
    void setExecutionContexts(bool);
    void setStorage(bool);

private:
    static const String Cache;
    static const String Cookies;
    static const String ExecutionContexts;
    static const String Storage;

    bool mCache;
    bool mCookies;
    bool mExecutionContexts;
    bool mStorage;

};

}
#endif
