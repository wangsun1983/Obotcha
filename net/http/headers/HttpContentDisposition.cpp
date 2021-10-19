#include "HttpContentDisposition.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"

namespace obotcha {

_HttpContentDisposition::_HttpContentDisposition() {
    
}

_HttpContentDisposition::_HttpContentDisposition(String s) {
    import(s);
}

void _HttpContentDisposition::import(String s) {
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
        if(parameter == nullptr) {
            type = directive;
        } else {
            if(directive->equalsIgnoreCase("name")) {
                name = parameter;
            } else if(directive->equalsIgnoreCase("filename")) {
                filename = parameter;
            }
        }
    });
}

String _HttpContentDisposition::toString() {
    String disposition = type;
    if(name == nullptr && filename == nullptr) {
        return type;
    }

    if(name != nullptr) {
        disposition = disposition->append("; name=\"",name,"\"");
    }

    if(filename != nullptr) {
        disposition = disposition->append("; filename=\"",filename,"\"");
    }

    
    return disposition->subString(0,disposition->size());
}

}
