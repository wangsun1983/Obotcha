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

DECLARE_SIMPLE_CLASS(Field) {
public:
    enum {
        FieldTypeInt = 0,
        FieldTypeByte,
        FieldTypeDouble,
        FieldTypeFloat,
        FieldTypeLong,
        FieldTypeString, 
        FieldTypeUint16,
        FieldTypeUint32,
        FieldTypeUint64,
        FieldTypeBool,
        FieldTypeVector,//??
        FieldTypeArrayList,
        FieldTypeObject,
        FieldTypeUnKnow,
    };

    //wangsl
    static const int FieldTypeUint8 = FieldTypeByte;
    
    int TypeOf(int v);
    int TypeOf(byte v);
    int TypeOf(double v);
    int TypeOf(float v);
    int TypeOf(bool v);
    int TypeOf(long v);
    int TypeOf(uint16_t v);
    int TypeOf(uint32_t v);
    int TypeOf(uint64_t v);
    int TypeOf(String v);

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
    
    void setReflectObject(_Object *obj);

    //reflect filed set function
    void setValue(int);
    void setValue(long);
    void setValue(uint8_t);
    void setValue(double);
    void setValue(float);
    void setValue(uint16_t);
    void setValue(uint32_t);
    void setValue(uint64_t);
    void setValue(sp<_Object>);
    void setValue(String value);
    void setValue(bool);

    //reflect filed get function
    int getIntValue();
    byte getByteValue();
    double getDoubleValue();
    long getLongValue();
    float getFloatValue();
    uint8_t getUint8Value();
    uint16_t getUint16Value();
    uint32_t getUint32Value();
    uint64_t getUint64Value();
    sp<_Object> getObjectValue();
    String getStringValue();
    bool getBoolValue();

    int getListObjectSize();
    sp<_Object> getListItemObject(int);

    //reflect filed create function
    sp<_Object> createObject();
    sp<_Object> createListItemObject();

    //std::function<void()> createfunc;
private:
    int type;
    String name;
    int id;
    _Object *object;

    //do not use
    void __setFieldIntValue(std::string,int){}
    void __setFieldByteValue(std::string,uint8_t){}
    void __setFieldDoubleValue(std::string,double){}
    void __setFieldFloatValue(std::string,float){}
    void __setFieldUint8Value(std::string,uint8_t){}
    void __setFieldUint16Value(std::string,uint16_t){}
    void __setFieldUint32Value(std::string,uint32_t){}
    void __setFieldUint64Value(std::string,uint64_t){}
    void __setFieldObjectValue(std::string,sp<_Object>){}
    void __setFieldStringValue(std::string name,std::string value){}
    void __setFieldBoolValue(std::string name,bool){}
};

DECLARE_CLASS(FieldContent,1) IMPLEMENTS(Field)  {
public:    
    std::function<void(T)> setfunc;

    _FieldContent(std::function<void(T)> set) {
        setfunc = set;
    }
};    

DECLARE_SIMPLE_CLASS(FieldContentValue) {
public:
    int intValue;
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