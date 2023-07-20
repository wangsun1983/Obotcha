#include "HttpHeaderContentLanguage.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"
#include "StringBuffer.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

_HttpHeaderContentLanguage::_HttpHeaderContentLanguage() {
    languages = createArrayList<String>();
}

_HttpHeaderContentLanguage::_HttpHeaderContentLanguage(String s) {
    load(s);
}

void _HttpHeaderContentLanguage::load(String s) {
    languages->clear();
    st(HttpHeaderContentParser)::load(s,[this](String directive,String parameter) {
        languages->add(directive);
    });
}

ArrayList<String> _HttpHeaderContentLanguage::get() {
    return languages;
}

void _HttpHeaderContentLanguage::add(String v) {
    languages->add(v->trim());
}


String _HttpHeaderContentLanguage::toString() {
    StringBuffer encoding = createStringBuffer();
    ForEveryOne(item,languages) {
        encoding->append(item,", ");
    }
    return encoding->toString(0,encoding->size() - 2);
}

}
