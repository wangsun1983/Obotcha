#include "ConfValue.hpp"

namespace obotcha {

_ConfValue::_ConfValue() {
    //nothing
}

_ConfValue::~_ConfValue() {
    ccl_release(&config);
}

String _ConfValue::getValue(String tag) {
    const char *v = ccl_get(&config,tag->toChars());
    if(v == nullptr) {
        return nullptr;
    }

    return createString(v);
}

ConfIterator _ConfValue::getIterator() {
    
    ConfIterator iterator = createConfIterator(this);
    return iterator;
}

_ConfIterator::_ConfIterator(_ConfValue *v) {
    value.set_pointer(v);
    //v->incStrong(0);
    
    ccl_t * pair = &(v->config);
    ccl_reset(pair);
    iterator = (ccl_pair_t *)ccl_iterate(pair);
}
   
_ConfIterator::_ConfIterator(ConfValue v) {
    value = v;

    ccl_t * pair = &(v->config);
    ccl_reset(pair);
    iterator = (ccl_pair_t *)ccl_iterate(pair);
}

String _ConfIterator::getTag() {
    if(iterator != nullptr) {
        return createString(iterator->key);
    }

    return nullptr;
}
    
String _ConfIterator::getValue() {
    if(iterator != nullptr) {
        return createString(iterator->value);
    }

    return nullptr;    
}

bool _ConfIterator::hasValue() {
    return iterator != nullptr;
}
    
bool _ConfIterator::next() {
    ccl_t * pair = &(value->config);
    iterator = (ccl_pair_t *)ccl_iterate(pair);
}

}
