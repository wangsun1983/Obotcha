#include "HttpHeaderUserAgent.hpp"
#include "StringBuffer.hpp"

namespace obotcha {

_HttpUserAgentDetail::_HttpUserAgentDetail(String product,String version,String info):
                mProduct(product),mVersion(version),mInfo(info) {
}

_HttpHeaderUserAgent::_HttpHeaderUserAgent(String v) {
    load(v);
}

void _HttpHeaderUserAgent::load(String value) {
    const char *v = value->toChars();
    int size = value->size();
    int status = ParseProduct;
    int start = 0;

    agents->clear();
    HttpUserAgentDetail detail = nullptr;
    //bool hasInfo = false;

    for(int i = 0;i < size;i++) {
        switch(status) {
            case ParseProduct:
            if(v[i] == ' ' && i == start) {
                start++;
                continue;
            } else if(v[i] == '/') {
                detail = createHttpUserAgentDetail();
                detail->mProduct = createString(v,start,i-start);
                start = i + 1;
                status = ParseVersion;
            }
            break;

            case ParseVersion:
            if(v[i] == ' ') {
                detail->mVersion = createString(v,start,i-start);
                start = i + 1;
                status = ParseInfo;
            } else if(i == size - 1) {
                detail->mVersion = createString(v,start,i-start+1);
                agents->add(detail);
            }

            break;

            case ParseInfo:
                if(v[i] == ' ') {
                    start++;
                    continue;
                } else if(v[i] == '(') {
                    start++;
                    for(;i < size;i++) {
                        if(v[i] == ')') {
                            detail->mInfo = createString(v,start,i - start);
                            start = i+1;
                            break;
                        }
                    }
                } else {
                    status = ParseProduct;
                    agents->add(detail);
                }
            break;
        }
    }
    
}

void _HttpHeaderUserAgent::add(String product,String version,String info) {
    HttpUserAgentDetail detail = createHttpUserAgentDetail(product,version,info);
    agents->add(detail);
}

ArrayList<HttpUserAgentDetail> _HttpHeaderUserAgent::get() {
    return agents;
}

String _HttpHeaderUserAgent::toString() {
    StringBuffer useragent = createStringBuffer();
    if(agents->size() == 0){
        return nullptr;
    }
    
    auto iterator = agents->getIterator();
    while(iterator->hasValue()) {
        auto v = iterator->getValue();
        useragent->append(v->mProduct,"/",v->mVersion," ");
        if(v->mInfo != nullptr) {
            useragent->append("(",v->mInfo,") ");
        }
        iterator->next();
    }

    return useragent->toString(0,useragent->size() - 1);
}

}
