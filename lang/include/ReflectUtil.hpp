#ifndef __OBOTCHA_REFLECT_UTIL_HPP__
#define __OBOTCHA_REFLECT_UTIL_HPP__

#include "StrongPointer.hpp"
#include "Object.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(ReflectUtil) {
public:
    template <typename T>
    static void createObject(sp<T> & value)
    {
        T *data = new T();
        data->__ReflectInit();
        value.set_pointer(data);
    }

    template<typename T>
    static void createObject(T){}

};

}
#endif

