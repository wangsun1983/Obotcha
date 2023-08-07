#ifndef __OBOTCHA_OBJECT_H__
#define __OBOTCHA_OBJECT_H__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/types.h>
#include <typeinfo>
#include <utility>
#include <thread>
#include <atomic>

#include "Implements.hpp"
#include "StrongPointer.hpp"
#include "OStdNew.hpp"
#include "MethodNotSupportException.hpp"

#define OBJ_DEC_FREE POINTER_DEC_FREE
#define OBJ_DEC_NO_FREE POINTER_DEC_NO_FREE

namespace obotcha {

// just add class declaration for reflect
class _Field;
class _String;
class _JsonValue;

template <typename T> class _ArrayList;

template <typename T, typename U> class _Pair;

//-------------------------- Declaration ----------------------------------//
class _Object {
public:
    friend class _Field;
    friend class _JsonValue;
    _Object() = default;

    inline void incStrong(__attribute__((unused)) const void *id) {
        __mCount__.fetch_add(1, std::memory_order_relaxed);        
    }

    inline void decStrong(__attribute__((unused)) const void *id) {
        const int32_t c = __mCount__.fetch_sub(1, std::memory_order_release);
        if (c == 1) {
            std::atomic_thread_fence(std::memory_order_acquire);
            delete this;
        }
    }

    //! DEBUGGING ONLY: Get current strong ref count.
    inline int32_t getStrongCount() const { 
        return __mCount__;
    }

    inline virtual bool equals(sp<_Object> m) { 
        return this == m.get_pointer(); 
    }

    inline virtual ~_Object() = default;

    inline virtual uint64_t hashcode() const { 
        return (uint64_t)this; 
    }

    // reflect function
    inline virtual void __ReflectInit() {
        // Intentionally unimplemented...
    }

    // must not return null!!! or build failed
    inline virtual sp<_Field> getField(sp<_String>) { 
        throw MethodNotSupportException();
    }

    inline virtual sp<_ArrayList<sp<_Field>>> getAllFields() {
        throw MethodNotSupportException();
    }
    
    inline virtual sp<_String> __ReflectClassName() { 
        throw MethodNotSupportException(); 
    }

    inline virtual int __getFieldIntValue(const std::string &) { 
        return 0; 
    }

    inline virtual uint8_t __getFieldByteValue(const std::string &) { 
        return 0; 
    }

    inline virtual bool __getFieldBoolValue(const std::string &) { 
        return true; 
    }

    inline virtual double __getFieldDoubleValue(const std::string &) { 
        return 0.0; 
    }

    inline virtual long __getFieldLongValue(const std::string &) { 
        return 0;
    }

    inline virtual float __getFieldFloatValue(const std::string &) { 
        return 0.0;
    }

    inline virtual uint8_t __getFieldUint8Value(const std::string &) { 
        return 0; 
    }

    inline virtual uint16_t __getFieldUint16Value(const std::string &) { 
        return 0;
    }

    inline virtual uint32_t __getFieldUint32Value(const std::string &) { 
        return 0; 
    }

    inline virtual uint64_t __getFieldUint64Value(const std::string &) { 
        return 0;
    }

    inline virtual sp<_String> __getFieldStringValue(const std::string &) {
        throw MethodNotSupportException();
    };

    inline virtual sp<_Object> __getFieldObjectValue(const std::string &) {
        return nullptr;
    }

    // reflect set function
    inline virtual void __setFieldIntValue(const std::string &, int) {
        // Intentionally unimplemented...
    }

    inline virtual void __setFieldByteValue(const std::string &, uint8_t) {
        // Intentionally unimplemented...
    }

    inline virtual void __setFieldDoubleValue(const std::string &, double) {
        // Intentionally unimplemented...
    }

    inline virtual void __setFieldFloatValue(const std::string &, float) {
        // Intentionally unimplemented...
    }

    inline virtual void __setFieldLongValue(const std::string &, long) {
        // Intentionally unimplemented...
    }

    inline virtual void __setFieldUint8Value(const std::string &, uint8_t) {
        // Intentionally unimplemented...
    }

    inline virtual void __setFieldUint16Value(const std::string &, uint16_t) {
        // Intentionally unimplemented...
    }

    inline virtual void __setFieldUint32Value(const std::string &, uint32_t) {
        // Intentionally unimplemented...
    }

    inline virtual void __setFieldUint64Value(const std::string &, uint64_t) {
        // Intentionally unimplemented...
    }

    inline virtual void __setFieldObjectValue(const std::string &, sp<_Object>) {
        // Intentionally unimplemented...
    }

    inline virtual void __setFieldStringValue(const std::string &name,
                                              const std::string value) {
        // Intentionally unimplemented...
    }

    inline virtual void __setFieldBoolValue(const std::string &name, bool) {
        // Intentionally unimplemented...
    }

    // create function
    inline virtual void __createFieldObject(const std::string &name) {
        // Intentionally unimplemented...
    }

    // list function
    inline virtual sp<_Object> __createListItemObject(const std::string &name) {
        return nullptr;
    }
    inline virtual sp<_Object> __getListItemObject(const std::string &name,
                                                   int index) {
        return nullptr;
    }

    inline virtual void __addListItemObject(const std::string &name, sp<_Object>) {
        throw MethodNotSupportException();
    }

    virtual sp<_String> toString();

    // hashmap function
    inline virtual sp<_Pair<sp<_Object>, sp<_Object>>>
    __createMapItemObject(const std::string &name) {
        throw MethodNotSupportException();
    }

    inline virtual sp<_ArrayList<sp<_Pair<sp<_Object>, sp<_Object>>>>>
    __getMapItemObjects(const std::string &name) {
        throw MethodNotSupportException();
    }
    inline virtual void __addMapItemObject(const std::string &name, sp<_Object>,
                                           sp<_Object>) {
        throw MethodNotSupportException();
    }

    inline virtual int __getContainerSize(const std::string &name) { 
        return 0; 
    }

    static const int __isReflected = 0;

private:
    std::atomic<int32_t>  __mCount__ = 0;
};

//-------------------------- Implementation ----------------------------------//
using Object = sp<_Object>;

template <typename U> sp<U> AutoClone(U *v) {
    sp<U> data;
    data.set_pointer(v);
    return data;
}

template <typename T> T AutoCreate() {
    T data;
    __AutoCreate(data);
    return data;
}

template <typename U, int N> class AutoCreator {
public:
    U get() {
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

#define ARG_0(N, ...) N

#define ARG_1(_1, N, ...) N

#define ARG_2(_1, _2, N, ...) N

#define ARG_3(_1, _2, _3, N, ...) N

#define ARG_4(_1, _2, _3, _4, N, ...) N

#define ARG_5(_1, _2, _3, _4, _5, N, ...) N

#define ARG_6(_1, _2, _3, _4, _5, _6, N, ...) N

#define ARG_7(_1, _2, _3, _4, _5, _6, _7, N, ...) N

#define ARG_8(_1, _2, _3, _4, _5, _6, _7, _8, N, ...) N

#define ARG_9(_1, _2, _3, _4, _5, _6, _7, _8, _9, N, ...) N

#define ARG_10(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, N, ...) N

#define ARG_11(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, N, ...) N

#define ARG_12(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, N, ...) N

#define ARG_13(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, N, ...) N

#define ARG_14(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, N, \
               ...)                                                            \
    N

#define ARG_15(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14,    \
               _15, N, ...)                                                    \
    N

#define RSEQ_N()                                                               \
    119, 118, 117, 116, 115, 114, 113, 112, 111, 110, 109, 108, 107, 106, 105, \
        104, 103, 102, 101, 100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89,   \
        88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72,    \
        71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55,    \
        54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38,    \
        37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21,    \
        20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, \
        0

#define ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14,     \
              _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, \
              _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, \
              _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, \
              _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, \
              _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, _77, _78, _79, \
              _80, _81, _82, _83, _84, _85, _86, _87, _88, _89, _90, _91, _92, \
              _93, _94, _95, _96, _97, _98, _99, _100, _101, _102, _103, _104, \
              _105, _106, _107, _108, _109, _110, _111, _112, _113, _114,      \
              _115, _116, _117, _118, _119, N, ...)                            \
    N

#define MARCO_EXPAND(...) __VA_ARGS__
#define GET_ARG_COUNT_INNER(...) MARCO_EXPAND(ARG_N(__VA_ARGS__))
#define GET_ARG_COUNT(...) GET_ARG_COUNT_INNER(__VA_ARGS__, RSEQ_N())

#define CLASS_PRE_DEF_0(YY) class _##YY

#define CLASS_PRE_DEF_1(classname,templatename)  template <typename templatename> class _##classname

#define CLASS_PRE_DEF_2(classname,templatename1,templatename2)  template <typename templatename1,typename templatename2> class _##classname

#define CLASS_PRE_DEF_3(classname,templatename1,templatename2,templatename3)  template <typename templatename1,typename templatename2,typename templatename3> class _##classname


#define TYPE_DEF_1(classname,templatename) \
    template <typename templatename> using classname = sp<_##classname<templatename>>;

#define TYPE_DEF_2(classname,templatename1,templatename2) \
    template <typename templatename1, typename templatename2> using classname = sp<_##classname<templatename1,templatename2>>;

#define TYPE_DEF_3(classname,templatename1,templatename2,templatename3) \
    template <typename templatename1, typename templatename2,typename templatename3> using classname = sp<_##classname<templatename1,templatename2,templatename3>>;


#define MAKE_FUNCTION_1(classname,templatename1)                                                     \
    template <typename templatename1, typename A = _##classname<templatename1>, typename... Args>              \
    sp<A> create##classname(Args &&... args) {                                         \
        _Object *obj = new A(std::forward<Args>(args)...);                     \
        obj->__ReflectInit();                                                  \
        return AutoClone<sp<A>>(obj);                                          \
    }

#define MAKE_FUNCTION_2(classname,templatename1,templatename2)                                                     \
    template <typename templatename1, typename templatename2, typename A = _##classname<templatename1,templatename2>,                 \
              typename... Args>                                                \
    sp<A> create##classname(Args &&... args) {                                         \
        _Object *obj = new A(std::forward<Args>(args)...);                     \
        obj->__ReflectInit();                                                  \
        return AutoClone<sp<A>>(obj);                                          \
    }

#define MAKE_FUNCTION_3(classname,templatename1,templatename2,templatename3)                                                     \
    template <typename templatename1, typename templatename2, typename typenamename3,typename A = _##classname<templatename1,templatename2,typenamename3>,                 \
              typename... Args>                                                \
    sp<A> create##classname(Args &&... args) {                                         \
        _Object *obj = new A(std::forward<Args>(args)...);                     \
        obj->__ReflectInit();                                                  \
        return AutoClone<sp<A>>(obj);                                          \
    }

#define TEMPLATE_DECLARE_1(templatename) template <typename templatename>

#define TEMPLATE_DECLARE_2(templatename1,templatename2) template <typename templatename1,typename templatename2>

#define TEMPLATE_DECLARE_3(templatename1,templatename2,templatename3) template <typename templatename1,typename templatename2,typename templatename3>

#define CLASS_PRE_DEF_FUNC_INTERFACE(Y,COUNT,...) CLASS_PRE_DEF_FUNC(Y,COUNT,__VA_ARGS__)

#define CLASS_PRE_DEF_FUNC(Y,COUNT,...) \
    CLASS_PRE_DEF_##COUNT(Y,__VA_ARGS__); \
    TYPE_DEF_##COUNT(Y,__VA_ARGS__);  \
    MAKE_FUNCTION_##COUNT(Y,__VA_ARGS__); \
    TEMPLATE_DECLARE_##COUNT(__VA_ARGS__) class _##Y: virtual public _Object


#define DECLARE_TEMPLATE_CLASS(Y, ...)                                         \
    CLASS_PRE_DEF_FUNC_INTERFACE(Y,GET_ARG_COUNT(__VA_ARGS__),__VA_ARGS__)

#define DECLARE_CLASS(Y) class _##Y; \
    typedef sp<_##Y> Y; \
    MAKE_FUNCTION_0(Y); \
    class _##Y:virtual public _Object

//-------------------------- Macro for Static Class Declaration
//----------------------------------//
#define st(Y) _##Y

#endif
