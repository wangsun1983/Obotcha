#include "HttpClearSiteData.hpp"
#include "HttpHeaderContentParser.hpp"

namespace obotcha {

const String _HttpClearSiteData::Cache = "cache";
const String _HttpClearSiteData::Cookies = "cookies";
const String _HttpClearSiteData::ExecutionContexts = "executionContexts";
const String _HttpClearSiteData::Storage = "storage";

_HttpClearSiteData::_HttpClearSiteData() {
    mCache = false;
    mCookies = false;
    mExecutionContexts = false;
    mStorage = false;
}

_HttpClearSiteData::_HttpClearSiteData(String v):_HttpClearSiteData() {
    import(v);
}

void _HttpClearSiteData::import(String v) {
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

bool _HttpClearSiteData::isCache() {
    return mCache;
}

bool _HttpClearSiteData::isCookies() {
    return mCookies;
}

bool _HttpClearSiteData::isExecutionContexts() {
    return mExecutionContexts;
}

bool _HttpClearSiteData::isStorage() {
    return mStorage;
}

void _HttpClearSiteData::setCache(bool v) {
    mCache = v;
}

void _HttpClearSiteData::setCookies(bool v) {
    mCookies = v;
}

void _HttpClearSiteData::setExecutionContexts(bool v) {
    mExecutionContexts = v;
}

void _HttpClearSiteData::setStorage(bool v) {
    mStorage = v;
}


String _HttpClearSiteData::toString() {
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
