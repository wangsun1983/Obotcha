#include "HttpHeaderXFrameOptions.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"

namespace obotcha {

_HttpHeaderXFrameOptions::_HttpHeaderXFrameOptions(String s) {
    load(s->trim());
}

void _HttpHeaderXFrameOptions::load(String s) {
    st(HttpHeaderContentParser)::load(s,[this](String directive,String parameter) {
        int spaceIndex = directive->indexOf(" ");
        int allowFrom = directive->indexOfIgnoreCase("allow-from");
        if(allowFrom == -1) {
            option = directive;
        } else {
            option = createString("allow-from");
            spaceIndex++;
            uri = directive->subString(spaceIndex,directive->size() - spaceIndex);
        }
    });
}

String _HttpHeaderXFrameOptions::toString() {
    String frameoption = option;
    if(uri != nullptr) {
        frameoption = frameoption->append(" ",uri);
    }

    return frameoption;
}

}
