#ifndef __OBOTCHA_REFLECT_METHOD_HPP__
#define __OBOTCHA_REFLECT_METHOD_HPP__

#include <string>
#include <vector>
#include <any>

#include "StrongPointer.hpp"
#include "Reflect.hpp"

namespace obotcha {

template <typename ClassType,typename ReturnType,typename... Args>
constexpr bool __is_void_function__(ReturnType (ClassType::*)(Args...)) {
    return false;
}

template <typename ClassType,typename... Args>
constexpr bool __is_void_function__(void (ClassType::*)(Args...)) {
    return true;
}

DECLARE_CLASS(MethodResult) {
public:
    template<typename T>
    _MethodResult(T v) {
        result = v;
    }

    template<typename T>
    T get() {
        return std::any_cast<T>(result);
    }

private:
    std::any result;    
};

template<typename ...Args>
class __reflect_base__:public _Object {
public:
    virtual MethodResult call() = 0;

    template<typename ...Args2>
    MethodResult execution(Args2... args) {
        params = std::make_tuple(args...);
        return call();
    }

protected:
    std::tuple<Args...> params;
};

template<typename ...Args>
MethodResult ReflectCall(void *p,Args... args) {
    auto base = (__reflect_base__<Args...> *)p;
    return base->execution(args...);
}

#define DEFINE_METHOD_MAP std::map<std::string,void *> __reflect_methods__;

#define DEFINE_GENERAL_ADD_METHOD(CLASS, METHOD)                                 \
template <typename ClassType, typename ReturnType, typename... Args>             \
void __add_method_##METHOD(ReturnType (ClassType::*)(Args...), std::string name) \
{                                                                                \
    __reflect_methods__[name] = (void *)(new reflect_##METHOD<Args...>(this));   \
}

#define DEFINE_METHOD_CLASS(CLASS, METHOD)                                              \
template <typename ClassType, typename ReturnType, typename... Args>                    \
void __delete_method_##METHOD(ReturnType (ClassType::*)(Args...))                       \
{                                                                                       \
    void *p = __reflect_methods__[#METHOD];                                             \
    reflect_##METHOD<Args...> *v = (reflect_##METHOD<Args...> *)p;                      \
    delete v;                                                                           \
}                                                                                       \
template <typename... Args>                                                             \
class reflect_##METHOD : public __reflect_base__<Args...>                               \
{                                                                                       \
public:                                                                                 \
    reflect_##METHOD(_##CLASS *p) : pthis(p)                                            \
    {                                                                                   \
    }                                                                                   \
    MethodResult call()                                                                 \
    {                                                                                   \
        auto f = [&](auto &&...args) {                                                  \
            return pthis->METHOD(args...);                                              \
        };                                                                              \
        if constexpr (!__is_void_function__(&_##CLASS::METHOD))                         \
        {                                                                               \
            return MethodResult::New(std::apply(f, __reflect_base__<Args...>::params)); \
        }                                                                               \
        if constexpr (__is_void_function__(&_##CLASS::METHOD))                          \
        {                                                                               \
            std::apply(f, __reflect_base__<Args...>::params);                           \
            return nullptr;                                                             \
        }                                                                               \
    }                                                                                   \
                                                                                        \
private:                                                                                \
    _##CLASS *pthis;                                                                    \
};

#define IMPLE_REFLECT_FUNCTION_DETECT(CLASS, COUNT, ...) \
IMPLE_REFLECT_FUNCTION_DETECT_TRACE(CLASS, COUNT, __VA_ARGS__)
#define IMPLE_REFLECT_FUNCTION_DETECT_TRACE(CLASS, COUNT, ...) \
IMPLE_REFLECT_FUNCTION_DETECT_TRACE1(CLASS, COUNT, __VA_ARGS__)
#define IMPLE_REFLECT_FUNCTION_DETECT_TRACE1(CLASS, COUNT, ...) \
IMPLE_REFLECT_FUNCTION_##COUNT(CLASS, __VA_ARGS__)

#define IMPLE_REFLECT_FUNCTION_1(CLASS, M1) \
void __init_method_field__()                \
{                                           \
    __add_method_##M1(&_##CLASS::M1, #M1);  \
}                                           \
void __release_reflect_method__()           \
{                                           \
    __delete_method_##M1(&_##CLASS::M1);    \
}                                           \
DEFINE_GENERAL_ADD_METHOD(CLASS, M1)        \
DEFINE_METHOD_CLASS(CLASS, M1)

#define IMPLE_REFLECT_FUNCTION_2(CLASS, M1, M2) \
void __init_method_field__()                    \
{                                               \
    __add_method_##M1(&_##CLASS::M1, #M1);      \
    __add_method_##M2(&_##CLASS::M2, #M2);      \
}                                               \
void __release_reflect_method__()               \
{                                               \
    __delete_method_##M1(&_##CLASS::M1);        \
    __delete_method_##M2(&_##CLASS::M2);        \
}                                               \
DEFINE_GENERAL_ADD_METHOD(CLASS, M1)            \
DEFINE_GENERAL_ADD_METHOD(CLASS, M2)            \
DEFINE_METHOD_CLASS(CLASS, M1)                  \
DEFINE_METHOD_CLASS(CLASS, M2)

#define IMPLE_REFLECT_FUNCTION_3(CLASS, M1, M2,M3) \
void __init_method_field__()                    \
{                                               \
    __add_method_##M1(&_##CLASS::M1, #M1);      \
    __add_method_##M2(&_##CLASS::M2, #M2);      \
    __add_method_##M3(&_##CLASS::M3, #M3);      \
}                                               \
void __release_reflect_method__()               \
{                                               \
    __delete_method_##M1(&_##CLASS::M1);        \
    __delete_method_##M2(&_##CLASS::M2);        \
    __delete_method_##M3(&_##CLASS::M3);        \
}                                               \
DEFINE_GENERAL_ADD_METHOD(CLASS, M1)            \
DEFINE_GENERAL_ADD_METHOD(CLASS, M2)            \
DEFINE_GENERAL_ADD_METHOD(CLASS, M3)            \
DEFINE_METHOD_CLASS(CLASS, M1)                  \
DEFINE_METHOD_CLASS(CLASS, M2)                  \
DEFINE_METHOD_CLASS(CLASS, M3)                  


#define IMPLE_REFLECT_FUNCTION_4(CLASS, M1, M2,M3,M4) \
void __init_method_field__()                    \
{                                               \
    __add_method_##M1(&_##CLASS::M1, #M1);      \
    __add_method_##M2(&_##CLASS::M2, #M2);      \
    __add_method_##M3(&_##CLASS::M3, #M3);      \
    __add_method_##M4(&_##CLASS::M4, #M4);      \
}                                               \
void __release_reflect_method__()               \
{                                               \
    __delete_method_##M1(&_##CLASS::M1);        \
    __delete_method_##M2(&_##CLASS::M2);        \
    __delete_method_##M3(&_##CLASS::M3);        \
    __delete_method_##M4(&_##CLASS::M4);        \
}                                               \
DEFINE_GENERAL_ADD_METHOD(CLASS, M1)            \
DEFINE_GENERAL_ADD_METHOD(CLASS, M2)            \
DEFINE_GENERAL_ADD_METHOD(CLASS, M3)            \
DEFINE_GENERAL_ADD_METHOD(CLASS, M4)            \
DEFINE_METHOD_CLASS(CLASS, M1)                  \
DEFINE_METHOD_CLASS(CLASS, M2)                  \
DEFINE_METHOD_CLASS(CLASS, M3)                  \
DEFINE_METHOD_CLASS(CLASS, M4)                  

#define IMPLE_REFLECT_FUNCTION_5(CLASS,M1,M2,M3,M4,M5) \
void __init_method_field__()                    \
{                                               \
    __add_method_##M1(&_##CLASS::M1, #M1);      \
    __add_method_##M2(&_##CLASS::M2, #M2);      \
    __add_method_##M3(&_##CLASS::M3, #M3);      \
    __add_method_##M4(&_##CLASS::M4, #M4);      \
    __add_method_##M5(&_##CLASS::M5, #M5);      \
}                                               \
void __release_reflect_method__()               \
{                                               \
    __delete_method_##M1(&_##CLASS::M1);        \
    __delete_method_##M2(&_##CLASS::M2);        \
    __delete_method_##M3(&_##CLASS::M3);        \
    __delete_method_##M4(&_##CLASS::M4);        \
    __delete_method_##M5(&_##CLASS::M5);        \
}                                               \
DEFINE_GENERAL_ADD_METHOD(CLASS, M1)            \
DEFINE_GENERAL_ADD_METHOD(CLASS, M2)            \
DEFINE_GENERAL_ADD_METHOD(CLASS, M3)            \
DEFINE_GENERAL_ADD_METHOD(CLASS, M4)            \
DEFINE_GENERAL_ADD_METHOD(CLASS, M5)            \
DEFINE_METHOD_CLASS(CLASS, M1)                  \
DEFINE_METHOD_CLASS(CLASS, M2)                  \
DEFINE_METHOD_CLASS(CLASS, M3)                  \
DEFINE_METHOD_CLASS(CLASS, M4)                  \
DEFINE_METHOD_CLASS(CLASS, M5)


#define IMPLE_REFLECT_FUNCTION_6(CLASS,M1,M2,M3,M4,M5,M6) \
void __init_method_field__()                    \
{                                               \
    __add_method_##M1(&_##CLASS::M1, #M1);      \
    __add_method_##M2(&_##CLASS::M2, #M2);      \
    __add_method_##M3(&_##CLASS::M3, #M3);      \
    __add_method_##M4(&_##CLASS::M4, #M4);      \
    __add_method_##M5(&_##CLASS::M5, #M5);      \
    __add_method_##M6(&_##CLASS::M6, #M6);      \
}                                               \
void __release_reflect_method__()               \
{                                               \
    __delete_method_##M1(&_##CLASS::M1);        \
    __delete_method_##M2(&_##CLASS::M2);        \
    __delete_method_##M3(&_##CLASS::M3);        \
    __delete_method_##M4(&_##CLASS::M4);        \
    __delete_method_##M5(&_##CLASS::M5);        \
    __delete_method_##M6(&_##CLASS::M6);        \
}                                               \
DEFINE_GENERAL_ADD_METHOD(CLASS, M1)            \
DEFINE_GENERAL_ADD_METHOD(CLASS, M2)            \
DEFINE_GENERAL_ADD_METHOD(CLASS, M3)            \
DEFINE_GENERAL_ADD_METHOD(CLASS, M4)            \
DEFINE_GENERAL_ADD_METHOD(CLASS, M5)            \
DEFINE_GENERAL_ADD_METHOD(CLASS, M6)            \
DEFINE_METHOD_CLASS(CLASS, M1)                  \
DEFINE_METHOD_CLASS(CLASS, M2)                  \
DEFINE_METHOD_CLASS(CLASS, M3)                  \
DEFINE_METHOD_CLASS(CLASS, M4)                  \
DEFINE_METHOD_CLASS(CLASS, M5)                  \
DEFINE_METHOD_CLASS(CLASS, M6)


#define IMPLE_REFLECT_FUNCTION_7(CLASS,M1,M2,M3,M4,M5,M6,M7) \
void __init_method_field__()                    \
{                                               \
    __add_method_##M1(&_##CLASS::M1, #M1);      \
    __add_method_##M2(&_##CLASS::M2, #M2);      \
    __add_method_##M3(&_##CLASS::M3, #M3);      \
    __add_method_##M4(&_##CLASS::M4, #M4);      \
    __add_method_##M5(&_##CLASS::M5, #M5);      \
    __add_method_##M6(&_##CLASS::M6, #M6);      \
    __add_method_##M7(&_##CLASS::M7, #M7);      \
}                                               \
void __release_reflect_method__()               \
{                                               \
    __delete_method_##M1(&_##CLASS::M1);        \
    __delete_method_##M2(&_##CLASS::M2);        \
    __delete_method_##M3(&_##CLASS::M3);        \
    __delete_method_##M4(&_##CLASS::M4);        \
    __delete_method_##M5(&_##CLASS::M5);        \
    __delete_method_##M6(&_##CLASS::M6);        \
    __delete_method_##M7(&_##CLASS::M7);        \
}                                               \
DEFINE_GENERAL_ADD_METHOD(CLASS, M1)            \
DEFINE_GENERAL_ADD_METHOD(CLASS, M2)            \
DEFINE_GENERAL_ADD_METHOD(CLASS, M3)            \
DEFINE_GENERAL_ADD_METHOD(CLASS, M4)            \
DEFINE_GENERAL_ADD_METHOD(CLASS, M5)            \
DEFINE_GENERAL_ADD_METHOD(CLASS, M6)            \
DEFINE_GENERAL_ADD_METHOD(CLASS, M7)            \
DEFINE_METHOD_CLASS(CLASS, M1)                  \
DEFINE_METHOD_CLASS(CLASS, M2)                  \
DEFINE_METHOD_CLASS(CLASS, M3)                  \
DEFINE_METHOD_CLASS(CLASS, M4)                  \
DEFINE_METHOD_CLASS(CLASS, M5)                  \
DEFINE_METHOD_CLASS(CLASS, M6)                  \
DEFINE_METHOD_CLASS(CLASS, M7)


#define IMPLE_REFLECT_FUNCTION_8(CLASS,M1,M2,M3,M4,M5,M6,M7,M8) \
void __init_method_field__()                    \
{                                               \
    __add_method_##M1(&_##CLASS::M1, #M1);      \
    __add_method_##M2(&_##CLASS::M2, #M2);      \
    __add_method_##M3(&_##CLASS::M3, #M3);      \
    __add_method_##M4(&_##CLASS::M4, #M4);      \
    __add_method_##M5(&_##CLASS::M5, #M5);      \
    __add_method_##M6(&_##CLASS::M6, #M6);      \
    __add_method_##M7(&_##CLASS::M7, #M7);      \
    __add_method_##M8(&_##CLASS::M8, #M8);      \
}                                               \
void __release_reflect_method__()               \
{                                               \
    __delete_method_##M1(&_##CLASS::M1);        \
    __delete_method_##M2(&_##CLASS::M2);        \
    __delete_method_##M3(&_##CLASS::M3);        \
    __delete_method_##M4(&_##CLASS::M4);        \
    __delete_method_##M5(&_##CLASS::M5);        \
    __delete_method_##M6(&_##CLASS::M6);        \
    __delete_method_##M7(&_##CLASS::M7);        \
    __delete_method_##M8(&_##CLASS::M8);        \
}                                               \
DEFINE_GENERAL_ADD_METHOD(CLASS, M1)            \
DEFINE_GENERAL_ADD_METHOD(CLASS, M2)            \
DEFINE_GENERAL_ADD_METHOD(CLASS, M3)            \
DEFINE_GENERAL_ADD_METHOD(CLASS, M4)            \
DEFINE_GENERAL_ADD_METHOD(CLASS, M5)            \
DEFINE_GENERAL_ADD_METHOD(CLASS, M6)            \
DEFINE_GENERAL_ADD_METHOD(CLASS, M7)            \
DEFINE_GENERAL_ADD_METHOD(CLASS, M8)            \
DEFINE_METHOD_CLASS(CLASS, M1)                  \
DEFINE_METHOD_CLASS(CLASS, M2)                  \
DEFINE_METHOD_CLASS(CLASS, M3)                  \
DEFINE_METHOD_CLASS(CLASS, M4)                  \
DEFINE_METHOD_CLASS(CLASS, M5)                  \
DEFINE_METHOD_CLASS(CLASS, M6)                  \
DEFINE_METHOD_CLASS(CLASS, M7)                  \
DEFINE_METHOD_CLASS(CLASS, M8)


#define DECLARE_REFLECT_METHOD(CLASS, ...)        \
DEFINE_METHOD_MAP                                 \
sp<_MethodField> getMethodField(std::string name) \
{                                                 \
    auto method = __reflect_methods__[name];      \
    return MethodField::New(method, this);        \
}                                                 \
IMPLE_REFLECT_FUNCTION_DETECT(CLASS, GET_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)

DECLARE_CLASS(MethodField) {
public:
    _MethodField(void *p,_Object *obj) {
        method = p;
        backup.set_pointer((_Object *)obj);
    }

    template<typename ...Args>
    MethodResult execute(Args... args) {
        return ReflectCall(method,args...);
    }

private:
    void *method;
    Object backup; //keep this instance to avoid release
};

}
#endif