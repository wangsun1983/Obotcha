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
    import(s);
}

void _HttpHeaderContentLanguage::import(String s) {
    languages->clear();
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
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
