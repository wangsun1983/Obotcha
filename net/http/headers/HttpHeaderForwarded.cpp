#include "HttpHeaderForwarded.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"
#include "StringBuffer.hpp"

namespace obotcha {

_HttpHeaderForwarded::_HttpHeaderForwarded(String s):_HttpHeaderForwarded() {
    load(s);
}

void _HttpHeaderForwarded::load(String s) {
    st(HttpHeaderContentParser)::load(s,[this](String directive,String parameter) {
        if(directive->equalsIgnoreCase("for")) {
            forIdentities->add(parameter);
        } else if(directive->equalsIgnoreCase("by")) {
            byIdentity = parameter;
        } else if(directive->equalsIgnoreCase("host")) {
            host = parameter;
        } else if(directive->equalsIgnoreCase("proto")) {
            proto = parameter;
        }
    });
}

String _HttpHeaderForwarded::toString() {
    StringBuffer forwarded = createStringBuffer();
    auto iterator = forIdentities->getIterator();
    //forward
    while(iterator->hasValue()) {
        if(String v = iterator->getValue();
            v->counts(":") > 1 || v->counts(".") == 0) {
            forwarded->append("for=\"",v,"\",");
        } else {
            forwarded->append("for=",v,",");
        }
        iterator->next();
    }

    forwarded->crop(0,forwarded->size() - 1);
    forwarded->append("; ");
    //proto
    if(proto != nullptr) {
        forwarded->append("proto=",proto,"; ");
    }

    //by
    if(byIdentity != nullptr) {
        forwarded->append("by=",byIdentity,"; ");
    }

    if(host != nullptr) {
        forwarded->append("host=",host,"; ");
    }


    return forwarded->toString(0,forwarded->size() - 2);
}

}
