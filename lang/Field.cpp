#include "Field.hpp"
#include "ReflectException.hpp"

namespace obotcha {

_Field::_Field() {object = nullptr;}

int _Field::TypeOf(int ) const { 
    return FieldTypeInt;
}

int _Field::TypeOf(byte ) const { 
    return FieldTypeByte;
}

int _Field::TypeOf(double ) const { 
    return FieldTypeDouble;
}

int _Field::TypeOf(float ) const { 
    return FieldTypeFloat;
}

int _Field::TypeOf(uint16_t ) const { 
    return FieldTypeUint16;
}

int _Field::TypeOf(uint32_t ) const { 
    return FieldTypeUint32;
}

int _Field::TypeOf(uint64_t ) const { 
    return FieldTypeUint64;
}

int _Field::TypeOf(bool ) const { 
    return FieldTypeBool;
}

int _Field::TypeOf(long ) const { 
    return FieldTypeLong;
}

int _Field::TypeOf(String ) const { 
    return FieldTypeString;
}

String _Field::getName() const { 
    return name;
}

int _Field::getType() const { 
    return type;
}

int _Field::getId() const { 
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

void _Field::setReflectObject(_Object *obj) { 
    object = obj;
}

void _Field::setValue(int v) {
    switch (type) {
        case FieldTypeInt:
            object->__setFieldIntValue(name->getStdString(), v);
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
        
        default:
            return;
    }
}

void _Field::setValue(long v) {
    object->__setFieldLongValue(name->getStdString(), v);
}

void _Field::setValue(uint8_t v) {
    object->__setFieldByteValue(name->getStdString(), v);
}

void _Field::setValue(double v) {
    switch (type) {
        case FieldTypeDouble:
            object->__setFieldDoubleValue(name->getStdString(), v);
            break;

        case FieldTypeFloat:
            object->__setFieldFloatValue(name->getStdString(), v);
            break;
        
        default:
            return;
    }
}

void _Field::setValue(float v) {
    object->__setFieldFloatValue(name->getStdString(), v);
}

void _Field::setValue(uint16_t v) {
    object->__setFieldUint16Value(name->getStdString(), v);
}

void _Field::setValue(uint32_t v) {
    object->__setFieldUint32Value(name->getStdString(), v);
}

void _Field::setValue(uint64_t v) {
    object->__setFieldUint64Value(name->getStdString(), v);
}

void _Field::setValue(String v) {
    object->__setFieldStringValue(name->getStdString(), v->getStdString());
}

void _Field::setValue(bool v) {
    object->__setFieldBoolValue(name->getStdString(), v);
}

int _Field::getIntValue() {
    return object->__getFieldIntValue(name->getStdString());
}

byte _Field::getByteValue() {
    return object->__getFieldByteValue(name->getStdString());
}

double _Field::getDoubleValue() {
    return object->__getFieldDoubleValue(name->getStdString());
}

long _Field::getLongValue() {
    return object->__getFieldLongValue(name->getStdString());
}

float _Field::getFloatValue() {
    return object->__getFieldFloatValue(name->getStdString());
}

byte _Field::getUint8Value() {
    return object->__getFieldByteValue(name->getStdString());
}

uint16_t _Field::getUint16Value() {
    return object->__getFieldUint16Value(name->getStdString());
}

uint32_t _Field::getUint32Value() {
    return object->__getFieldUint32Value(name->getStdString());
}

uint64_t _Field::getUint64Value() {
    return object->__getFieldUint64Value(name->getStdString());
}

sp<_Object> _Field::getObjectValue() {
    return object->__getFieldObjectValue(name->getStdString());
}

String _Field::getStringValue() {
    return object->__getFieldStringValue(name->getStdString());
}

bool _Field::getBoolValue() {
    return object->__getFieldBoolValue(name->getStdString());
}

sp<_Object> _Field::createObject() {
    object->__createFieldObject(name->getStdString());
    return object->__getFieldObjectValue(name->getStdString());
}

sp<_Object> _Field::createListItemObject() {
    return object->__createListItemObject(name->getStdString());
}

sp<_Object> _Field::getListItemObject(int index) {
    return object->__getListItemObject(name->getStdString(), index);
}

int _Field::getContainerSize() {
    if(object == nullptr) {
        return 0;
    }
    return object->__getContainerSize(name->getStdString());
}

sp<_Pair<sp<_Object>, sp<_Object>>> _Field::createMapItemObject() {
    return object->__createMapItemObject(name->getStdString());
}

ArrayList<Pair<sp<_Object>, sp<_Object>>> _Field::getMapItemObjects() {
    if(object == nullptr) {
        return nullptr;
    }
    return object->__getMapItemObjects(name->getStdString());
}

void _Field::addListItemObject(sp<_Object> v) {
    object->__addListItemObject(name->getStdString(), v);
}

void _Field::addMapItemObject(sp<_Object> k, sp<_Object> v) {
    object->__addMapItemObject(name->getStdString(), k, v);
}

} // namespace obotcha