#include "Field.hpp"

namespace obotcha {

const int _Field::FieldTypeInt = 0;
const int _Field::FieldTypeByte = 1;
const int _Field::FieldTypeByteArray = 2;
const int _Field::FieldTypeDouble = 3;
const int _Field::FieldTypeFloat = 4;
const int _Field::FieldTypeString = 5;
const int _Field::FieldTypeUint8 = 6;
const int _Field::FieldTypeUint16 = 7;
const int _Field::FieldTypeUint32 = 8;
const int _Field::FieldTypeUint64 = 9;
const int _Field::FieldTypeVector = 10;
const int _Field::FieldTypeArrayList = 11;
const int _Field::FieldTypeObject = 12;

int _Field::TypeOf(int v) {
    return FieldTypeInt;
}

int _Field::TypeOf(byte v) {
    return FieldTypeByte;
}

int _Field::TypeOf(ByteArray v) {
    return FieldTypeByteArray;
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

void _Field::setName(String n) {
    name = n;
}

void _Field::setType(int t) {
    type = t;
}

}
