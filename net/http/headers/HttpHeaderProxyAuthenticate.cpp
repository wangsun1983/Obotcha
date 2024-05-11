#include "HttpHeaderProxyAuthenticate.hpp"
#include "HttpHeaderContentParser.hpp"
#include "StringBuffer.hpp"

namespace obotcha {

_HttpHeaderProxyAuthenticate::_HttpHeaderProxyAuthenticate(String s) {
    load(s);
}

void _HttpHeaderProxyAuthenticate::load(String s) {
    st(HttpHeaderContentParser)::load(s,[this](String directive,String parameter) {
        if(type == nullptr) {
            size_t pos = directive->indexOf(" ");
            if(pos != -1) {
                type = directive->subString(0,pos);
                pos++;
                directive = directive->subString(pos,directive->size() - pos);
            } else {
                type = directive;
                return;
            }
        }

        if(directive->equalsIgnoreCase("realm")) {
            realm = parameter;
        }
    });
}

String _HttpHeaderProxyAuthenticate::toString() {
    StringBuffer prox = StringBuffer::New();
    if(type != nullptr) {
        prox->append(type);
    }
    
    if(realm != nullptr) {
        prox->append(" realm=\"",realm,"\"");
    }

    return prox->toString();
}

}
