#include "HttpContentLanguage.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"

namespace obotcha {


_HttpContentLanguage::_HttpContentLanguage() {
    languages = createArrayList<String>();
}

_HttpContentLanguage::_HttpContentLanguage(String s) {
    import(s);
}

void _HttpContentLanguage::import(String s) {
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
        languages->add(directive);
    });
}

ArrayList<String> _HttpContentLanguage::get() {
    return languages;
}

void _HttpContentLanguage::add(String v) {
    languages->add(v->trim());
}


String _HttpContentLanguage::toString() {
    String encoding = "";
    auto iterator = languages->getIterator();
    while(iterator->hasValue()) {
        encoding = encoding->append(iterator->getValue(),", ");
        iterator->next();
    }

    return encoding->subString(0,encoding->size() - 2);
}

}
