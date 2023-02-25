#include "HttpHeaderAcceptPatch.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"
#include "StringBuffer.hpp"

namespace obotcha {

_HttpHeaderAcceptPatchItem::_HttpHeaderAcceptPatchItem(String t,String c) {
    type = t;
    charset = c;
}

_HttpHeaderAcceptPatch::_HttpHeaderAcceptPatch() {
    patches = createArrayList<HttpHeaderAcceptPatchItem>();
}

_HttpHeaderAcceptPatch::_HttpHeaderAcceptPatch(String s) {
    import(s);
}

void _HttpHeaderAcceptPatch::import(String s) {
    patches->clear();

    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
        if(parameter == nullptr) {
            HttpHeaderAcceptPatchItem item = createHttpHeaderAcceptPatchItem(directive,nullptr);
            patches->add(item);
        } else {
            if(directive->equals("charset")) {
                patches->get(patches->size() - 1)->charset = parameter;
            }
        }
    });
}

ArrayList<HttpHeaderAcceptPatchItem> _HttpHeaderAcceptPatch::get() {
    return patches;
}

void _HttpHeaderAcceptPatch::add(String type,String charset) {
    patches->add(createHttpHeaderAcceptPatchItem(type,charset));
}

String _HttpHeaderAcceptPatch::toString() {
    StringBuffer patch = createStringBuffer();
    auto iterator = patches->getIterator();
    while(iterator->hasValue()) {
        HttpHeaderAcceptPatchItem item = iterator->getValue();
        if(item->charset == nullptr) {
            patch->append(item->type,",");
        } else {
            patch->append(item->type,";charset=",item->charset,",");
        }
        iterator->next();
    }

    return patch->toString(0,patch->size() - 1);
}

}
