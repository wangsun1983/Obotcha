#include "HttpHeaderAcceptEncoding.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Float.hpp"
#include "StringBuffer.hpp"
#include "HashMap.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {
_HttpHeaderAcceptEncodingItem::_HttpHeaderAcceptEncodingItem(String s,float w):type(s),weight(w) {
}

_HttpHeaderAcceptEncoding::_HttpHeaderAcceptEncoding(String s) {
    load(s);
}

void _HttpHeaderAcceptEncoding::load(String s) {
    size_t index = 0;
    st(HttpHeaderContentParser)::load(s,[&index,this](String directive,String parameter) {
        if(parameter == nullptr) {
            HttpHeaderAcceptEncodingItem item = HttpHeaderAcceptEncodingItem::New(directive);
            encodings->add(item);
        } else {
            if(directive->sameAs("q")) {
                for(int i = index;i<encodings->size();i++) {
                    encodings->get(i)->weight = parameter->toBasicFloat();
                }
            }
            index = encodings->size();
        }
    });
}

ArrayList<HttpHeaderAcceptEncodingItem> _HttpHeaderAcceptEncoding::get() {
    return encodings;
}

void _HttpHeaderAcceptEncoding::add(String s,float w) {
    encodings->add(HttpHeaderAcceptEncodingItem::New(s,w));
}

String _HttpHeaderAcceptEncoding::toString() {
    if(encodings->size() == 0) {
        return nullptr;
    }

    HashMap<float,ArrayList<String>> map = HashMap<float,ArrayList<String>>::New();
    ForEveryOne(item,encodings) {
        ArrayList<String> l = map->get(item->weight);
        if(l == nullptr) {
            l = ArrayList<String>::New();
            map->put(item->weight,l);
        }
        l->add(item->type);
    }

    String langStrs = String::New("");
    auto keyList = map->keySet();
    auto entryList = map->entrySet();
    size_t index = keyList->size() - 1;
    //for(;index != 0;index--) {
    while(true) {
        ArrayList<String> langs = entryList->get(index);
        ForEveryOne(lang,langs) {
            langStrs = langStrs->append(lang,String::New(","));
        }

        langStrs = langStrs->subString(0,langStrs->size() - 1);
        if(keyList->size() != 1 || st(Float)::Compare(1.0,keyList->get(index)) != 0) {
            langStrs = langStrs->append(String::New(";q="),
                                        String::New(keyList->get(index),1),",");
        } else {
            langStrs = langStrs->append(String::New(","));
        }

        if(index == 0){
            break;
        }

        index--;
    }

    return langStrs->subString(0,langStrs->size() - 1);
}

}
