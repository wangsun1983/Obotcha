#include "json/value.h"

#include "JsonArray.hpp"
#include "JsonValue.hpp"

namespace obotcha {

_JsonArray::_JsonArray(String s) {
    name = s;
    jvalue = new Json::Value();
}

void _JsonArray::append(String value) {
    (*jvalue)[name->toChars()].append(value->toChars());
}

void _JsonArray::append(char *value) {
    (*jvalue)[name->toChars()].append(value);
}

void _JsonArray::append(std::string value) {
    (*jvalue)[name->toChars()].append(value);
}

void _JsonArray::append(Integer value) {
    (*jvalue)[name->toChars()].append(value->toValue());
}

void _JsonArray::append(int value) {
    (*jvalue)[name->toChars()].append(value);
}

void _JsonArray::append(Boolean value) {
    (*jvalue)[name->toChars()].append(value->toValue());
}

void _JsonArray::append(bool value) {
    (*jvalue)[name->toChars()].append(value);
}

void _JsonArray::append(Double value) {
    (*jvalue)[name->toChars()].append(value->toValue());
}

void _JsonArray::append(double value) {
    (*jvalue)[name->toChars()].append(value);
}

void _JsonArray::append(sp<_JsonValue> value) {
    (*jvalue)[name->toChars()].append(value->jvalue);
}

String _JsonArray::getName() {
    return name;
}

_JsonArray::~_JsonArray() {
    delete jvalue;
}


}