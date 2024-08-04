#include "HttpUrlEncodedValue.hpp"
#include "HttpHeaderContentParser.hpp"
#include "StringBuffer.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

_HttpUrlEncodedValue::_HttpUrlEncodedValue() {
    encodedValues = HashMap<String,String>::New();
}

_HttpUrlEncodedValue::_HttpUrlEncodedValue(String v):_HttpUrlEncodedValue() {
    load(v);
}

void _HttpUrlEncodedValue::load(String value) {
    auto eqItem = value->split("&");
    ForEveryOne(item,eqItem) {
        auto items = item->split("=");
        if(items->size() == 2) {
            String key = items->get(0)->trim();
            String value = items->get(1)->trim();
            encodedValues->put(key,value);
        }
    }
}

HashMap<String,String> _HttpUrlEncodedValue::getValues() {
    return encodedValues;
}

void _HttpUrlEncodedValue::set(String k,String v) {
    encodedValues->put(k,v);
}

String _HttpUrlEncodedValue::get(String k) {
    return encodedValues->get(k);
}

String _HttpUrlEncodedValue::toString() {
    StringBuffer v = StringBuffer::New();
    auto iterator = encodedValues->getIterator();
    while (iterator->hasValue()) {
        String key = iterator->getKey();
        String value = iterator->getValue();
        v->append(key,"=",value,"&");
        iterator->next();
    }
    return v->toString(0,v->size()-1);
}

}

