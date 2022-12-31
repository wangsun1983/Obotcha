#include "HttpHeaderAcceptLanguage.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"
#include "StringBuffer.hpp"
#include "HashMap.hpp"
#include "ForEveryOne.hpp"

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
    int index = 0;
    st(HttpHeaderContentParser)::import(s,[&index,this](String directive,String parameter) {
        if(parameter == nullptr) {
            HttpHeaderAcceptLanguageItem item = createHttpHeaderAcceptLanguageItem(directive);
            languages->add(item);
        } else {
            if(directive->equals("q")) {
                for(int i = index;i<languages->size();i++) {
                    languages->get(i)->weight = parameter->toBasicFloat();
                }
            }
            index = languages->size();
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
    if(languages->size() == 0) {
        return nullptr;
    }
    HashMap<float,ArrayList<String>> map = createHashMap<float,ArrayList<String>>();
    ForEveryOne(item,languages) {
        ArrayList<String> l = map->get(item->weight);
        if(l == nullptr) {
            l = createArrayList<String>();
            map->put(item->weight,l);
        }

        l->add(item->lang);
    }

    String langStrs = createString("");
    //ForEveryOne(pair,map) {
    auto keyList = map->keySet();
    auto entryList = map->entrySet();
    int index = keyList->size() - 1;
    for(;index >= 0;index--) {
        ArrayList<String> langs = entryList->get(index);
        ForEveryOne(lang,langs) {
            langStrs = langStrs->append(lang,createString(","));
        }

        langStrs = langStrs->subString(0,langStrs->size() - 1);
        if(keyList->size() != 1) {
            langStrs = langStrs->append(createString(";q="),createString(keyList->get(index),1),",");
        } else {
            langStrs = langStrs->append(createString(","));
        }
    }

    return langStrs->subString(0,langStrs->size() - 1);
}

}
