#include "HttpXFrameOptions.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"

namespace obotcha {

_HttpXFrameOptions::_HttpXFrameOptions() {
    
}

_HttpXFrameOptions::_HttpXFrameOptions(String s) {
    import(s);
}

void _HttpXFrameOptions::import(String s) {
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
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

String _HttpXFrameOptions::toString() {
    String frameoption = option;
    if(uri != nullptr) {
        frameoption = frameoption->append(" ",uri);
    }

    return frameoption;
}

}
