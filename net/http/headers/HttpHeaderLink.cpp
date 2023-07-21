#include "HttpHeaderLink.hpp"
#include "HttpHeaderContentParser.hpp"
#include "StringBuffer.hpp"

namespace obotcha {

_HttpHeaderLink::_HttpHeaderLink(String v):_HttpHeaderLink() {
    load(v);
}

void _HttpHeaderLink::load(String s) {
    st(HttpHeaderContentParser)::load(s,[this](String directive,String parameter) {
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
        link->append("; rel=\"",rel,"\"");
    }

    if(title != nullptr) {
        link->append("; title= \"",title,"\"");
    }

    return link->toString();
}

} // namespace obotcha