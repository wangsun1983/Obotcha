#include "HttpProxyAuthenticate.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"

namespace obotcha {

_HttpProxyAuthenticate::_HttpProxyAuthenticate() {
}

_HttpProxyAuthenticate::_HttpProxyAuthenticate(String s) {
    import(s);
}

void _HttpProxyAuthenticate::import(String s) {
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
        if(type == nullptr) {
            int pos = directive->indexOf(" ");
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

String _HttpProxyAuthenticate::toString() {
    String prox = type;
    if(realm != nullptr) {
        prox = prox->append(" realm=\"",realm,"\"");
    }
    return prox;
}

}
