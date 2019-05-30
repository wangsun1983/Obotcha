#include <iostream>
#include "json/value.h"
#include "JsonValue.hpp"
#include "JsonArray.hpp"

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

void _JsonValue::put(String tag,char *value) {
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

void _JsonValue::put(sp<_JsonArray> v) {
    
    const char *name = v->getName()->toChars();

    //Json::Value *value = new Json::Value(*v->jvalue);
    jvalue[name]= v->jvalue;
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

    //Json::Value *v = &jvalue[tag->toChars()];
    //if(v->isArray()) {
    //    delete v;
    //} else if(v->isObject()) {
    //    delete v;
    //}

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

int _JsonValue::size() { 
    return jvalue.size();
}

Integer _JsonValue::getInteger() {
    int v = jvalue.asInt();
    return createInteger(v);
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

sp<_JsonValue> _JsonValue::getObject(String tag) {
    if(tag == nullptr) {
        return nullptr;
    }

    if(contains(tag)) {
        Json::Value value = jvalue[tag->toChars()];
        return createJsonValue(value);
    }
    
    return nullptr;
}

sp<_JsonArray> _JsonValue::getArray(String tag) {
    //printf("getArray tag is %s \n",tag->toChars());
    if(tag == nullptr) {
        return nullptr;
    }
    //printf("getArray trace \n");
    if(contains(tag)) {
        //printf("getArray trace2 \n");
        Json::Value value = jvalue[tag->toChars()];
        return createJsonArray(tag,value);
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

bool _JsonValue::isString() {
    return jvalue.isString();
}

bool _JsonValue::isDouble() {
    return jvalue.isDouble();
}

bool _JsonValue::isArray() {
    return jvalue.isArray();
}

sp<_JsonValueIterator> _JsonValue::getIterator() {
    return new _JsonValueIterator(this);
}

//JsonValueIterator
_JsonValueIterator::_JsonValueIterator(JsonValue v) {
    value = v;
    count = 0;
}

_JsonValueIterator::_JsonValueIterator(_JsonValue *v) {
    value.set_pointer(v);
    //v->incStrong(0);

    count = 0;
}

String _JsonValueIterator::getTag() {
    
    if(count == value->jvalue.getMemberNames().size()) {
        return nullptr;
    }
    
    return createString(value->jvalue.getMemberNames()[count]);
}

bool _JsonValueIterator::hasValue() {
    return count < value->jvalue.getMemberNames().size();
}

bool _JsonValueIterator::next() {
    count++;
    if(count == value->jvalue.getMemberNames().size()) {
        return false;
    }

    return true;
}

bool _JsonValueIterator::isBool() {
    std::string ss = value->jvalue.getMemberNames()[count];

    return (value->jvalue)[ss].isBool();
}

bool _JsonValueIterator::isInt() {
    std::string ss = value->jvalue.getMemberNames()[count];

    return (value->jvalue)[ss].isInt();
}

bool _JsonValueIterator::isString() {
    std::string ss = value->jvalue.getMemberNames()[count];

    return (value->jvalue)[ss].isString();
}

bool _JsonValueIterator::isDouble() {
    std::string ss = value->jvalue.getMemberNames()[count];

    return (value->jvalue)[ss].isDouble();
}

bool _JsonValueIterator::isArray() {
    std::string ss = value->jvalue.getMemberNames()[count];

    return (value->jvalue)[ss].isArray();
}

}