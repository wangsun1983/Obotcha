#include "HttpHeaderContentLanguage.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"

namespace obotcha {


_HttpHeaderContentLanguage::_HttpHeaderContentLanguage() {
    languages = createArrayList<String>();
}

_HttpHeaderContentLanguage::_HttpHeaderContentLanguage(String s) {
    import(s);
}

void _HttpHeaderContentLanguage::import(String s) {
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
    String encoding = "";
    auto iterator = languages->getIterator();
    while(iterator->hasValue()) {
        encoding = encoding->append(iterator->getValue(),", ");
        iterator->next();
    }

    return encoding->subString(0,encoding->size() - 2);
}

}
