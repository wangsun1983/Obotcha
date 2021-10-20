#include "HttpAcceptPatch.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"

namespace obotcha {

_HttpAcceptPatchItem::_HttpAcceptPatchItem(String t,String c) {
    type = t;
    charset = c;
}

_HttpAcceptPatch::_HttpAcceptPatch() {
    patches = createArrayList<HttpAcceptPatchItem>();
}

_HttpAcceptPatch::_HttpAcceptPatch(String s) {
    import(s);
}

void _HttpAcceptPatch::import(String s) {
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
        if(parameter == nullptr) {
            HttpAcceptPatchItem item = createHttpAcceptPatchItem(directive,nullptr);
            patches->add(item);
        } else {
            if(directive->equals("charset")) {
                patches->get(patches->size() - 1)->charset = parameter;
            }
        }
    });
}

ArrayList<HttpAcceptPatchItem> _HttpAcceptPatch::get() {
    return patches;
}

void _HttpAcceptPatch::add(String type,String charset) {
    patches->add(createHttpAcceptPatchItem(type,charset));
}

String _HttpAcceptPatch::toString() {
    String patch = "";
    auto iterator = patches->getIterator();
    while(iterator->hasValue()) {
        HttpAcceptPatchItem item = iterator->getValue();
        if(item->charset == nullptr) {
            patch = patch->append(item->type,",");
        } else {
            patch = patch->append(item->type,";charset=",item->charset,",");
        }
        iterator->next();
    }

    return patch->subString(0,patch->size() - 1);
}

}
