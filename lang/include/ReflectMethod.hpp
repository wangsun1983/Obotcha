#ifndef __OBOTCHA_REFLECT_METHOD_HPP__
#define __OBOTCHA_REFLECT_METHOD_HPP__

#include <string>
#include <vector>

#include "StrongPointer.hpp"
#include "Reflect.hpp"

namespace obotcha {

DECLARE_CLASS(MethodResult) {
public:
    void set(int value) {
        intValue = value;
    }
    
    void set(double value) {
        doubleValue = value;
    }

    void set(bool value) {
        boolValue = value;
    }

    void set(float value) {
        floatValue = value;
    }

    void set(long value) {
        longValue = value;
    }

    void set(uint8_t value) {
        uint8Value = value;
    }

    void set(uint16_t value) {
        uint16Value = value;
    }
    
    void set(uint32_t value) {
        uint16Value = value;
    }

    void set(uint64_t value) {
        uint16Value = value;
    }

    void set(void* value) {
        pointerValue = value;
    }

    template<typename T>
    void set(T v) {
        objValue = v;
    }

    template<typename T>
    T get() {
        return Cast<T>(objValue);
    }

    int getIntValue() {
        return intValue;
    }

    double getDoubleValue() {
        return doubleValue;
    }

    bool getBoolValue() {
        return boolValue;
    }

    float getFloatValue() {
        return floatValue;
    }

    long getLongValue() {
        return longValue;
    }

    uint8_t getUint8Value() {
        return uint8Value;
    }

    uint16_t getUint16Value() {
        return uint16Value;
    }

    uint32_t getUint32Value() {
        return uint32Value;
    }

    uint64_t getUint64Value() {
        return uint64Value;
    }

    void *getVoidPointer() {
        return pointerValue;
    }

private:
    int intValue;
    double doubleValue;
    bool boolValue;
    float floatValue;
    long longValue;
    uint8_t uint8Value;
    uint16_t uint16Value;
    uint32_t uint32Value;
    uint64_t uint64Value;
    void *pointerValue;
    Object objValue;
};


template<typename ...Args>
class __reflect_base__ {
public:
    virtual void call() = 0;

    template<typename ...Args2>
    void execution(Args2... args) {
        printf("start execute!!!! \n");
        params = std::make_tuple(args...);
        call();
    }

protected:
    std::tuple<Args...> params;
};

template<typename ...Args>
void ReflectCall(void *p,Args... args) {
    auto base = (__reflect_base__<Args...> *)p;
    base->execution(args...);
}

#define DEFINE_METHOD_MAP std::map<std::string,void *> __reflect_methods__;

#define DEFINE_GENERAL_ADD_METHOD(CLASS,METHOD) \
    template <typename ClassType,typename ReturnType,typename... Args>\
    void __add_method_##METHOD(ReturnType (ClassType::*)(Args...),std::string name) {\
        __reflect_methods__[name] = (void *)(new reflect_##METHOD<Args...>(this));\
    }

#define DEFINE_METHOD_CLASS(CLASS,METHOD) \
    template <typename ClassType,typename ReturnType,typename... Args> \
    void __delete_method_##METHOD(ReturnType (ClassType::*)(Args...)) {\
        void *p = __reflect_methods__[#METHOD];\
        reflect_##METHOD<Args...> *v = (reflect_##METHOD<Args...> *)p;\
        delete v;\
    }\
    template<typename... Args>\
    class reflect_##METHOD:public __reflect_base__<Args...> {\
    public:\
        reflect_##METHOD(_##CLASS *p):pthis(p) {\
        }\
        void call() {\
            auto f = [&](auto &&...args) {\
                return pthis->METHOD(args...);\
            };\
            std::apply(f,__reflect_base__<Args...>::params);\
        }\
    private:\
        _##CLASS *pthis;\
    };


#define IMPLE_REFLECT_FUNCTION_DETECT(CLASS, COUNT, ...) \
IMPLE_REFLECT_FUNCTION_DETECT_TRACE(CLASS, COUNT, __VA_ARGS__)
#define IMPLE_REFLECT_FUNCTION_DETECT_TRACE(CLASS, COUNT, ...) \
IMPLE_REFLECT_FUNCTION_DETECT_TRACE1(CLASS, COUNT, __VA_ARGS__)
#define IMPLE_REFLECT_FUNCTION_DETECT_TRACE1(CLASS, COUNT, ...) \
IMPLE_REFLECT_FUNCTION_##COUNT(CLASS, __VA_ARGS__)

#define IMPLE_REFLECT_FUNCTION_1(CLASS, M1)                    \
void __init_method_field__()                                   \
{                                                              \
   __add_method_##M1(&_##CLASS::M1,#M1);                       \
}                                                              \
void __release_reflect_method__()                              \
{                                                              \
    __delete_method_##M1(&_##CLASS::M1);                       \
}                                                              \
DEFINE_GENERAL_ADD_METHOD(CLASS,M1)                            \
DEFINE_METHOD_CLASS(CLASS, M1)


#define IMPLE_REFLECT_FUNCTION_2(CLASS, M1,M2)                 \
void __init_method_field__()                                   \
{                                                              \
   __add_method_##M1(&_##CLASS::M1,#M1);                       \
   __add_method_##M2(&_##CLASS::M2,#M2);                       \
}                                                              \
void __release_reflect_method__()                              \
{                                                              \
    __delete_method_##M1(&_##CLASS::M1);                       \
    __delete_method_##M2(&_##CLASS::M2);                       \
}                                                              \
DEFINE_GENERAL_ADD_METHOD(CLASS,M1)                            \
DEFINE_GENERAL_ADD_METHOD(CLASS,M2)                            \
DEFINE_METHOD_CLASS(CLASS, M1)                                 \
DEFINE_METHOD_CLASS(CLASS, M2)                                 





#define DECLARE_REFLECT_METHOD(CLASS, ...)                \
DEFINE_METHOD_MAP                                         \
sp<_MethodField> getMethodField(std::string name)         \
{                                                         \
    auto method = __reflect_methods__[name];              \
    return MethodField::New(method);                      \
}                                                         \
IMPLE_REFLECT_FUNCTION_DETECT(CLASS, GET_ARG_COUNT(__VA_ARGS__), __VA_ARGS__)


DECLARE_CLASS(MethodField) {
public:
    _MethodField(void *p) {
        method = p;
    }

    template<typename ...Args>
    MethodResult execute(Args... args) {
        ReflectCall(method,args...);
        return nullptr;
    }
private:
    void *method;
};

}
#endif