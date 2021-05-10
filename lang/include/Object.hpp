#ifndef __OBOTCHA_OBJECT_H__
#define __OBOTCHA_OBJECT_H__

#include <stdint.h>
#include <sys/types.h>
#include <stdlib.h>
#include <utility>
#include <stdio.h>
#include <typeinfo>
#include <string>

#include "StrongPointer.hpp"

#define OBJ_DEC_FREE 0
#define OBJ_DEC_NO_FREE 1

namespace obotcha {

//just add class declaration for reflect
class _Field;
class _String;
template<typename T>
class _ArrayList;

//-------------------------- Declaration ----------------------------------//
class _Object {
public:
    friend class _Field;
    _Object() : mCount(0) { }

    inline void incStrong(__attribute__((unused)) const void* id) {
        __sync_fetch_and_add(&mCount, 1);
        return;
    }

    inline int decStrong(__attribute__((unused)) const void* id) {
        if (__sync_fetch_and_sub(&mCount, 1) == 1) {
            return OBJ_DEC_FREE;
        }
        return OBJ_DEC_NO_FREE;
    }

    //! DEBUGGING ONLY: Get current strong ref count.
    inline int32_t getStrongCount() {
        return mCount;
    }

    inline virtual bool equals(const _Object *m) {
        return this == m;
    }

    inline virtual bool equals(_Object &m) {
        return this == &m;
    }

    inline virtual ~_Object() {
    }

    inline virtual uint64_t hashcode() {
        return (uint64_t)this;
    }

    //reflect function
    inline virtual void __ReflectInit(){}
    //must not return null!!! or build failed
    inline virtual sp<_Field> getField(sp<_String>){throw "not support";}
    inline virtual sp<_ArrayList<sp<_Field>>> getAllFields(){throw "not support";}
    inline virtual sp<_String> __ReflectClassName(){throw "not support";}

protected:
    inline virtual int __getFieldIntValue(std::string){return 0;}
    inline virtual uint8_t __getFieldByteValue(std::string){return 0;}
    inline virtual bool __getFieldBoolValue(std::string){return true;}
    inline virtual double __getFieldDoubleValue(std::string){return 0.0;}
    inline virtual long __getFieldLongValue(std::string name){return 0;}
    inline virtual float __getFieldFloatValue(std::string){return 0.0;}
    inline virtual uint8_t __getFieldUint8Value(std::string){return 0;}
    inline virtual uint16_t __getFieldUint16Value(std::string){return 0;}
    inline virtual uint32_t __getFieldUint32Value(std::string){return 0;}
    inline virtual uint64_t __getFieldUint64Value(std::string){return 0;}
    inline virtual sp<_String> __getFieldStringValue(std::string name){throw "not support";};
    inline virtual sp<_Object> __getFieldObjectValue(std::string){return nullptr;}

    //reflect set function
    inline virtual void __setFieldIntValue(std::string,int){}
    inline virtual void __setFieldByteValue(std::string,uint8_t){}
    inline virtual void __setFieldDoubleValue(std::string,double){}
    inline virtual void __setFieldFloatValue(std::string,float){}
    inline virtual void __setFieldLongValue(std::string,long){}
    inline virtual void __setFieldUint8Value(std::string,uint8_t){}
    inline virtual void __setFieldUint16Value(std::string,uint16_t){}
    inline virtual void __setFieldUint32Value(std::string,uint32_t){}
    inline virtual void __setFieldUint64Value(std::string,uint64_t){}
    inline virtual void __setFieldObjectValue(std::string,sp<_Object>){}
    inline virtual void __setFieldStringValue(std::string name,std::string value){}
    inline virtual void __setFieldBoolValue(std::string name,bool){}
    
    //create function
    inline virtual void __createFieldObject(std::string name){}
    inline virtual sp<_Object> __createListItemObject(std::string name){return nullptr;}
    inline virtual sp<_Object> __getListItemObject(std::string name,int index){return nullptr;}
    inline virtual int __getListObjectSize(std::string name) {return 0;}

private:
    mutable volatile int32_t mCount;
};

//-------------------------- Implementation ----------------------------------//
using Object = sp<_Object>;

template<typename U>
sp<U> AutoClone(U *v) {
    sp<U> data;
    data.set_pointer(v);
    return data;
}

template<typename T,typename U>
T AutoClone(U *v) {
    T data;
    data.set_pointer(dynamic_cast<decltype(data.get_pointer())>(v));
    return data;
}

template<typename X,typename V>
X Cast(sp<V> t) {
    return AutoClone<X>(t.m_ptr);
}

}


//-------------------------- Macro for Class Declaration ----------------------------------//
#define MAKE_FUNCTION_0(Y) \
template<typename A=_##Y,typename... Args>\
sp<A> create##Y(Args&&... args) {\
    _Object* obj = new A(std::forward<Args>(args)...);\
    obj->__ReflectInit();\
    return AutoClone<sp<A>>(obj);\
}\


#define MAKE_FUNCTION_1(Y) \
template<typename T,typename A=_##Y<T>,typename... Args>\
sp<A> create##Y(Args&&... args) {\
    _Object* obj = new A(std::forward<Args>(args)...);\
    obj->__ReflectInit();\
    return AutoClone<sp<A>>(obj);\
}\

#define MAKE_FUNCTION_2(Y) \
template<typename T,typename U,typename A=_##Y<T,U>,typename... Args>\
sp<A> create##Y(Args&&... args) {\
    _Object* obj = new A(std::forward<Args>(args)...);\
    obj->__ReflectInit();\
    return AutoClone<sp<A>>(obj);\
}\


#define CLASS_PRE_DEF_0(YY) class _##YY
#define CLASS_PRE_DEF_1(YY) template<typename X>class _##YY
#define CLASS_PRE_DEF_2(YY) template<typename X,typename Z>class _##YY

#define TYPE_DEF_0(YY) typedef sp<_##YY> YY
#define TYPE_DEF_1(YY) \
template<typename UU> \
using YY = sp<_##YY<UU>>; \

#define TYPE_DEF_2(YY) \
template<typename UU,typename VV> \
using YY = sp<_##YY<UU,VV>>; \


#define TEPMLATE_DECLARE_0
#define TEPMLATE_DECLARE_1 template<typename T>
#define TEPMLATE_DECLARE_2 template<typename T,typename U>


#define DECLARE_CLASS(Y,U) \
CLASS_PRE_DEF_##U(Y); \
TYPE_DEF_##U(Y); \
MAKE_FUNCTION_##U(Y) \
TEPMLATE_DECLARE_##U \
class _##Y: virtual public _Object\

#define DECLARE_SIMPLE_CLASS(Y) DECLARE_CLASS(Y,0)


//-------------------------- Macro for Static Class Declaration ----------------------------------//
#define st(Y) _##Y

//-------------------------- Macro for Class Implementation ----------------------------------//
#define FL_ARG_COUNT(...) FL_INTERNAL_ARG_COUNT_PRIVATE(0, ##__VA_ARGS__,\
	64, 63, 62, 61, 60, \
	59, 58, 57, 56, 55, 54, 53, 52, 51, 50, \
	49, 48, 47, 46, 45, 44, 43, 42, 41, 40, \
	39, 38, 37, 36, 35, 34, 33, 32, 31, 30, \
	29, 28, 27, 26, 25, 24, 23, 22, 21, 20, \
	19, 18, 17, 16, 15, 14, 13, 12, 11, 10, \
	 9,  8,  7,  6,  5,  4,  3,  2,  1,  0)

#define FL_INTERNAL_ARG_COUNT_PRIVATE(\
	 _0,  _1,  _2,  _3,  _4,  _5,  _6,  _7,  _8,  _9, \
	_10, _11, _12, _13, _14, _15, _16, _17, _18, _19, \
	_20, _21, _22, _23, _24, _25, _26, _27, _28, _29, \
	_30, _31, _32, _33, _34, _35, _36, _37, _38, _39, \
	_40, _41, _42, _43, _44, _45, _46, _47, _48, _49, \
	_50, _51, _52, _53, _54, _55, _56, _57, _58, _59, \
	_60, _61, _62, _63, _64, N, ...) N

#define _IMPLEMENTS_1(A) ,virtual public _##A
#define _IMPLEMENTS_2(A,B) ,virtual public _##A,virtual public _##B

#define IMPLEMENTS(...) IMPLEMENTS_FUNC_INNER(FL_ARG_COUNT(__VA_ARGS__),__VA_ARGS__)
#define IMPLEMENTS_FUNC_INNER(COUNT,...) IMPLEMENTS_FUNC_INNER_2(COUNT,__VA_ARGS__)
#define IMPLEMENTS_FUNC_INNER_2(COUNT,...) _IMPLEMENTS_##COUNT(__VA_ARGS__)

#endif
