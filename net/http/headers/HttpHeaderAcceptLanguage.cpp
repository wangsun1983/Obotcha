#include "HttpHeaderAcceptLanguage.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Float.hpp"
#include "StringBuffer.hpp"
#include "HashMap.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

_HttpHeaderAcceptLanguageItem::_HttpHeaderAcceptLanguageItem(String s,float w):lang(s),weight(w) {
}

_HttpHeaderAcceptLanguage::_HttpHeaderAcceptLanguage(String s) {
    load(s);
}

void _HttpHeaderAcceptLanguage::load(String s) {
    size_t index = 0;
    languages->clear();
    
    st(HttpHeaderContentParser)::load(s,[&index,this](String directive,String parameter) {
        if(parameter == nullptr) {
            HttpHeaderAcceptLanguageItem item = createHttpHeaderAcceptLanguageItem(directive);
            languages->add(item);
        } else {
            if(directive->sameAs("q")) {
                for(auto i = index;i<languages->size();i++) {
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
    auto keyList = map->keySet();
    //we should sort
    for(int i = 0; i < keyList->size();i++) {
        float v1 = keyList->get(i);
        for(int j = i + 1;j < keyList->size();j++) {
            float v2 = keyList->get(j);
            if(v2 > v1) {
                keyList->set(j,v1);
                keyList->set(i,v2);
                v1 = v2;
            }
        }
    }

    for(int index = 0;index < keyList->size();index++) {
        ArrayList<String> langs = map->get(keyList->get(index));
        ForEveryOne(lang,langs) {
            langStrs = langStrs->append(lang,createString(","));
        }

        langStrs = langStrs->subString(0,langStrs->size() - 1);
        if(keyList->size() != 1 || st(Float)::Compare(1.0,keyList->get(index)) != 0) {
            langStrs = langStrs->append(createString(";q="),createString(keyList->get(index),1),",");
        } else {
            langStrs = langStrs->append(createString(","));
        }
    }

    return langStrs->subString(0,langStrs->size() - 1);
}

}
