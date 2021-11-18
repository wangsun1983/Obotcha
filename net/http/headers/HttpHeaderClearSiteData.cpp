#include "HttpHeaderClearSiteData.hpp"
#include "HttpHeaderContentParser.hpp"
#include "StringBuffer.hpp"

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
        String predict = createString(directive->toChars(),1,directive->size() - 2); //trim \"\"
        if(Cache->equalsIgnoreCase(predict)) {
            mCache = true;
        } else if(Cookies->equalsIgnoreCase(predict)){
            mCookies = true;
        } else if(ExecutionContexts->equalsIgnoreCase(predict)){
            mExecutionContexts = true;
        } else if(Storage->equalsIgnoreCase(predict)){
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
    StringBuffer type = createStringBuffer();
    printf("start toString \n");
    if(mCache) {
        printf("to 1\n");
        type->append("\"",Cache,"\",");
    }

    if(mCookies) {
        printf("to 2\n");
        type->append("\"",Cookies,"\",");
    }

    if(mExecutionContexts) {
        printf("to 3\n");
        type->append("\"",ExecutionContexts,"\",");
    }

    if(mStorage) {
        printf("to 4\n");
        type->append("\"",Storage,"\",");
    }

    return type->toString(0,type->size() - 1);
}
}
