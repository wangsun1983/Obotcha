#include "HttpHeaderAccept.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Float.hpp"
#include "HashMap.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

_HttpHeaderAcceptItem::_HttpHeaderAcceptItem(String s,float w):type(s),weight(w) {
}

_HttpHeaderAccept::_HttpHeaderAccept(String s) {
    load(s);
}

void _HttpHeaderAccept::load(String s) {
    size_t index = 0;
    accepts->clear();
    
    st(HttpHeaderContentParser)::load(s,[&index,this](String directive,String parameter) {
        if(parameter == nullptr) {
            HttpHeaderAcceptItem item = HttpHeaderAcceptItem::New(directive);
            accepts->add(item);
        } else {
            if(directive->sameAs("q")) {
                for(auto i = index;i<accepts->size();i++) {
                    accepts->get(i)->weight = parameter->toBasicFloat();
                }
            }
            index = accepts->size();
        }
    });
}

ArrayList<HttpHeaderAcceptItem> _HttpHeaderAccept::get() {
    return accepts;
}

void _HttpHeaderAccept::add(String s,float w) {
    accepts->add(HttpHeaderAcceptItem::New(s,w));
}

String _HttpHeaderAccept::toString() {
    if(accepts->size() == 0) {
        return nullptr;
    }

    HashMap<float,ArrayList<String>> map = HashMap<float,ArrayList<String>>::New();
    ForEveryOne(item,accepts) {
        ArrayList<String> l = map->get(item->weight);
        if(l == nullptr) {
            l = ArrayList<String>::New();
            map->put(item->weight,l);
        }
        l->add(item->type);
    }
    String langStrs = String::New("");
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
            langStrs = langStrs->append(lang,String::New(","));
        }

        langStrs = langStrs->subString(0,langStrs->size() - 1);
        if(keyList->size() != 1) {
            auto qValue = keyList->get(index);
            if(st(Float)::Compare(qValue,1.0) != 0) {
                langStrs = langStrs->append(String::New(";q="),String::New(keyList->get(index),1),",");
                continue;
            }
        }
        
        langStrs = langStrs->append(String::New(","));
    }

    return langStrs->subString(0,langStrs->size() - 1);
}

}
