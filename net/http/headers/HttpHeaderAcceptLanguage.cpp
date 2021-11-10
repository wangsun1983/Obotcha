#include "HttpHeaderAcceptLanguage.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"

namespace obotcha {

_HttpHeaderAcceptLanguageItem::_HttpHeaderAcceptLanguageItem(String s,float w) {
    weight = w;
    lang = s;
}

_HttpHeaderAcceptLanguage::_HttpHeaderAcceptLanguage() {
    languages = createArrayList<HttpHeaderAcceptLanguageItem>();
}

_HttpHeaderAcceptLanguage::_HttpHeaderAcceptLanguage(String s) {
    import(s);
}

void _HttpHeaderAcceptLanguage::import(String s) {
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
        if(parameter == nullptr) {
            HttpHeaderAcceptLanguageItem item = createHttpHeaderAcceptLanguageItem(directive);
            languages->add(item);
        } else {
            if(directive->equals("q")) {
                languages->get(languages->size() - 1)->weight = parameter->toBasicFloat();
            }
        }
    });
}

ArrayList<HttpHeaderAcceptLanguageItem> _HttpHeaderAcceptLanguage::get() {
    return languages;
}

void _HttpHeaderAcceptLanguage::add(String s,float w) {
    languages->add(createHttpHeaderAcceptLanguageItem(s,w));
}

String _HttpHeaderAcceptLanguage::toString() {
    String encoding = "";
    auto iterator = languages->getIterator();
    while(iterator->hasValue()) {
        HttpHeaderAcceptLanguageItem item = iterator->getValue();
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
