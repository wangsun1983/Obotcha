#include "Field.hpp"

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

int _Field::TypeOf(Float v) {
    return FieldTypeFloat;
}

int _Field::TypeOf(String v) {
    return FieldTypeString;
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
}
