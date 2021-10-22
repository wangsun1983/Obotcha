#ifndef __OBOTCHA_HTTP_CLEAR_SITE_DATA_HPP__
#define __OBOTCHA_HTTP_CLEAR_SITE_DATA_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpClearSiteData) {

public:
    _HttpClearSiteData();
    _HttpClearSiteData(String);

    void import(String);

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
