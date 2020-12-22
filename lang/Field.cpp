#include "Field.hpp"
#include "ReflectException.hpp"

namespace obotcha {

int _Field::TypeOf(int v) {
    return FieldTypeInt;
}

int _Field::TypeOf(byte v) {
    return FieldTypeByte;
}

int _Field::TypeOf(double v) {
    return FieldTypeDouble;
}

int _Field::TypeOf(float v) {
    return FieldTypeFloat;
}

int _Field::TypeOf(uint16_t v) {
    return FieldTypeUint16;
}

int _Field::TypeOf(uint32_t v) {
    return FieldTypeUint32;
}

int _Field::TypeOf(uint64_t v) {
    return FieldTypeUint64;
}

int _Field::TypeOf(bool v) {
    return FieldTypeBool;
}

int _Field::TypeOf(long v) {
    return FieldTypeLong;
}

int _Field::TypeOf(String v) {
    return FieldTypeString;
}

/*
int _Field::TypeOf(Integer v) {
    return FieldTypeInt;
}

int _Field::TypeOf(Float v) {
    return FieldTypeFloat;
}



int _Field::TypeOf(Uint8 v) {
    return FieldTypeUint8;
}

int _Field::TypeOf(Uint16 v) {
    return FieldTypeUint16;
}

int _Field::TypeOf(Uint32 v) {
    return FieldTypeUint32;
}

int _Field::TypeOf(Uint64 v) {
    return FieldTypeUint64;
}

int _Field::TypeOf(bool v) {
    return FieldTypeBool;
}

int _Field::TypeOf(long v) {
    return FieldTypeLong;
}
*/
String _Field::getName() {
    return name;
}

int _Field::getType() {
    return type;
}

int _Field::getId() {
    return id;
}

void _Field::setName(String n) {
    name = n;
}

void _Field::setType(int t) {
    type = t;
}

void _Field::setId(int d) {
    id = d;
}

void _Field::setReflectObject(Object *obj) {
    object = obj;
}

void _Field::setValue(int v) {
    switch(type) {
        case FieldTypeInt:
            object->setFieldIntValue(name->getStdString(),v);
        break;

        case FieldTypeByte:
            setValue((uint8_t)v);
        break;

        case FieldTypeLong:
            setValue((long)v);
        break;

        case FieldTypeUint16:
            setValue((uint16_t)v);
        break;

        case FieldTypeUint32:
            setValue((uint32_t)v);
        break;

        case FieldTypeUint64:
            setValue((uint64_t)v);
        break;
    }

    return;
}

void _Field::setValue(long v) {
    object->setFieldLongValue(name->getStdString(),v);
}

void _Field::setValue(uint8_t v) {
    object->setFieldByteValue(name->getStdString(),v);
}

void _Field::setValue(double v) {
    switch(type) {
        case FieldTypeDouble:
            object->setFieldDoubleValue(name->getStdString(),v);
        break;

        case FieldTypeFloat:
            object->setFieldFloatValue(name->getStdString(),v);
        break;
    }
}

void _Field::setValue(float v) {
    object->setFieldFloatValue(name->getStdString(),v);
}

void _Field::setValue(uint16_t v) {
    object->setFieldUint16Value(name->getStdString(),v);
}

void _Field::setValue(uint32_t v) {
    object->setFieldUint32Value(name->getStdString(),v);
}

void _Field::setValue(uint64_t v) {
    object->setFieldUint64Value(name->getStdString(),v);
}

void _Field::setValue(sp<Object> v) {
    //object->setFieldObjectValue(name->getStdString(),v);
    Trigger(ReflectException,"not support set Object value");
}

void _Field::setValue(String v) {
    object->setFieldStringValue(name->getStdString(),v->getStdString());
}

void _Field::setValue(bool v) {
    object->setFieldBoolValue(name->getStdString(),v);
}

int _Field::getIntValue() {
    return object->getFieldIntValue(name->getStdString());
}

byte _Field::getByteValue() {
    return object->getFieldByteValue(name->getStdString());
}

double _Field::getDoubleValue() {
    return object->getFieldDoubleValue(name->getStdString());
}

long _Field::getLongValue() {
    return object->getFieldLongValue(name->getStdString());
}

float _Field::getFloatValue() {
    return object->getFieldFloatValue(name->getStdString());
}

byte _Field::getUint8Value() {
    return object->getFieldByteValue(name->getStdString());
}

uint16_t _Field::getUint16Value() {
    return object->getFieldUint16Value(name->getStdString());
}

uint32_t _Field::getUint32Value() {
    return object->getFieldUint32Value(name->getStdString());
}

uint64_t _Field::getUint64Value() {
    return object->getFieldUint64Value(name->getStdString());
}

sp<Object> _Field::getObjectValue() {
    return object->getFieldObjectValue(name->getStdString());
}

String _Field::getStringValue() {
    return object->getFieldStringValue(name->getStdString());
}

bool _Field::getBoolValue() {
    return object->getFieldBoolValue(name->getStdString());
}

sp<Object> _Field::createObject() {
    object->createFieldObject(name->getStdString());
    return object->getFieldObjectValue(name->getStdString());
}

sp<Object>  _Field::createListItemObject() {
    return object->createListItemObject(name->getStdString());
}

sp<Object> _Field::getListItemObject(int index) {
    return object->getListItemObject(name->getStdString(),index);
}

}