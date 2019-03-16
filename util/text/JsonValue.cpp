#include <iostream>
#include "json/value.h"
#include "JsonValue.hpp"
#include "JsonArray.hpp"

#include "Log.hpp"

namespace obotcha {

_JsonValue::~_JsonValue() {
    delete(jvalue);
}

_JsonValue::_JsonValue() {
    jvalue = new Json::Value();
}

_JsonValue::_JsonValue(Json::Value v) {
    jvalue = new Json::Value(v);
}

_JsonValue::_JsonValue(sp<_JsonValue> v) {
    jvalue = new Json::Value(*v->jvalue);
}


void _JsonValue::put(String tag,String value) {
    (*jvalue)[tag->getStdString()] = value->toChars();
}

void _JsonValue::put(String tag,char *value) {
    (*jvalue)[tag->toChars()] = value;
}

void _JsonValue::put(String tag,std::string value) {
    (*jvalue)[tag->toChars()] = value;
}

void _JsonValue::put(String tag,Integer value) {
    (*jvalue)[tag->toChars()] = value->toValue();
}

void _JsonValue::put(String tag,int value) {
    (*jvalue)[tag->toChars()] = value;
}

void _JsonValue::put(String tag,Boolean value) {
    (*jvalue)[tag->toChars()] = value->toValue();
}

void _JsonValue::put(String tag,bool value) {
    (*jvalue)[tag->toChars()] = value;
}

void _JsonValue::put(String tag,Double value) {
    (*jvalue)[tag->toChars()] = value->toValue();
}

void _JsonValue::put(String tag,double value) {
    (*jvalue)[tag->toChars()] = value;
}

void _JsonValue::put(sp<_JsonArray> value) {
    //jvalue[value->getName()->toChars()] = value->jvalue;
    //jvalue.swap(value->jvalue);
    const char *name = value->getName()->toChars();

    int size = (*(value->jvalue))[name].size();
    for(int i = 0;i<size;i++) {
        (*jvalue)[name].append((*(value->jvalue))[name][i].asString());
    }
}

String _JsonValue::getString(String tag) {
    if(jvalue->isMember(tag->toChars())) {
        std::string v = (*jvalue)[tag->toChars()].asString();
        return createString(v);
    }

    return nullptr;
}

Integer _JsonValue::getInteger(String tag) {
    if(jvalue->isMember(tag->toChars())) {
        int v = (*jvalue)[tag->toChars()].asInt();
        return createInteger(v);
    }

    return nullptr;
}

Boolean _JsonValue::getBoolean(String tag) {
    if(jvalue->isMember(tag->toChars())) {
        bool v = (*jvalue)[tag->toChars()].asBool();
        return createBoolean(v);
    }

    return nullptr;
}

Double _JsonValue::getDouble(String tag) {
    if(jvalue->isMember(tag->toChars())) {
        double v = (*jvalue)[tag->toChars()].asDouble();
        return createDouble(v);
    }

    return nullptr; 
}

sp<_JsonValue> _JsonValue::getObject(String tag) {
    if(contains(tag)) {
        Json::Value value = (*jvalue)[tag->toChars()];
        return createJsonValue(value);
    }
    
    return nullptr;
}

bool _JsonValue::contains(String tag) {
    return jvalue->isMember(tag->toChars());
}


bool _JsonValue::isBool() {
    return jvalue->isBool();
}

bool _JsonValue::isInt() {
    return jvalue->isInt();
}

bool _JsonValue::isString() {
    return jvalue->isString();
}

bool _JsonValue::isDouble() {
    return jvalue->isDouble();
}

bool _JsonValue::isArray() {
    return jvalue->isArray();
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
    v->incStrong(0);

    count = 0;
}

String _JsonValueIterator::getTag() {
    
    if(count == value->jvalue->getMemberNames().size()) {
        return nullptr;
    }
    
    return createString(value->jvalue->getMemberNames()[count]);
}

bool _JsonValueIterator::hasValue() {
    return count < value->jvalue->getMemberNames().size();
}

bool _JsonValueIterator::next() {
    count++;
    if(count == value->jvalue->getMemberNames().size()) {
        return false;
    }

    return true;
}

bool _JsonValueIterator::isBool() {
    std::string ss = value->jvalue->getMemberNames()[count];

    return (*(value->jvalue))[ss].isBool();
}

bool _JsonValueIterator::isInt() {
    std::string ss = value->jvalue->getMemberNames()[count];

    return (*(value->jvalue))[ss].isInt();
}

bool _JsonValueIterator::isString() {
    std::string ss = value->jvalue->getMemberNames()[count];

    return (*(value->jvalue))[ss].isString();
}

bool _JsonValueIterator::isDouble() {
    std::string ss = value->jvalue->getMemberNames()[count];

    return (*(value->jvalue))[ss].isDouble();
}

bool _JsonValueIterator::isArray() {
    std::string ss = value->jvalue->getMemberNames()[count];

    return (*(value->jvalue))[ss].isArray();
}

}