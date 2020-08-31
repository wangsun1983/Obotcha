#ifndef __OBOTCHA_FIELD_HPP__
#define __OBOTCHA_FIELD_HPP__

#include <vector>
#include <functional>
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"
#include "ByteArray.hpp"
#include "ArrayList.hpp"

namespace obotcha {

template<typename T>
class _FieldContent;

enum {
    FieldTypeInt = 0,
    FieldTypeByte,
    FieldTypeDouble,
    FieldTypeFloat,
    FieldTypeString,
    FieldTypeUint8,
    FieldTypeUint16,
    FieldTypeUint32,
    FieldTypeUint64,
    FieldTypeBool,
    FieldTypeVector,
    FieldTypeArrayList,
    FieldTypeObject,
    FieldTypeUnKnow,
};


DECLARE_SIMPLE_CLASS(Field) {
public:
    int TypeOf(int v);
    int TypeOf(byte v);
    int TypeOf(double v);
    int TypeOf(Float v);
    int TypeOf(String v);
    int TypeOf(Uint8 v);
    int TypeOf(Uint16 v);
    int TypeOf(Uint32 v);
    int TypeOf(Uint64 v);
    int TypeOf(bool v);

    template<typename T>
    int TypeOf(std::vector<T> v) {
        return FieldTypeVector;
    }

    template<typename T>
    int TypeOf(ArrayList<T> v) {
        return FieldTypeArrayList;
    }

    template<typename T>
    int TypeOf(T v) {
        return FieldTypeObject;
    }

    template<typename T>
    int TypenameOf(std::vector<T> v) {
        T t;
        return TypeOf(t);
    }

    template<typename T>
    int TypenameOf(ArrayList<T> v) {
        T t;
        return TypeOf(t);
    }
    
    String getName();

    int getType();

    int getId();

    void setName(String);

    void setType(int);

    void setId(int);
    
    std::function<void()> createfunc;
private:
    int type;
    String name;
    int id;
};

DECLARE_CLASS(FieldContent,1) EXTENDS(Field)  {
public:    
    std::function<void(T)> setfunc;

    _FieldContent(std::function<void(T)> set) {
        setfunc = set;
    }
};    

DECLARE_SIMPLE_CLASS(FieldContentValue) {
public:
    int intValue;
    byte byteValue;
    double doubleValue;
    bool boolValue;
    float floatValue;
    uint8_t uint8Value;
    uint16_t uint16Value;
    uint32_t uint32Value;
    uint64_t uint64Value;
    String stringValue;
    Object *objectValue;

    void set(int v) {
        intValue = v;
    }

    void set(double v) {
        doubleValue = v;
    }

    void set(bool v) {
        boolValue = v;
    }

    void set(float v) {
        floatValue = v;
    }

    void set(uint8_t v) {
        uint8Value = v;
    }

    void set(uint16_t v) {
        uint16Value = v;
    }

    void set(uint32_t v) {
        uint32Value = v;
    }

    void set(uint64_t v) {
        uint64Value = v;
    }

    void set(String v) {
        stringValue = v;
    }

    template<typename T>
    void set(sp<T> v) {
        objectValue = (Object *)v.get_pointer();
    }
};

}
#endif