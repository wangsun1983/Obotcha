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
    static const int FieldTypeInt;
    static const int FieldTypeByte;
    static const int FieldTypeByteArray;
    static const int FieldTypeDouble;
    static const int FieldTypeFloat;
    static const int FieldTypeString;
    static const int FieldTypeUint8;
    static const int FieldTypeUint16;
    static const int FieldTypeUint32;
    static const int FieldTypeUint64;
    static const int FieldTypeVector;
    static const int FieldTypeArrayList;
    static const int FieldTypeObject;

    int TypeOf(int v);
    int TypeOf(byte v);
    int TypeOf(ByteArray v);
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

    void setName(String);

    void setType(int);

    template<typename T>
    void setValue(T value) {
        _FieldContent<decltype(value)> *t= dynamic_cast<_FieldContent<decltype(value)> *>(this);
        t->setfunc(value);
    }

private:
    int type;
    String name;    
};

DECLARE_CLASS(FieldContent,1) EXTENDS(Field)  {
public:    
    std::function<void(T)> setfunc;
    std::function<T(void)> getfunc;
    _FieldContent(std::function<void(T)> set,std::function<T(void)>get) {
        setfunc = set;
        getfunc = get;
    }
};    

}
#endif