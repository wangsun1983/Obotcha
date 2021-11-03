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
                printf("product is %s \n",detail->product->toChars());
                start = i + 1;
                status = ParseVersion;
            }
            break;

            case ParseVersion:
            if(v[i] == ' ') {
                detail->version = createString(v,start,i-start);
                start = i + 1;
                status = ParseInfo;
                if(start == size) {
                    agents->add(detail);
                }
                printf("version is %s \n",detail->version->toChars());
            } 
            break;

            case ParseInfo:
                printf("v[start] is %c ,i is %d,start is %d\n",v[start],i,start);
                if(v[i] == ' ') {
                    start++;
                    continue;
                } else if(v[i] == '(') {
                    start++;
                    hasInfo = true;
                    continue;
                } else if(v[i] == ')' && hasInfo) {
                    detail->info = createString(v,start,i-start);
                    continue;
                    printf("info is %s \n",detail->info->toChars());
                }

                
                status = ParseProduct;
                agents->add(detail);
                hasInfo = false;
                
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
    //return agent;
    return nullptr;
}

}
