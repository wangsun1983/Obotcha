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
    FieldTypeLong,
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
    int TypeOf(long v);

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
    
    void setReflectObject(Object *obj);

    //reflect filed set function
    void setValue(int);
    void setValue(unsigned char);
    void setValue(double);
    void setValue(float);
    void setValue(uint16_t);
    void setValue(uint32_t);
    void setValue(uint64_t);
    void setValue(sp<Object>);
    void setValue(String value);
    void setValue(bool);

    //reflect filed get function
    int getIntValue();
    byte getByteValue();
    double getDoubleValue();
    float getFloatValue();
    uint16_t getUint16Value();
    uint32_t getUint32Value();
    uint64_t getUint64Value();
    sp<Object> getObjectValue();
    String getStringValue();
    bool getBoolValue();

    //reflect filed create function
    void createObject();
    sp<Object> createListItemObject();

    //std::function<void()> createfunc;
private:
    int type;
    String name;
    int id;
    Object *object;

    //do not use
    void setFieldIntValue(std::string,int){}
    void setFieldByteValue(std::string,unsigned char){}
    void setFieldDoubleValue(std::string,double){}
    void setFieldFloatValue(std::string,float){}
    void setFieldUint8Value(std::string,uint8_t){}
    void setFieldUint16Value(std::string,uint16_t){}
    void setFieldUint32Value(std::string,uint32_t){}
    void setFieldUint64Value(std::string,uint64_t){}
    void setFieldObjectValue(std::string,sp<Object>){}
    void setFieldStringValue(std::string name,std::string value){}
    void setFieldBoolValue(std::string name,bool){}
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
    long longValue;
    uint8_t uint8Value;
    uint16_t uint16Value;
    uint32_t uint32Value;
    uint64_t uint64Value;
    String stringValue;
    Object *objectValue;

    void set(long v) {
        longValue = v;
    }

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