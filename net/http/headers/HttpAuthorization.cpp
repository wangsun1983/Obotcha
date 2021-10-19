#include "HttpAuthorization.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"

namespace obotcha {

_HttpAuthorization::_HttpAuthorization() {
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

_HttpAuthorization::_HttpAuthorization(String s) {
    import(s);
}

void _HttpAuthorization::import(String s) {
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
        while(1) {
            if(type == nullptr) {
                //first 
                int pos = st(HttpHeaderContentParser)::skipUntil(directive, 0,createString(" "));
                type = directive->subString(0,pos)->trimAll();
                parameter = directive->subString(pos,directive->size() - pos)->trimAll();
                if(type->equalsIgnoreCase("Basic")) {
                    credentials = parameter;
                    break;
                }

                directive = parameter;
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

String _HttpAuthorization::toString() {
    String authorization = type;
    
    if(credentials != nullptr) {
        authorization = authorization->append(" ",credentials,",");
    } else {
        if(username != nullptr) {
            authorization = authorization->append(" username=",username,",");
        }

        if(realm != nullptr) {
            authorization = authorization->append(" realm=\"",realm,"\",");
        }

        if(uri != nullptr) {
            authorization = authorization->append(" uri=\"",uri,"\",");
        }

        if(algorithm != nullptr) {
            authorization = authorization->append(" algorithm=",algorithm,",");
        }

        if(nonce != nullptr) {
            authorization = authorization->append(" nonce=\"",nonce,"\",");
        }

        if(nc != nullptr) {
            authorization = authorization->append(" nc=",nc,",");
        }

        if(cnonce != nullptr) {
            authorization = authorization->append(" cnonce=\"",cnonce,"\",");
        }

        if(qop != nullptr) {
            authorization = authorization->append(" qop=",qop,",");
        }

        if(response != nullptr) {
            authorization = authorization->append(" response=\"",response,"\",");
        }

        if(opaque != nullptr) {
            authorization = authorization->append(" opaque=\"",opaque,"\",");
        }
    }
    return authorization->subString(0,authorization->size() - 1);
}

}
