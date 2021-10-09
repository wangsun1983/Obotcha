#include "HttpAcceptPatch.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"

namespace obotcha {

_HttpAcceptPatchItem::_HttpAcceptPatchItem() {
    type = nullptr;
    charset = nullptr;
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
            HttpAcceptPatchItem item = createHttpAcceptPatchItem();
            item->type = directive;
            patches->add(item);
        } else {
            if(directive->equals("q")) {
                patches->get(patches->size() - 1)->charset = parameter;
            }
        }
    });
}

ArrayList<HttpAcceptPatchItem> _HttpAcceptPatch::getAcceptPatches() {
    return patches;
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
