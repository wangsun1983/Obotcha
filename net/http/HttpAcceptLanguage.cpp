#include "HttpAcceptLanguage.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"

namespace obotcha {

_HttpAcceptLanguageItem::_HttpAcceptLanguageItem() {
    weight = 1.0;
}

_HttpAcceptLanguage::_HttpAcceptLanguage() {
    languages = createArrayList<HttpAcceptLanguageItem>();
}

_HttpAcceptLanguage::_HttpAcceptLanguage(String s) {
    import(s);
}

void _HttpAcceptLanguage::import(String s) {
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
        if(parameter == nullptr) {
            HttpAcceptLanguageItem item = createHttpAcceptLanguageItem();
            item->lang = directive;
            languages->add(item);
        } else {
            if(directive->equals("q")) {
                languages->get(languages->size() - 1)->weight = parameter->toBasicFloat();
            }
        }
    });
}

ArrayList<HttpAcceptLanguageItem> _HttpAcceptLanguage::getLanguages() {
    return languages;
}

String _HttpAcceptLanguage::toString() {
    String encoding = "";
    auto iterator = languages->getIterator();
    while(iterator->hasValue()) {
        HttpAcceptLanguageItem item = iterator->getValue();
        if(st(Math)::compareFloat(item->weight,1.0) == st(Math)::AlmostEqual) {
            encoding = encoding->append(item->lang,",");
        } else {
            encoding = encoding->append(item->lang,";q=",createString(item->weight,2),",");
        }
        iterator->next();
    }

    return encoding->subString(0,encoding->size() - 1);
}

}
