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
    
    template<typename T,typename Y>
    void setFieldValue(T obj,Y value) {
        const int index = this->id;
        std::get<0>(obj->setFuncTuple)(value);
    }

#define SWITCH_CASE(V) \
    case V:\
    if(tupleTestSize > V) {\
        return std::get<V>(obj->getFuncTuple)();\
    }\
    break;\

    template<typename T>
    auto getFieldValue(T obj){
        int tupleTestSize = std::tuple_size<decltype(obj->getFuncTuple)>::value;
        switch(this->id) {
            SWITCH_CASE(0)
            SWITCH_CASE(1)
            SWITCH_CASE(2)
            SWITCH_CASE(3)
            SWITCH_CASE(4)
            SWITCH_CASE(5)
            SWITCH_CASE(6)
            SWITCH_CASE(7)
            SWITCH_CASE(8)
            SWITCH_CASE(9)
            SWITCH_CASE(10)
            SWITCH_CASE(11)
            SWITCH_CASE(12)
            SWITCH_CASE(13)
            SWITCH_CASE(14)
            SWITCH_CASE(15) 
        }
    }

private:
    int type;
    String name;
    int id;
};

}
#endif