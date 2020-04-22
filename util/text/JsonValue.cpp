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
}

_JsonValue::_JsonValue(Json::Value v) {
    jvalue = v;//new Json::Value(v);
}

_JsonValue::_JsonValue(sp<_JsonValue> v) {
    jvalue = v->jvalue;//new Json::Value(*v->jvalue);
}


void _JsonValue::put(String tag,String value) {
    if(value == nullptr || tag == nullptr) {
        return;
    }

    jvalue[tag->getStdString()] = value->toChars();
}

void _JsonValue::put(String tag,const char *value) {
    if(value == nullptr || tag == nullptr) {
        return;
    }
    
    jvalue[tag->toChars()] = value;
}

void _JsonValue::put(String tag,std::string value) {
    if(tag == nullptr) {
        return;
    }
    
    jvalue[tag->toChars()] = value;
}

void _JsonValue::put(String tag,Integer value) {
    if(value == nullptr || tag == nullptr) {
        return;
    }

    jvalue[tag->toChars()] = value->toValue();
}

void _JsonValue::put(String tag,int value) {
    if(tag == nullptr) {
        return;
    }

    jvalue[tag->toChars()] = value;
}

void _JsonValue::put(String tag,Boolean value) {
    if(value == nullptr || tag == nullptr) {
        return;
    }

    jvalue[tag->toChars()] = value->toValue();
}

void _JsonValue::put(String tag,bool value) {
    if(tag == nullptr) {
        return;
    }

    jvalue[tag->toChars()] = value;
}

void _JsonValue::put(String tag,Double value) {
    if(value == nullptr || tag == nullptr) {
        return;
    }

    jvalue[tag->toChars()] = value->toValue();
}

void _JsonValue::put(String tag,double value) {
    if(tag == nullptr) {
        return;
    }

    jvalue[tag->toChars()] = value;
}

void _JsonValue::put(String tag,Uint64 value) {
    put(tag,value->toValue());
}

void _JsonValue::put(String tag,uint64_t value) {
    if(tag == nullptr) {
        return;
    }

    jvalue[tag->toChars()] = (Json::UInt)value;
}

void _JsonValue::put(String tag,sp<_JsonValue> v) {
    if(tag == nullptr) {
        return;
    }

    //Json::Value *value = new Json::Value(*v->jvalue);
    jvalue[tag->toChars()] = v->jvalue;
}

void _JsonValue::remove(String tag) {
    if(tag == nullptr) {
        return;
    }

    jvalue.removeMember(tag->toChars());
}

String _JsonValue::getString(String tag) {
    if(tag == nullptr) {
        return nullptr;
    }

    if(jvalue.isMember(tag->toChars())) {
        std::string v = jvalue[tag->toChars()].asString();
        return createString(v);
    }

    return nullptr;
}

String _JsonValue::getString() {
    std::string v = jvalue.asString();
    return createString(v);
}

Integer _JsonValue::getInteger(String tag) {
    if(jvalue.isMember(tag->toChars())) {
        int v = jvalue[tag->toChars()].asInt();
        return createInteger(v);
    }

    return nullptr;
}

Integer _JsonValue::getInteger() {
    int v = jvalue.asInt();
    return createInteger(v);
}

Uint64  _JsonValue::getUint64(String tag) {
    uint64_t v = (uint64_t)jvalue[tag->toChars()].asUInt64();
    return createUint64(v);
}

Uint64 _JsonValue::getUint64() {
    uint64_t v = (uint64_t)jvalue.asUInt64();
    return createUint64(v);
}

int _JsonValue::size() { 
    return jvalue.size();
}

Boolean _JsonValue::getBoolean(String tag) {
    if(tag == nullptr) {
        return nullptr;
    }

    if(jvalue.isMember(tag->toChars())) {
        bool v = jvalue[tag->toChars()].asBool();
        return createBoolean(v);
    }

    return nullptr;
}

Boolean _JsonValue::getBoolean() {
    bool v = jvalue.asBool();
    return createBoolean(v);
}


Double _JsonValue::getDouble(String tag) {
    if(tag == nullptr) {
        return nullptr;
    }

    if(jvalue.isMember(tag->toChars())) {
        double v = jvalue[tag->toChars()].asDouble();
        return createDouble(v);
    }

    return nullptr; 
}

Double _JsonValue::getDouble() {
    double v = jvalue.asDouble();
    return createDouble(v);
}

sp<_JsonValue> _JsonValue::getValue(String tag) {
    if(tag == nullptr) {
        return nullptr;
    }

    if(contains(tag)) {
        Json::Value value = jvalue[tag->toChars()];
        return createJsonValue(value);
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

void _JsonValue::append(Uint64 value) {
    jvalue.append((Json::UInt64)value->toValue());
}

void _JsonValue::append(int value) {
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
    return createJsonValue(jvalue[index]);
}


String _JsonValue::getStringAt(int index) {
    return createString(jvalue[index].asString());
}

Integer _JsonValue::getIntegerAt(int index) {
    return createInteger(jvalue[index].asInt());
}
    
Boolean _JsonValue::getBooleanAt(int index) {
    return createBoolean(jvalue[index].asBool());
}

Double _JsonValue::getDoubleAt(int index) {
    return createDouble(jvalue[index].asDouble());
}

//iterator----------------------------
sp<_JsonValueIterator> _JsonValue::getIterator() {
    return new _JsonValueIterator(this);
}

//JsonValueIterator
_JsonValueIterator::_JsonValueIterator(JsonValue v) {
    value = v;
    count = 0;

    mMembers = v->jvalue.getMemberNames();
}

_JsonValueIterator::_JsonValueIterator(_JsonValue *v) {
    value.set_pointer(v);
    //v->incStrong(0);
    mMembers = value->jvalue.getMemberNames();

    count = 0;
}

String _JsonValueIterator::getTag() {
    
    if(count == mMembers.size()) {
        return nullptr;
    }
    
    return createString(mMembers[count]);
}

bool _JsonValueIterator::hasValue() {
    return count < mMembers.size();
}

bool _JsonValueIterator::next() {
    count++;
    if(count == mMembers.size()) {
        return false;
    }

    return true;
}

bool _JsonValueIterator::isBool() {
    std::string ss = mMembers[count];

    return (value->jvalue)[ss].isBool();
}

bool _JsonValueIterator::isInt() {
    std::string ss = mMembers[count];

    return (value->jvalue)[ss].isInt();
}

bool _JsonValueIterator::isString() {
    std::string ss = mMembers[count];

    return (value->jvalue)[ss].isString();
}

bool _JsonValueIterator::isDouble() {
    std::string ss = mMembers[count];

    return (value->jvalue)[ss].isDouble();
}

bool _JsonValueIterator::isArray() {
    std::string ss = mMembers[count];

    return (value->jvalue)[ss].isArray();
}

bool _JsonValueIterator::isObject() {
    std::string ss = mMembers[count];

    return (value->jvalue)[ss].isObject();
}

sp<_JsonValue> _JsonValueIterator::getValue() {
    std::string ss = mMembers[count];

    return createJsonValue((value->jvalue)[ss]);
}

String _JsonValueIterator::getString() {
    std::string ss = mMembers[count];

    return createString((value->jvalue)[ss].asString());
}

Integer _JsonValueIterator::getInteger() {
    std::string ss = mMembers[count];
    return createInteger((value->jvalue)[ss].asInt());
}

Boolean _JsonValueIterator::getBoolean() {
    std::string ss = mMembers[count];
    return createBoolean((value->jvalue)[ss].asBool());   
}

Double _JsonValueIterator::getDouble() {
    std::string ss = mMembers[count];
    return createDouble((value->jvalue)[ss].asDouble());
}

sp<_JsonValue> _JsonValueIterator::getObject() {
    std::string ss = mMembers[count];
    return createJsonValue((value->jvalue)[ss]);   
}
}