#include "HttpHeaderAcceptCharSet.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"
#include "StringBuffer.hpp"
#include "HashMap.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

_HttpHeaderAcceptCharSetItem::_HttpHeaderAcceptCharSetItem(String s,float w) {
    weight = w;
    type = s;
}

//----------- HeaderAcceptCharSet -------------
_HttpHeaderAcceptCharSet::_HttpHeaderAcceptCharSet() {
    charsets = createArrayList<HttpHeaderAcceptCharSetItem>();
}

_HttpHeaderAcceptCharSet::_HttpHeaderAcceptCharSet(String s):_HttpHeaderAcceptCharSet() {
    import(s);
}

void _HttpHeaderAcceptCharSet::import(String s) {
    int index = 0;
    charsets->clear();
    
    st(HttpHeaderContentParser)::import(s,[&index,this](String directive,String parameter) {
        if(parameter == nullptr) {
            HttpHeaderAcceptCharSetItem item = createHttpHeaderAcceptCharSetItem(directive);
            charsets->add(item);
        } else {
            if(directive->equals("q")) {
                for(int i = index;i<charsets->size();i++) {
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
    charsets->add(createHttpHeaderAcceptCharSetItem(s,w));
}

String _HttpHeaderAcceptCharSet::toString() {
    if(charsets->size() == 0) {
        return nullptr;
    }

    HashMap<float,ArrayList<String>> map = createHashMap<float,ArrayList<String>>();
    ForEveryOne(item,charsets) {
        ArrayList<String> l = map->get(item->weight);
        if(l == nullptr) {
            l = createArrayList<String>();
            map->put(item->weight,l);
        }
        l->add(item->type);
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
        if(keyList->size() != 1 || st(Math)::compareFloat(1.0,keyList->get(index)) != st(Math)::AlmostEqual) {
            langStrs = langStrs->append(createString(";q="),createString(keyList->get(index),1),",");
        } else {
            langStrs = langStrs->append(createString(","));
        }
    }

    return langStrs->subString(0,langStrs->size() - 1);
}

}
