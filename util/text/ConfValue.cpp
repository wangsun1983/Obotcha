#include "ConfValue.hpp"



namespace obotcha {

_ConfValue::_ConfValue() {
    mCaches = createHashMap<String,String>();
    ccl_init(&config);
}

_ConfValue::~_ConfValue() {
    ccl_release(&config);
}

String _ConfValue::get(String tag) {
    const char *v = ccl_get(&config,tag->toChars());
    if(v == nullptr) {
        return nullptr;
    }

    return createString(v);
}

void _ConfValue::set(String key,String value) {
    struct ccl_t *data = &config;
    auto pair = (struct ccl_pair_t *)malloc(sizeof(struct ccl_pair_t));

    char * keydata = (char *)malloc(key->size() + 1);
    memcpy(keydata,key->toChars(),key->size());
    keydata[key->size()] = 0;

    char * valuedata = (char *)malloc(value->size() + 1);
    memcpy(valuedata,value->toChars(),value->size());
    valuedata[value->size()] = 0;

    pair->key = keydata;
    pair->value = valuedata;
    bst_probe(data->table, pair);
}

ConfIterator _ConfValue::getIterator() {
    ConfIterator iterator = createConfIterator(this);
    return iterator;
}

_ConfIterator::_ConfIterator(_ConfValue *v) {
    value.set_pointer(v);
    //v>incStrong(0);
    
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
    return (iterator != nullptr);
}

}