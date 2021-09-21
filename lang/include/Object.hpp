#ifndef __OBOTCHA_OBJECT_H__
#define __OBOTCHA_OBJECT_H__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/types.h>
#include <typeinfo>
#include <utility>

#include "Definations.hpp"
#include "Implements.hpp"
#include "StrongPointer.hpp"

#define OBJ_DEC_FREE POINTER_DEC_FREE
#define OBJ_DEC_NO_FREE POINTER_DEC_NO_FREE

namespace obotcha {

// just add class declaration for reflect
class _Field;
class _String;
class _JsonValue;

template <typename T> class _ArrayList;

template <typename T, typename U> class _KeyValuePair;

//-------------------------- Declaration ----------------------------------//
class _Object {
public:
    friend class _Field;
    friend class _JsonValue;
    _Object() : __mCount__(0) {}

    inline void incStrong(__attribute__((unused)) const void *id) {
        __sync_fetch_and_add(&__mCount__, 1);
        return;
    }

    inline int decStrong(__attribute__((unused)) const void *id) {
        if (__sync_fetch_and_sub(&__mCount__, 1) == 1) {
            return OBJ_DEC_FREE;
        }
        return OBJ_DEC_NO_FREE;
    }

    //! DEBUGGING ONLY: Get current strong ref count.
    inline int32_t getStrongCount() { return __mCount__; }

    inline virtual bool equals(const _Object *m) { return this == m; }

    inline virtual bool equals(_Object &m) { return this == &m; }

    inline virtual ~_Object() {}

    inline virtual uint64_t hashcode() { return (uint64_t)this; }

    // reflect function
    inline virtual void __ReflectInit() {}
    // must not return null!!! or build failed
    inline virtual sp<_Field> getField(sp<_String>) { throw "not support"; }
    inline virtual sp<_ArrayList<sp<_Field>>> getAllFields() {
        throw "not support";
    }
    inline virtual sp<_String> __ReflectClassName() { throw "not support"; }

    inline virtual int __getFieldIntValue(std::string) { return 0; }
    inline virtual uint8_t __getFieldByteValue(std::string) { return 0; }
    inline virtual bool __getFieldBoolValue(std::string) { return true; }
    inline virtual double __getFieldDoubleValue(std::string) { return 0.0; }
    inline virtual long __getFieldLongValue(std::string name) { return 0; }
    inline virtual float __getFieldFloatValue(std::string) { return 0.0; }
    inline virtual uint8_t __getFieldUint8Value(std::string) { return 0; }
    inline virtual uint16_t __getFieldUint16Value(std::string) { return 0; }
    inline virtual uint32_t __getFieldUint32Value(std::string) { return 0; }
    inline virtual uint64_t __getFieldUint64Value(std::string) { return 0; }
    inline virtual sp<_String> __getFieldStringValue(std::string name) {
        throw "not support";
    };
    inline virtual sp<_Object> __getFieldObjectValue(std::string) {
        return nullptr;
    }

    // reflect set function
    inline virtual void __setFieldIntValue(std::string, int) {}
    inline virtual void __setFieldByteValue(std::string, uint8_t) {}
    inline virtual void __setFieldDoubleValue(std::string, double) {}
    inline virtual void __setFieldFloatValue(std::string, float) {}
    inline virtual void __setFieldLongValue(std::string, long) {}
    inline virtual void __setFieldUint8Value(std::string, uint8_t) {}
    inline virtual void __setFieldUint16Value(std::string, uint16_t) {}
    inline virtual void __setFieldUint32Value(std::string, uint32_t) {}
    inline virtual void __setFieldUint64Value(std::string, uint64_t) {}
    inline virtual void __setFieldObjectValue(std::string, sp<_Object>) {}
    inline virtual void __setFieldStringValue(std::string name,
                                              std::string value) {}
    inline virtual void __setFieldBoolValue(std::string name, bool) {}

    // create function
    inline virtual void __createFieldObject(std::string name) {}

    // list function
    inline virtual sp<_Object> __createListItemObject(std::string name) {
        return nullptr;
    }
    inline virtual sp<_Object> __getListItemObject(std::string name,
                                                   int index) {
        return nullptr;
    }
    inline virtual void __addListItemObject(std::string name, sp<_Object>) {
        throw "not support";
    }

    // hashmap function
    inline virtual sp<_KeyValuePair<sp<_Object>, sp<_Object>>>
    __createMapItemObject(std::string name) {
        throw "not support";
    }
    inline virtual sp<_ArrayList<sp<_KeyValuePair<sp<_Object>, sp<_Object>>>>>
    __getMapItemObjects(std::string name) {
        throw "not support";
    }
    inline virtual void __addMapItemObject(std::string name, sp<_Object>,
                                           sp<_Object>) {
        throw "not support";
    }

    inline virtual int __getContainerSize(std::string name) { return 0; }

    static const int __isReflected = 0;

private:
    mutable volatile int32_t __mCount__;
};

//-------------------------- Implementation ----------------------------------//
using Object = sp<_Object>;

template <typename U> sp<U> AutoClone(U *v) {
    sp<U> data;
    data.set_pointer(v);
    return data;
}

template <typename U, int N> class AutoCreator {
public:
    U get() {
        printf("AutoCreator 2222 \n");
        return nullptr;
    }
};

template <typename U> class AutoCreator<U, 1> {
public:
    U get() {
        U v;
        __AutoCreate(v);
        return v;
    }
};

template <typename U> void __AutoCreate(sp<U> &v) {
    U *val = new U();
    val->__ReflectInit();
    v.set_pointer(val);
}

template <typename T, typename U> T AutoClone(U *v) {
    T data;
    data.set_pointer(dynamic_cast<decltype(data.get_pointer())>(v));
    return data;
}

template <typename X, typename V> X Cast(sp<V> t) {
    return AutoClone<X>(t.m_ptr);
}

} // namespace obotcha

//-------------------------- Macro for Class Declaration
//----------------------------------//
#define MAKE_FUNCTION_0(Y)                                                     \
    template <typename A = _##Y, typename... Args>                             \
    sp<A> create##Y(Args &&... args) {                                         \
        _Object *obj = new A(std::forward<Args>(args)...);                     \
        obj->__ReflectInit();                                                  \
        return AutoClone<sp<A>>(obj);                                          \
    }

#define MAKE_FUNCTION_1(Y)                                                     \
    template <typename T, typename A = _##Y<T>, typename... Args>              \
    sp<A> create##Y(Args &&... args) {                                         \
        _Object *obj = new A(std::forward<Args>(args)...);                     \
        obj->__ReflectInit();                                                  \
        return AutoClone<sp<A>>(obj);                                          \
    }

#define MAKE_FUNCTION_2(Y)                                                     \
    template <typename T, typename U, typename A = _##Y<T, U>,                 \
              typename... Args>                                                \
    sp<A> create##Y(Args &&... args) {                                         \
        _Object *obj = new A(std::forward<Args>(args)...);                     \
        obj->__ReflectInit();                                                  \
        return AutoClone<sp<A>>(obj);                                          \
    }

#define CLASS_PRE_DEF_0(YY) class _##YY
#define CLASS_PRE_DEF_1(YY) template <typename X> class _##YY
#define CLASS_PRE_DEF_2(YY) template <typename X, typename Z> class _##YY

#define TYPE_DEF_0(YY) typedef sp<_##YY> YY
#define TYPE_DEF_1(YY) template <typename UU> using YY = sp<_##YY<UU>>;

#define TYPE_DEF_2(YY)                                                         \
    template <typename UU, typename VV> using YY = sp<_##YY<UU, VV>>;

#define TEPMLATE_DECLARE_0
#define TEPMLATE_DECLARE_1 template <typename T>
#define TEPMLATE_DECLARE_2 template <typename T, typename U>

#define DECLARE_TEMPLATE_CLASS(Y, U)                                           \
    CLASS_PRE_DEF_##U(Y);                                                      \
    TYPE_DEF_##U(Y);                                                           \
    MAKE_FUNCTION_##U(Y) TEPMLATE_DECLARE_##U class _##Y                       \
        : virtual public _Object

#define DECLARE_CLASS(Y) DECLARE_TEMPLATE_CLASS(Y, 0)

//-------------------------- Macro for Static Class Declaration
//----------------------------------//
#define st(Y) _##Y

#endif
