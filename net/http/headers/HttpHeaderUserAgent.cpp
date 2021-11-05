#include "HttpHeaderUserAgent.hpp"

namespace obotcha {

_HttpUserAgentDetail::_HttpUserAgentDetail(String product,String version,String info) {
    this->product = product;
    this->version = version;
    this->info = info;
}

_HttpUserAgentDetail::_HttpUserAgentDetail() {

}

_HttpHeaderUserAgent::_HttpHeaderUserAgent() {
    agents = createArrayList<HttpUserAgentDetail>();
}

_HttpHeaderUserAgent::_HttpHeaderUserAgent(String v):_HttpHeaderUserAgent() {
    import(v);
}

void _HttpHeaderUserAgent::import(String value) {
    const char *v = value->toChars();
    int size = value->size();
    int status = ParseProduct;
    int start = 0;

    HttpUserAgentDetail detail = nullptr;
    bool hasInfo = false;

    for(int i = 0;i < size;i++) {
        switch(status) {
            case ParseProduct:
            if(v[i] == ' ' && i == start) {
                start++;
                continue;
            } else if(v[i] == '/') {
                detail = createHttpUserAgentDetail();
                detail->product = createString(v,start,i-start);
                start = i + 1;
                status = ParseVersion;
            }
            break;

            case ParseVersion:
            if(v[i] == ' ') {
                detail->version = createString(v,start,i-start);
                start = i + 1;
                status = ParseInfo;
            } else if(i == size - 1) {
                detail->version = createString(v,start,i-start+1);
                agents->add(detail);
            }

            break;

            case ParseInfo:
                if(v[i] == ' ') {
                    start++;
                    continue;
                } else if(v[i] == '(') {
                    start++;
                    hasInfo = true;
                    for(int next = i;next < size;next++) {
                        if(v[next] == ')') {
                            detail->info = createString(v,start,next - start);
                            start = next+1;
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
    //agent = v->trim();
}

ArrayList<HttpUserAgentDetail> _HttpHeaderUserAgent::get() {
    return agents;
}

String _HttpHeaderUserAgent::toString() {
    String useragent = "";
    if(agents->size() == 0){
        return nullptr;
    }
    
    auto iterator = agents->getIterator();
    while(iterator->hasValue()) {
        auto v = iterator->getValue();
        useragent = useragent->append(v->product,"/",v->version," ");
        if(v->info != nullptr) {
            useragent = useragent->append("(",v->info,") ");
        }
        iterator->next();
    }

    return useragent->subString(0,useragent->size() - 1);
}

}
