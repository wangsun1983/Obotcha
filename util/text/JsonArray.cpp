#include "json/value.h"

#include "JsonArray.hpp"
#include "JsonValue.hpp"

namespace obotcha {

_JsonArray::_JsonArray(String s) {
    name = s;
    //jvalue = new Json::Value();
}

_JsonArray::_JsonArray(String s,Json::Value v) {
    name = s;
    jvalue = v;
}

void _JsonArray::append(String value) {
    jvalue.append(value->toChars());
}

void _JsonArray::append(char *value) {
    jvalue.append(value);
}

void _JsonArray::append(std::string value) {
    jvalue.append(value);
}

void _JsonArray::append(Integer value) {
    jvalue.append(value->toValue());
}

void _JsonArray::append(int value) {
    jvalue.append(value);
}

void _JsonArray::append(Boolean value) {
    jvalue.append(value->toValue());
}

void _JsonArray::append(bool value) {
    jvalue.append(value);
}

void _JsonArray::append(Double value) {
    jvalue.append(value->toValue());
}

void _JsonArray::append(double value) {
    jvalue.append(value);
}

void _JsonArray::append(sp<_JsonValue> value) {
    jvalue.append(value->jvalue);
}

String _JsonArray::getName() {
    return name;
}

sp<_JsonValue> _JsonArray::getValue(int index) {
    return createJsonValue(jvalue[index]);
}

int _JsonArray::size() {
    return jvalue.size();
}

_JsonArray::~_JsonArray() {
    //delete jvalue;
}


}