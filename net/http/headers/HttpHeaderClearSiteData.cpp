#include "HttpHeaderClearSiteData.hpp"
#include "HttpHeaderContentParser.hpp"

namespace obotcha {

const String _HttpHeaderClearSiteData::Cache = "cache";
const String _HttpHeaderClearSiteData::Cookies = "cookies";
const String _HttpHeaderClearSiteData::ExecutionContexts = "executionContexts";
const String _HttpHeaderClearSiteData::Storage = "storage";

_HttpHeaderClearSiteData::_HttpHeaderClearSiteData() {
    mCache = false;
    mCookies = false;
    mExecutionContexts = false;
    mStorage = false;
}

_HttpHeaderClearSiteData::_HttpHeaderClearSiteData(String v):_HttpHeaderClearSiteData() {
    import(v);
}

void _HttpHeaderClearSiteData::import(String v) {
     st(HttpHeaderContentParser)::import(v,[this](String directive,String parameter) {
        if(Cache->equalsIgnoreCase(directive)) {
            mCache = true;
        } else if(Cookies->equalsIgnoreCase(directive)){
            mCookies = true;
        } else if(ExecutionContexts->equalsIgnoreCase(directive)){
            mExecutionContexts = true;
        } else if(Storage->equalsIgnoreCase(directive)){
            mStorage = true;
        }
    });
}

bool _HttpHeaderClearSiteData::isCache() {
    return mCache;
}

bool _HttpHeaderClearSiteData::isCookies() {
    return mCookies;
}

bool _HttpHeaderClearSiteData::isExecutionContexts() {
    return mExecutionContexts;
}

bool _HttpHeaderClearSiteData::isStorage() {
    return mStorage;
}

void _HttpHeaderClearSiteData::setCache(bool v) {
    mCache = v;
}

void _HttpHeaderClearSiteData::setCookies(bool v) {
    mCookies = v;
}

void _HttpHeaderClearSiteData::setExecutionContexts(bool v) {
    mExecutionContexts = v;
}

void _HttpHeaderClearSiteData::setStorage(bool v) {
    mStorage = v;
}


String _HttpHeaderClearSiteData::toString() {
    String type = "";
    if(mCache) {
        type = type->append("\"",Cache,"\",");
    }

    if(mCookies) {
        type = type->append("\"",Cookies,"\",");
    }

    if(mExecutionContexts) {
        type = type->append("\"",ExecutionContexts,"\",");
    }

    if(mStorage) {
        type = type->append("\"",Storage,"\",");
    }

    return type->subString(0,type->size() - 1);
}
}
