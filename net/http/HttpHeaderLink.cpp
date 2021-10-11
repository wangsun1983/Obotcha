#include "HttpHeaderLink.hpp"
#include "HttpHeaderContentParser.hpp"

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
    String link = createString("<")->append(url,">");
    if(rel != nullptr) {
        link = link->append("; rel= \"",rel,"\"");
    }

    if(title != nullptr) {
        link = link->append("; title= \"",title,"\"");
    }

    return link->subString(0,link->size() - 1);
}

} // namespace obotcha