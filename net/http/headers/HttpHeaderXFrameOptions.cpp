#include "HttpHeaderXFrameOptions.hpp"
#include "HttpHeaderContentParser.hpp"

namespace obotcha {

_HttpHeaderXFrameOptions::_HttpHeaderXFrameOptions(String s) {
    load(s->trim());
}

void _HttpHeaderXFrameOptions::load(String s) {
    st(HttpHeaderContentParser)::load(s,[this](String directive,
                                [[maybe_unused]]String parameter) {
        size_t spaceIndex = directive->indexOf(" ");
        size_t allowFrom = directive->indexOfIgnoreCase("allow-from");
        if(allowFrom == -1) {
            option = directive;
        } else {
            option = String::New("allow-from");
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
