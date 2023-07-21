#include "ConfValue.hpp"
#include "Inspect.hpp"

namespace obotcha {

_ConfValue::_ConfValue() {
    ccl_init(&mConfig);
}

_ConfValue::~_ConfValue() {
    ccl_release(&mConfig);
}

String _ConfValue::get(String tag) {
    const char *v = ccl_get(&mConfig,tag->toChars());
    Inspect(v == nullptr,nullptr)
    return createString(v);
}

void _ConfValue::set(String key,String value) {
    auto pair = (struct ccl_pair_t *)malloc(sizeof(struct ccl_pair_t));

    char * keydata = (char *)malloc(key->size() + 1);
    memcpy(keydata,key->toChars(),key->size());
    keydata[key->size()] = 0;

    char * valuedata = (char *)malloc(value->size() + 1);
    memcpy(valuedata,value->toChars(),value->size());
    valuedata[value->size()] = 0;

    pair->key = keydata;
    pair->value = valuedata;
    bst_probe(mConfig.table, pair);
}

ConfIterator _ConfValue::getIterator() {
    return createConfIterator(this);
}

//-------- ConfIterator ---------
_ConfIterator::_ConfIterator(_ConfValue *v):_ConfIterator(AutoClone(v)) {
}
   
_ConfIterator::_ConfIterator(ConfValue v) {
    mValue = v;
    ccl_t * pair = &(v->mConfig);
    ccl_reset(pair);
    mIterator = const_cast<ccl_pair_t *>(ccl_iterate(pair));
}

String _ConfIterator::getTag() {
    return (mIterator == nullptr)?nullptr:createString(mIterator->key);
}
    
String _ConfIterator::getValue() {
    return (mIterator == nullptr)?nullptr:createString(mIterator->value);
}

bool _ConfIterator::hasValue() {
    return mIterator != nullptr;
}
    
bool _ConfIterator::next() {
    mIterator = const_cast<ccl_pair_t *>(ccl_iterate(&(mValue->mConfig)));
    return (mIterator != nullptr);
}

}