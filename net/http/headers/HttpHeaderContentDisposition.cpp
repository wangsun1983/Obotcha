#include "HttpHeaderContentDisposition.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"
#include "StringBuffer.hpp"

namespace obotcha {

_HttpHeaderContentDisposition::_HttpHeaderContentDisposition() {
    
}

_HttpHeaderContentDisposition::_HttpHeaderContentDisposition(String s) {
    import(s);
}

void _HttpHeaderContentDisposition::import(String s) {
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

String _HttpHeaderContentDisposition::toString() {
    if(name == nullptr && filename == nullptr) {
        return type;
    }
    StringBuffer disposition = createStringBuffer();
    
    if(type != nullptr) {
        disposition->append(type);    
    }
    
    if(name != nullptr) {
        disposition->append("; name=\"",name,"\"");
    }

    if(filename != nullptr) {
        disposition->append("; filename=\"",filename,"\"");
    }

    return disposition->toString(0,disposition->size());
}

}
