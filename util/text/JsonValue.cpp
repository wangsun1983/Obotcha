#include <iostream>
#include "json/value.h"
#include "JsonValue.hpp"

#include "Log.hpp"

namespace obotcha {

_JsonValue::~_JsonValue() {
    //delete(jvalue);
}

_JsonValue::_JsonValue() {
    //jvalue = new Json::Value();
    mName = nullptr;
}

_JsonValue::_JsonValue(Json::Value v,String name) {
    jvalue = v;
    mName = name;
}

_JsonValue::_JsonValue(sp<_JsonValue> v,String name) {
    jvalue = v->jvalue;
    mName = name;
}

void _JsonValue::put(String tag,String value) {
    jvalue[tag->getStdString()] = value->toChars();
}

void _JsonValue::put(String tag,const char *value) {
    jvalue[tag->toChars()] = value;
}

void _JsonValue::put(String tag,std::string value) {
    jvalue[tag->toChars()] = value;
}

void _JsonValue::put(String tag,Integer value) {
    jvalue[tag->toChars()] = value->toValue();
}

void _JsonValue::put(String tag,int value) {
    jvalue[tag->toChars()] = value;
}

void _JsonValue::put(String tag,Boolean value) {
    jvalue[tag->toChars()] = value->toValue();
}

void _JsonValue::put(String tag,bool value) {
    jvalue[tag->toChars()] = value;
}

void _JsonValue::put(String tag,Double value) {
    if(value == nullptr || tag == nullptr) {
        return;
    }

    jvalue[tag->toChars()] = value->toValue();
}

void _JsonValue::put(String tag,double value) {
    jvalue[tag->toChars()] = value;
}

void _JsonValue::put(String tag,Uint64 value) {
    put(tag,value->toValue());
}

void _JsonValue::put(String tag,uint64_t value) {
    jvalue[tag->toChars()] = (Json::UInt)value;
}

void _JsonValue::put(String tag,Long value) {
    jvalue[tag->toChars()] = (Json::LargestInt)value->toValue();
}

void _JsonValue::put(String tag,long value) {
    jvalue[tag->toChars()] = (Json::LargestInt)value;
}

void _JsonValue::put(String tag,sp<_JsonValue> v) {
    jvalue[tag->toChars()] = v->jvalue;
}

JsonValue _JsonValue::remove(String tag) {
    JsonValue v = createJsonValue();
    jvalue.removeMember(tag->toChars(),&v->jvalue);
    return v;
}

JsonValue _JsonValue::removeAt(int index) {
    JsonValue v = createJsonValue();
    jvalue.removeIndex(index,&v->jvalue);
    return v;
}

String _JsonValue::getName() {
    return mName;
}


String _JsonValue::getString(String tag) {
    return getString(tag->toChars());
}

String _JsonValue::getString(const char * tag) {
    if(jvalue.isMember(tag)) {
        std::string v = jvalue[tag].asString();
        return createString(v);
    }

    return nullptr;
}

String _JsonValue::getString() {
    std::string v = jvalue.asString();
    return createString(v);
}

Integer _JsonValue::getInteger(String tag) {
    return getInteger(tag->toChars());
}

Integer _JsonValue::getInteger(const char* tag) {
    if(jvalue.isMember(tag)) {
        int v = jvalue[tag].asInt();
        return createInteger(v);
    }

    return nullptr;
}

Integer _JsonValue::getInteger() {
    int v = jvalue.asInt();
    return createInteger(v);
}

bool _JsonValue::isEmpty() {
    return jvalue.empty();
}

Uint64  _JsonValue::getUint64(String tag) {
    return getUint64(tag->toChars());
}

Uint64  _JsonValue::getUint64(const char* tag) {
    if(tag!= nullptr && jvalue.isMember(tag)) {
        Json::Value va = jvalue[tag];
        if(!va.isNull()) {
            uint64_t v = (uint64_t)va.asUInt64();
            return createUint64(v);
        }
    }

    return nullptr;
}

Uint64 _JsonValue::getUint64() {
    if(!jvalue.isNull()) {
        uint64_t v = (uint64_t)jvalue.asUInt64();
        return createUint64(v);
    }
    return nullptr;
}

Long _JsonValue::getLong(String tag) {
    return getLong(tag->toChars());
}

Long _JsonValue::getLong(const char* tag) {
    if(tag!= nullptr && jvalue.isMember(tag)) {
        Json::Value va = jvalue[tag];
        if(!va.isNull()) {
            long v = (long)jvalue[tag].asLargestInt();
            return createLong(v);
        }
    }

    return nullptr;
}

Long _JsonValue::getLong() {
    long v = (long)jvalue.asLargestInt();
    return createLong(v);
}

int _JsonValue::size() { 
    return jvalue.size();
}

Boolean _JsonValue::getBoolean(String tag) {
    return getBoolean(tag->toChars());
}

Boolean _JsonValue::getBoolean(const char* tag) {
    if(tag != nullptr && jvalue.isMember(tag)) {
        Json::Value va = jvalue[tag];
        if(!va.isNull()) {
            bool v = va.asBool();
            return createBoolean(v);
        }
    }

    return nullptr;
}

Boolean _JsonValue::getBoolean() {
    bool v = jvalue.asBool();
    return createBoolean(v);
}


Double _JsonValue::getDouble(String tag) {
    return getDouble(tag->toChars());
}

Double _JsonValue::getDouble(const char *tag) {
    if(tag!= nullptr && jvalue.isMember(tag)) {
        Json::Value va = jvalue[tag];
        if(!va.isNull()) {
            double v = jvalue[tag].asDouble();
            return createDouble(v);
        }
    }

    return nullptr; 
}

Double _JsonValue::getDouble() {
    double v = jvalue.asDouble();
    return createDouble(v);
}

sp<_JsonValue> _JsonValue::getValue(String tag) {
    return getValue(tag->toChars());
}

sp<_JsonValue> _JsonValue::getValue(const char * tag) {
    if(tag != nullptr && jvalue.isMember(tag)) {
        Json::Value value = jvalue[tag];
        return createJsonValue(value,S(tag));
    }
    
    return nullptr;
}

bool _JsonValue::contains(String tag) {
    if(tag == nullptr) {
        return false;
    }

    return jvalue.isMember(tag->toChars());
}


bool _JsonValue::isBool() {
    return jvalue.isBool();
}

bool _JsonValue::isInt() {
    return jvalue.isInt();
}

bool _JsonValue::isUint64() {
    return jvalue.isUInt64();
}


bool _JsonValue::isString() {
    return jvalue.isString();
}

bool _JsonValue::isDouble() {
    return jvalue.isDouble();
}

bool _JsonValue::isArray() {
    return jvalue.isArray();
}

bool _JsonValue::isNull() {
    return jvalue.size() == 0;
}

bool _JsonValue::isObject() {
    return jvalue.isObject();
}

void _JsonValue::append(String value) {
    jvalue.append(value->toChars());
}

void _JsonValue::append(const char *value) {
    jvalue.append(value);
}

void _JsonValue::append(std::string value) {
    jvalue.append(value);
}

void _JsonValue::append(Integer value) {
    jvalue.append(value->toValue());
}

void _JsonValue::append(int value) {
    jvalue.append(value);
}

void _JsonValue::append(Long value) {
    jvalue.append((Json::Int64)value->toValue());
}

void _JsonValue::append(long value) {
    jvalue.append((Json::Int64)value);
}

void _JsonValue::append(Uint8 value) {
    jvalue.append((Json::UInt64)value->toValue());
}

void _JsonValue::append(uint8_t value) {
    jvalue.append(value);
}

void _JsonValue::append(Uint16 value) {
    jvalue.append((Json::UInt64)value->toValue());
}

void _JsonValue::append(uint16_t value) {
    jvalue.append(value);
}

void _JsonValue::append(Uint32 value) {
    jvalue.append((Json::UInt64)value->toValue());
}

void _JsonValue::append(uint32_t value) {
    jvalue.append(value);
}

void _JsonValue::append(Uint64 value) {
    jvalue.append((Json::UInt64)value->toValue());
}

void _JsonValue::append(uint64_t value) {
    jvalue.append(value);
}

void _JsonValue::append(Boolean value) {
    jvalue.append(value->toValue());
}

void _JsonValue::append(bool value) {
    jvalue.append(value);
}

void _JsonValue::append(Double value) {
    jvalue.append(value->toValue());
}

void _JsonValue::append(double value) {
    jvalue.append(value);
}

void _JsonValue::append(sp<_JsonValue> value) {
    jvalue.append(value->jvalue);
}

sp<_JsonValue> _JsonValue::getValueAt(int index) {
    Json::Value v = jvalue[index];
    if(!v.isNull()) {
        return createJsonValue(v,S(jvalue.getMemberNames()[index]));
    }

    return nullptr;
}

sp<_JsonValue> _JsonValue::getListItemAt(unsigned int index) {
    Json::Value v = jvalue[index];
    if(!v.isNull()) {
        return createJsonValue(v);
    }

    return nullptr;
}

String _JsonValue::getStringAt(int index) {
    Json::Value v = jvalue[index];
    if(!v.isNull()) {
        return createString(jvalue[index].asString());
    }
    
    return nullptr;
}

Integer _JsonValue::getIntegerAt(int index) {
    Json::Value v = jvalue[index];
    if(!v.isNull()) {
        return createString(jvalue[index].asString())->toInteger();
    }

    return nullptr;
}
    
Boolean _JsonValue::getBooleanAt(int index) {
    Json::Value v = jvalue[index];
    if(!v.isNull()) {
        return createBoolean(jvalue[index].asBool());
    }
    
    return nullptr;
}

Double _JsonValue::getDoubleAt(int index) {
    Json::Value v = jvalue[index];
    if(!v.isNull()) {
        return createDouble(jvalue[index].asDouble());
    }
    
    return nullptr;
}

String _JsonValue::toString() {
    return createString(jvalue.toStyledString());
}

//iterator----------------------------
sp<_JsonValueIterator> _JsonValue::getIterator() {
    return AutoClone(new _JsonValueIterator(AutoClone(this)));
}

//JsonValueIterator
_JsonValueIterator::_JsonValueIterator(JsonValue v) {
    value = v;
    index = 0;
    isArrayMember = true;
    if(!v->jvalue.isArray()) {
        mMembers = v->jvalue.getMemberNames();
        isArrayMember = false;
        size = mMembers.size();
    } else {
        size = v->jvalue.size();
    }
}

String _JsonValueIterator::getTag() {
    if(index == size) {
        return nullptr;
    }
    
    return createString(mMembers[index]);
}

bool _JsonValueIterator::hasValue() {
    printf("index is %d,size is %d \n",index,size);
    return index < size;
}

bool _JsonValueIterator::next() {
    index++;
    if(index == size) {
        return false;
    }

    return true;
}

bool _JsonValueIterator::isBool() {
    std::string ss = mMembers[index];

    return (value->jvalue)[ss].isBool();
}

bool _JsonValueIterator::isInt() {
    std::string ss = mMembers[index];

    return (value->jvalue)[ss].isInt();
}

bool _JsonValueIterator::isString() {
    std::string ss = mMembers[index];

    return (value->jvalue)[ss].isString();
}

bool _JsonValueIterator::isDouble() {
    std::string ss = mMembers[index];

    return (value->jvalue)[ss].isDouble();
}

bool _JsonValueIterator::isArray() {
    std::string ss = mMembers[index];

    return (value->jvalue)[ss].isArray();
}

bool _JsonValueIterator::isObject() {
    std::string ss = mMembers[index];

    return (value->jvalue)[ss].isObject();
}

sp<_JsonValue> _JsonValueIterator::getValue() {
    if(isArrayMember) {
        return createJsonValue((value->jvalue)[index]);
    }

    std::string ss = mMembers[index];
    Json::Value v = (value->jvalue)[ss];
    if(v.isNull()) {
        return nullptr;
    }

    return createJsonValue(v,S(ss));
}

String _JsonValueIterator::getString() {
    std::string ss = mMembers[index];
    Json::Value v = (value->jvalue)[ss];
    if(v.isNull()) {
        return nullptr;
    }

    return createString((value->jvalue)[ss].asString());
}

Integer _JsonValueIterator::getInteger() {
    std::string ss = mMembers[index];
    Json::Value v = (value->jvalue)[ss];
    if(v.isNull()) {
        return nullptr;
    }

    return createInteger((value->jvalue)[ss].asInt());
}

Boolean _JsonValueIterator::getBoolean() {
    std::string ss = mMembers[index];
    Json::Value v = (value->jvalue)[ss];
    if(v.isNull()) {
        return nullptr;
    }

    return createBoolean((value->jvalue)[ss].asBool());   
}

Double _JsonValueIterator::getDouble() {
    std::string ss = mMembers[index];
    Json::Value v = (value->jvalue)[ss];
    if(v.isNull()) {
        return nullptr;
    }

    return createDouble((value->jvalue)[ss].asDouble());
}

sp<_JsonValue> _JsonValueIterator::getObject() {
    std::string ss = mMembers[index];
    Json::Value v = (value->jvalue)[ss];
    if(v.isNull()) {
        return nullptr;
    }
    return createJsonValue((value->jvalue)[ss],S(ss));   
}
}