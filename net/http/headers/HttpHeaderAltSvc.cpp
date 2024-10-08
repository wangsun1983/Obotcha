#include "HttpHeaderAltSvc.hpp"
#include "HttpHeaderContentParser.hpp"
#include "HttpUrl.hpp"
#include "StringBuffer.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

_HttpHeaderAltSvcServiceItem::_HttpHeaderAltSvcServiceItem(String s,HttpUrl uri):serviceName(s),url(uri) {
}

_HttpHeaderAltSvc::_HttpHeaderAltSvc(String s) {
    this->load(s);
}

void _HttpHeaderAltSvc::load(String s) {
    altSvcs->clear();
    st(HttpHeaderContentParser)::load(s,[this](String directive,String parameter) {
        if(directive->equalsIgnoreCase("ma")) {
            maxAge = parameter->toBasicInt();
        } else if(directive->equalsIgnoreCase("persist")) {
            persist = parameter->toBasicInt();
        } else {
            HttpUrl url = HttpUrl::New(parameter);
            altSvcs->add(HttpHeaderAltSvcServiceItem::New(directive,url));
        }
    });
}

void _HttpHeaderAltSvc::addService(String service,HttpUrl url) {
    altSvcs->add(HttpHeaderAltSvcServiceItem::New(service,url));
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

int _HttpHeaderAltSvc::getMaxAge() const {
    return maxAge;
}

int _HttpHeaderAltSvc::getPersist() const {
    return persist;
}

String _HttpHeaderAltSvc::toString() {
    StringBuffer svc = StringBuffer::New();
    ForEveryOne(item,altSvcs) {
        svc->append(item->serviceName,"=\"",item->url->toString(),"\", ");
    }

    if(svc->size() != 0) {
        svc->crop(0,svc->size() - 2);
        svc->append("; ");
    }

    if(maxAge != -1) {
        svc->append("ma=",String::New(maxAge),"; ");
    }

    if(persist != -1) {
        svc->append("persist=",String::New(persist),"; ");
    }

    if(svc->size() != 0) {
        return svc->toString(0,svc->size() - 2);
    }

    return nullptr;
}

}