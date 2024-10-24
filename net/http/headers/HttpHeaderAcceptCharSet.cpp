#include "HttpHeaderAcceptCharSet.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Float.hpp"
#include "StringBuffer.hpp"
#include "HashMap.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

_HttpHeaderAcceptCharSetItem::_HttpHeaderAcceptCharSetItem(String s,float w):type(s),weight(w) {
}

//----------- HeaderAcceptCharSet -------------
_HttpHeaderAcceptCharSet::_HttpHeaderAcceptCharSet(String s) {
    load(s);
}

void _HttpHeaderAcceptCharSet::load(String s) {
    size_t index = 0;
    charsets->clear();
    
    st(HttpHeaderContentParser)::load(s,[&index,this](String directive,String parameter) {
        if(parameter == nullptr) {
            HttpHeaderAcceptCharSetItem item = HttpHeaderAcceptCharSetItem::New(directive);
            charsets->add(item);
        } else {
            if(directive->sameAs("q")) {
                for(auto i = index;i<charsets->size();i++) {
                    charsets->get(i)->weight = parameter->toBasicFloat();
                }
            }
            index = charsets->size();
        }
    });
}

ArrayList<HttpHeaderAcceptCharSetItem> _HttpHeaderAcceptCharSet::get() {
    return charsets;
}

void _HttpHeaderAcceptCharSet::add(String s,float w) {
    charsets->add(HttpHeaderAcceptCharSetItem::New(s,w));
}

String _HttpHeaderAcceptCharSet::toString() {
    if(charsets->size() == 0) {
        return nullptr;
    }

    HashMap<float,ArrayList<String>> map = HashMap<float,ArrayList<String>>::New();
    ForEveryOne(item,charsets) {
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
    while(true) {
        ArrayList<String> langs = entryList->get(index);
        ForEveryOne(lang,langs) {
            langStrs = langStrs->append(lang,String::New(","));
        }
        langStrs = langStrs->subString(0,langStrs->size() - 1);
        if(keyList->size() != 1 || st(Float)::Compare(1.0,keyList->get(index)) != 0) {
            langStrs = langStrs->append(String::New(";q="),String::New(keyList->get(index),1),",");
        } else {
            langStrs = langStrs->append(String::New(","));
        }

        if(index == 0) {
            break;
        }

        index--;
    }
    return langStrs->subString(0,langStrs->size() - 1);
}

}
