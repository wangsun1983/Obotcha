#include "HttpHeaderLink.hpp"
#include "HttpHeaderContentParser.hpp"
#include "StringBuffer.hpp"

namespace obotcha {

_HttpHeaderLink::_HttpHeaderLink() {
}

_HttpHeaderLink::_HttpHeaderLink(String v):_HttpHeaderLink() {
    import(v);
}

void _HttpHeaderLink::import(String s) {
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
        if(parameter == nullptr) {
            url = directive->trimAll()->replaceAll("<","")->replaceAll(">","");
        } else {
            if(directive->equalsIgnoreCase("rel")) {
                rel = parameter;
            } else if(directive->equalsIgnoreCase("title")) {
                title = parameter;
            }
        }
    });
}

String _HttpHeaderLink::toString() {
    StringBuffer link = createStringBuffer();

    if(url != nullptr) {
        link->append("<",url,">");
    }

    if(rel != nullptr) {
        link->append("; rel= \"",rel,"\"");
    }

    if(title != nullptr) {
        link->append("; title= \"",title,"\"");
    }

    return link->toString();
}

} // namespace obotcha