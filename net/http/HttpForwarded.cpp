#include "HttpForwarded.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"

namespace obotcha {

_HttpForwarded::_HttpForwarded() {
    forIdentities = createArrayList<String>();
}

_HttpForwarded::_HttpForwarded(String s):_HttpForwarded() {
    import(s);
}

void _HttpForwarded::import(String s) {
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
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

String _HttpForwarded::toString() {
    String forwarded = "";
    auto iterator = forIdentities->getIterator();
    //forward
    while(iterator->hasValue()) {
        String v = iterator->getValue();
        if(v->counts(":") > 1 || v->counts(".") == 0) {
            forwarded = forwarded->append("for=\"",v,"\",");
        } else {
            forwarded = forwarded->append("for=",v,",");
        }
        iterator->next();
    }

    forwarded = forwarded->subString(0,forwarded->size() - 1)->append("; ");
    //proto
    if(proto != nullptr) {
        forwarded = forwarded->append("proto=",proto,"; ");
    }

    //by
    if(byIdentity != nullptr) {
        forwarded = forwarded->append("by=",byIdentity,"; ");
    }

    if(host != nullptr) {
        forwarded = forwarded->append("host=",host,"; ");
    }


    return forwarded->subString(0,forwarded->size() - 2);
}

}
