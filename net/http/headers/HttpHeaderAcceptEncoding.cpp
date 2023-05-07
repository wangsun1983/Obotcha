#include "HttpHeaderAcceptEncoding.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"
#include "StringBuffer.hpp"
#include "HashMap.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {
_HttpHeaderAcceptEncodingItem::_HttpHeaderAcceptEncodingItem(String s,float w) {
    weight = w;
    type = s;
}

_HttpHeaderAcceptEncoding::_HttpHeaderAcceptEncoding() {
    encodings = createArrayList<HttpHeaderAcceptEncodingItem>();
}

_HttpHeaderAcceptEncoding::_HttpHeaderAcceptEncoding(String s) {
    import(s);
}

void _HttpHeaderAcceptEncoding::import(String s) {
    int index = 0;
    st(HttpHeaderContentParser)::import(s,[&index,this](String directive,String parameter) {
        if(parameter == nullptr) {
            HttpHeaderAcceptEncodingItem item = createHttpHeaderAcceptEncodingItem(directive);
            encodings->add(item);
        } else {
            if(directive->equals("q")) {
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
    encodings->add(createHttpHeaderAcceptEncodingItem(s,w));
}

String _HttpHeaderAcceptEncoding::toString() {
    if(encodings->size() == 0) {
        return nullptr;
    }

    HashMap<float,ArrayList<String>> map = createHashMap<float,ArrayList<String>>();
    ForEveryOne(item,encodings) {
        ArrayList<String> l = map->get(item->weight);
        if(l == nullptr) {
            l = createArrayList<String>();
            map->put(item->weight,l);
        }
        l->add(item->type);
    }

    String langStrs = createString("");
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
            langStrs = langStrs->append(createString(";q="),
                                        createString(keyList->get(index),1),",");
        } else {
            langStrs = langStrs->append(createString(","));
        }
    }

    return langStrs->subString(0,langStrs->size() - 1);
}

}
