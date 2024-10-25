#include "HttpHeaderAcceptPatch.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"
#include "StringBuffer.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

_HttpHeaderAcceptPatchItem::_HttpHeaderAcceptPatchItem(String t,String c):type(t),charset(c) {
}

_HttpHeaderAcceptPatch::_HttpHeaderAcceptPatch(String s) {
    load(s);
}

void _HttpHeaderAcceptPatch::load(String s) {
    patches->clear();

    st(HttpHeaderContentParser)::load(s,[this](String directive,String parameter) {
        if(parameter == nullptr) {
            HttpHeaderAcceptPatchItem item = HttpHeaderAcceptPatchItem::New(directive,nullptr);
            patches->add(item);
        } else {
            if(directive->sameAs("charset")) {
                patches->get(patches->size() - 1)->charset = parameter;
            }
        }
    });
}

ArrayList<HttpHeaderAcceptPatchItem> _HttpHeaderAcceptPatch::get() {
    return patches;
}

void _HttpHeaderAcceptPatch::add(String type,String charset) {
    patches->add(HttpHeaderAcceptPatchItem::New(type,charset));
}

String _HttpHeaderAcceptPatch::toString() {
    StringBuffer patch = StringBuffer::New();
    ForEveryOne(item,patches) {
        if(item->charset == nullptr) {
            patch->append(item->type,",");
        } else {
            patch->append(item->type,";charset=",item->charset,",");
        }
    }

    return patch->toString(0,patch->size() - 1);
}

}
