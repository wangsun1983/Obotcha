#include "HttpHeaderAltSvc.hpp"
#include "HttpHeaderContentParser.hpp"
#include "HttpUrl.hpp"
#include "StringBuffer.hpp"

namespace obotcha {

_HttpHeaderAltSvcServiceItem::_HttpHeaderAltSvcServiceItem(String s,HttpUrl url) {
    this->serviceName = s;
    this->url = url;
}

_HttpHeaderAltSvc::_HttpHeaderAltSvc() {
    this->persist =-1;
    this->maxAge = -1;
    altSvcs = createArrayList<HttpHeaderAltSvcServiceItem>();
}

_HttpHeaderAltSvc::_HttpHeaderAltSvc(String s):_HttpHeaderAltSvc() {
    this->import(s);
}

void _HttpHeaderAltSvc::import(String s) {
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
        if(directive->equalsIgnoreCase("ma")) {
            maxAge = parameter->toBasicInt();
        } else if(directive->equalsIgnoreCase("persist")) {
            persist = parameter->toBasicInt();
        } else {
            HttpUrl url = createHttpUrl(parameter);
            altSvcs->add(createHttpHeaderAltSvcServiceItem(directive,url));
        }
    });
}

void _HttpHeaderAltSvc::addService(String service,HttpUrl url) {
    altSvcs->add(createHttpHeaderAltSvcServiceItem(service,url));
}

void _HttpHeaderAltSvc::setMaxAge(int s) {
    maxAge = s;
}

void _HttpHeaderAltSvc::setPersist(int s) {
    persist = s;
}

ArrayList<HttpHeaderAltSvcServiceItem> _HttpHeaderAltSvc::getServices() {
    return altSvcs;
}

int _HttpHeaderAltSvc::getMaxAge() {
    return maxAge;
}

int _HttpHeaderAltSvc::getPersist() {
    return persist;
}

String _HttpHeaderAltSvc::toString() {
    StringBuffer svc = createStringBuffer();
    
    auto iterator = altSvcs->getIterator();
    while(iterator->hasValue()) {
        HttpHeaderAltSvcServiceItem item = iterator->getValue();
        svc->append(item->serviceName,"=\"",item->url->toString(),"\", ");
        iterator->next();
    }

    if(svc->size() != 0) {
        svc->subString(0,svc->size() - 2)->append("; ");
    }

    if(maxAge != -1) {
        svc->append("ma=",createString(maxAge),"; ");
    }

    if(persist != -1) {
        svc->append("persist=",createString(persist),"; ");
    }

    if(svc->size() != 0) {
        return svc->toString(0,svc->size() - 2);
    }

    return nullptr;
}

}