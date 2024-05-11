#include "HttpHeaderClearSiteData.hpp"
#include "HttpHeaderContentParser.hpp"
#include "StringBuffer.hpp"

namespace obotcha {

const String _HttpHeaderClearSiteData::Cache = "cache";
const String _HttpHeaderClearSiteData::Cookies = "cookies";
const String _HttpHeaderClearSiteData::ExecutionContexts = "executionContexts";
const String _HttpHeaderClearSiteData::Storage = "storage";

_HttpHeaderClearSiteData::_HttpHeaderClearSiteData(String v) {
    load(v);
}

void _HttpHeaderClearSiteData::load(String v) {
     st(HttpHeaderContentParser)::load(v,
        [this](String directive,[[maybe_unused]]String parameter) {
            String predict = String::New(directive->toChars(),1,directive->size() - 2); //trim \"\"
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

bool _HttpHeaderClearSiteData::isCache() const {
    return mCache;
}

bool _HttpHeaderClearSiteData::isCookies() const {
    return mCookies;
}

bool _HttpHeaderClearSiteData::isExecutionContexts() const {
    return mExecutionContexts;
}

bool _HttpHeaderClearSiteData::isStorage() const {
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
    StringBuffer type = StringBuffer::New();
    if(mCache) {
        type->append("\"",Cache,"\",");
    }

    if(mCookies) {
        type->append("\"",Cookies,"\",");
    }

    if(mExecutionContexts) {
        type->append("\"",ExecutionContexts,"\",");
    }

    if(mStorage) {
        type->append("\"",Storage,"\",");
    }

    return type->toString(0,type->size() - 1);
}
}
