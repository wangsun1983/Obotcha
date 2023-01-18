#include "HttpHeaderAccept.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"
#include "StringBuffer.hpp"
#include "HashMap.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

_HttpHeaderAcceptItem::_HttpHeaderAcceptItem(String s,float w) {
    weight = w;
    type = s;
}

_HttpHeaderAccept::_HttpHeaderAccept() {
    accepts = createArrayList<HttpHeaderAcceptItem>();
}

_HttpHeaderAccept::_HttpHeaderAccept(String s) {
    import(s);
}

void _HttpHeaderAccept::import(String s) {
    int index = 0;
    st(HttpHeaderContentParser)::import(s,[&index,this](String directive,String parameter) {
        if(parameter == nullptr) {
            HttpHeaderAcceptItem item = createHttpHeaderAcceptItem(directive);
            accepts->add(item);
        } else {
            if(directive->equals("q")) {
                for(int i = index;i<accepts->size();i++) {
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
    accepts->add(createHttpHeaderAcceptItem(s,w));
}

String _HttpHeaderAccept::toString() {
    if(accepts->size() == 0) {
        return nullptr;
    }

    HashMap<float,ArrayList<String>> map = createHashMap<float,ArrayList<String>>();
    ForEveryOne(item,accepts) {
        ArrayList<String> l = map->get(item->weight);
        if(l == nullptr) {
            l = createArrayList<String>();
            map->put(item->weight,l);
        }
        printf("item weight is %f,type is %s \n",item->weight,item->type->toChars());
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
        if(keyList->size() != 1) {
            langStrs = langStrs->append(createString(";q="),createString(keyList->get(index),1),",");
        } else {
            langStrs = langStrs->append(createString(","));
        }
    }

    return langStrs->subString(0,langStrs->size() - 1);
}

}
