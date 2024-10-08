#include "HttpHeaderUserAgent.hpp"
#include "StringBuffer.hpp"

namespace obotcha {

_HttpUserAgentDetail::_HttpUserAgentDetail(String product,String version,String info):
                agentProduct(product),agentVersion(version),agentInfo(info) {
}

_HttpHeaderUserAgent::_HttpHeaderUserAgent(String v) {
    load(v);
}

void _HttpHeaderUserAgent::load(String value) {
    const char *v = value->toChars();
    size_t size = value->size();
    Status status = Status::ParseProduct;
    size_t start = 0;

    agents->clear();
    HttpUserAgentDetail detail = nullptr;

    for(int i = 0;i < size;i++) {
        switch(status) {
            case Status::ParseProduct:
            if(v[i] == ' ' && i == start) {
                start++;
                continue;
            } else if(v[i] == '/') {
                detail = HttpUserAgentDetail::New();
                detail->agentProduct = String::New(v,start,i-start);
                start = i + 1;
                status = Status::ParseVersion;
            }
            break;

            case Status::ParseVersion:
            if(v[i] == ' ') {
                detail->agentVersion = String::New(v,start,i-start);
                start = i + 1;
                status = Status::ParseInfo;
            } else if(i == size - 1) {
                detail->agentVersion = String::New(v,start,i-start+1);
                agents->add(detail);
            }

            break;

            case Status::ParseInfo:
                if(v[i] == ' ') {
                    start++;
                    continue;
                } else if(v[i] == '(') {
                    start++;
                    for(;i < size;i++) {
                        if(v[i] == ')') {
                            detail->agentInfo = String::New(v,start,i - start);
                            start = i+1;
                            break;
                        }
                    }
                } else {
                    status = Status::ParseProduct;
                    agents->add(detail);
                }
            break;
        }
    }
    
}

void _HttpHeaderUserAgent::add(String product,String version,String info) {
    HttpUserAgentDetail detail = HttpUserAgentDetail::New(product,version,info);
    agents->add(detail);
}

ArrayList<HttpUserAgentDetail> _HttpHeaderUserAgent::get() {
    return agents;
}

String _HttpHeaderUserAgent::toString() {
    StringBuffer useragent = StringBuffer::New();
    if(agents->size() == 0){
        return nullptr;
    }
    
    auto iterator = agents->getIterator();
    while(iterator->hasValue()) {
        auto v = iterator->getValue();
        useragent->append(v->agentProduct,"/",v->agentVersion," ");
        if(v->agentInfo != nullptr) {
            useragent->append("(",v->agentInfo,") ");
        }
        iterator->next();
    }

    return useragent->toString(0,useragent->size() - 1);
}

}
