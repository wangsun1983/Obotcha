#include "HttpHeaderAuthorization.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"
#include "StringBuffer.hpp"
#include "InfiniteLoop.hpp"

namespace obotcha {

_HttpHeaderAuthorization::_HttpHeaderAuthorization() {
    type = nullptr;
    credentials = nullptr; //used for basic
    username = nullptr;
    realm = nullptr;
    uri = nullptr;
    algorithm = nullptr;
    nonce = nullptr;
    nc = nullptr;
    cnonce = nullptr;
    qop = nullptr;
    response = nullptr;
    opaque = nullptr;
}

_HttpHeaderAuthorization::_HttpHeaderAuthorization(String s) {
    load(s);
}

void _HttpHeaderAuthorization::load(String s) {
    st(HttpHeaderContentParser)::load(s,[this](String directive,String parameter) {
        InfiniteLoop {
            if(type == nullptr) {
                //first 
                int pos = st(HttpHeaderContentParser)::skipUntil(directive, 0,createString(" "));
                type = directive->subString(0,pos)->trimAll();
                String subParam = directive->subString(pos,directive->size() - pos)->trimAll();
                if(type->equalsIgnoreCase("Basic")) {
                    credentials = subParam;
                    break;
                }

                directive = subParam;
                continue;
            } else {
                if(directive->equalsIgnoreCase("username")) {
                    username = parameter;
                } else if(directive->equalsIgnoreCase("realm")) {
                    realm = parameter;
                } else if(directive->equalsIgnoreCase("uri")) {
                    uri = parameter;
                } else if(directive->equalsIgnoreCase("algorithm")) {
                    algorithm = parameter;
                } else if(directive->equalsIgnoreCase("nonce")) {
                    nonce = parameter;
                } else if(directive->equalsIgnoreCase("nc")) {
                    nc = parameter;
                } else if(directive->equalsIgnoreCase("cnonce")) {
                    cnonce = parameter;
                } else if(directive->equalsIgnoreCase("qop")) {
                    qop = parameter;
                } else if(directive->equalsIgnoreCase("response")) {
                    response = parameter;
                } else if(directive->equalsIgnoreCase("opaque")) {
                    opaque = parameter;
                }
            }
            break;
        }
    });
}

String _HttpHeaderAuthorization::toString() {
    StringBuffer authorization = createStringBuffer();
    
    if(type != nullptr) {
        authorization->append(type," ");
        if(credentials != nullptr) {
            authorization->append(credentials,",");
        }
    }
    
    if(username != nullptr) {
        authorization->append("username=\"",username,"\",");
    }

    if(realm != nullptr) {
        authorization->append("realm=\"",realm,"\",");
    }

    if(nonce != nullptr) {
        authorization->append("nonce=\"",nonce,"\",");
    }

    if(uri != nullptr) {
        authorization->append("uri=\"",uri,"\",");
    }

    if(qop != nullptr) {
        authorization->append("qop=",qop,",");
    }

    if(nc != nullptr) {
        authorization->append("nc=",nc,",");
    }

    if(cnonce != nullptr) {
        authorization->append("cnonce=\"",cnonce,"\",");
    }

    if(response != nullptr) {
        authorization->append("response=\"",response,"\",");
    }    

    if(opaque != nullptr) {
        authorization->append("opaque=\"",opaque,"\",");
    }

    if(algorithm != nullptr) {
        authorization->append("algorithm=",algorithm,",");
    }

    return authorization->toString(0,authorization->size() - 1);
}

}
