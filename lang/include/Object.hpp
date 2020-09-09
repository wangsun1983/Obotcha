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

class _Field;
class _String;

class Object
{
public:
    friend class _Field;
    Object() : mCount(0) { }

    inline void incStrong(__attribute__((unused)) const void* id) {
        __sync_fetch_and_add(&mCount, 1);
        return;
    }

    inline int decStrong(__attribute__((unused)) const void* id) {
        if (__sync_fetch_and_sub(&mCount, 1) == 1) {
            //delete static_cast<const T*>(this);
            return OBJ_DEC_FREE;
        }
        return OBJ_DEC_NO_FREE;
    }

    //! DEBUGGING ONLY: Get current strong ref count.
    inline int32_t getStrongCount() {
        return mCount;
    }

    inline virtual bool equals(const Object *m) {
        return this == m;
    }

    inline virtual bool equals(Object &m) {
        return this == &m;
    }

    inline virtual ~Object() {
    }

    //reflect function
    inline virtual void __ReflectInit(){}
    inline virtual sp<_Field> getField(sp<_String>){}

    //reflect get function
protected:
    inline virtual int getFieldIntValue(std::string){return 0;}
    inline virtual unsigned char getFieldByteValue(std::string){return 0;}
    inline virtual bool getFieldBoolValue(std::string){return true;}
    inline virtual double getFieldDoubleValue(std::string){return 0;}
    inline virtual long getFieldLongValue(std::string name){return 0;}
    inline virtual float getFieldFloatValue(std::string){return 0;}
    inline virtual uint8_t getFieldUint8Value(std::string){return 0;}
    inline virtual uint16_t getFieldUint16Value(std::string){return 0;}
    inline virtual uint32_t getFieldUint32Value(std::string){return 0;}
    inline virtual uint64_t getFieldUint64Value(std::string){return 0;}
    inline virtual sp<Object> getFieldObjectValue(std::string){return nullptr;}
    //reflect set function
    inline virtual void setFieldIntValue(std::string,int){}
    inline virtual void setFieldByteValue(std::string,unsigned char){}
    inline virtual void setFieldDoubleValue(std::string,double){}
    inline virtual void setFieldFloatValue(std::string,float){}
    inline virtual void setFieldLongValue(std::string,long){}
    inline virtual void setFieldUint8Value(std::string,uint8_t){}
    inline virtual void setFieldUint16Value(std::string,uint16_t){}
    inline virtual void setFieldUint32Value(std::string,uint32_t){}
    inline virtual void setFieldUint64Value(std::string,uint64_t){}
    inline virtual void setFieldObjectValue(std::string,sp<Object>){}
    inline virtual void setFieldStringValue(std::string name,std::string value){}
    inline virtual void setFieldBoolValue(std::string name,bool){}
    
    //create function
    inline virtual void createFieldObject(std::string name){}
    inline virtual sp<Object> createListItemObject(std::string name){return nullptr;}

private:
    mutable volatile int32_t mCount;
};

}

//    sp<_##Y> ret = new _##Y(std::forward<Args>(args)...);\
    ret->__ReflectInit();\

#define MAKE_FUNCTION_0(Y) \
template<typename... Args>\
sp<_##Y> create##Y(Args&&... args)\
{\
    Object* obj = new _##Y(std::forward<Args>(args)...);\
    obj->__ReflectInit();\
    sp<_##Y> ret;\
    ret.set_pointer(dynamic_cast<_##Y *>(obj));\
    return ret;\
}\

//    sp<_##Y<T>> ret = new _##Y<T>(std::forward<Args>(args)...);\
    ret->__ReflectInit();\

#define MAKE_FUNCTION_1(Y) \
template<typename T,typename... Args>\
sp<_##Y<T>> create##Y(Args&&... args)\
{\
    Object* obj = new _##Y<T>(std::forward<Args>(args)...);\
    obj->__ReflectInit();\
    sp<_##Y<T>> ret;\
    ret.set_pointer(dynamic_cast<_##Y<T> *>(obj));\
    return ret;\
}\

// sp<_##Y<T,U>> ret = new _##Y<T,U>(std::forward<Args>(args)...);\
    ret->__ReflectInit();\

#define MAKE_FUNCTION_2(Y) \
template<typename T,typename U,typename... Args>\
sp<_##Y<T,U>> create##Y(Args&&... args)\
{\
    Object* obj = new _##Y<T,U>(std::forward<Args>(args)...);\
    obj->__ReflectInit();\
    sp<_##Y<T,U>> ret;\
    ret.set_pointer(dynamic_cast<_##Y<T,U> *>(obj));\
    return ret;\
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
class _##Y: virtual public Object\

#define DECLARE_SIMPLE_CLASS(Y) DECLARE_CLASS(Y,0)

#define CONSTRUCT(X) _##X

#define DESTRUCT(X) ~_##X

#define EXTENDS(X) ,virtual public _##X

#define IMPLEMENTS(X) ,virtual public _##X

#define CLASS(X) _##X

#define CONSTRUCT_IMPLEMENT(X) CLASS(##X)::CONSTRUCT(##X)

#define DESTRUCT_IMPLEMENT(X) CLASS(##X)::DESTRUCT(##X)

#define st(Y) _##Y

#define InstanceOf(X,Y) typeid(*X.get_pointer()) == typeid(_##Y)


#endif
