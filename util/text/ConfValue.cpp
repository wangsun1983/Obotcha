#include "ConfValue.hpp"
#include "Inspect.hpp"

namespace obotcha {

_ConfValue::_ConfValue() {
    ccl_init(&mConfig);
}

_ConfValue::~_ConfValue() {
    ccl_release(&mConfig);
}

String _ConfValue::get(String tag) const {
    const char *v = ccl_get(&mConfig,tag->toChars());
    Inspect(v == nullptr,nullptr)
    return String::New(v);
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
    return ConfIterator::New(this);
}

//-------- ConfIterator ---------
_ConfIterator::_ConfIterator(_ConfValue *v):_ConfIterator(AutoClone(v)) {
}
   
_ConfIterator::_ConfIterator(ConfValue v):mValue(v) {
    ccl_t * pair = &(v->mConfig);
    ccl_reset(pair);
    mIterator = ccl_iterate(pair);
}

String _ConfIterator::getTag() const {
    return (mIterator == nullptr)?nullptr:String::New(mIterator->key);
}
    
String _ConfIterator::getValue() const {
    return (mIterator == nullptr)?nullptr:String::New(mIterator->value);
}

bool _ConfIterator::hasValue() const {
    return mIterator != nullptr;
}
    
bool _ConfIterator::next() {
    mIterator = ccl_iterate(&(mValue->mConfig));
    return (mIterator != nullptr);
}

}