#ifndef __OBOTCHA_CONTAINER_VALUE_HPP__
#define __OBOTCHA_CONTAINER_VALUE_HPP__

#include "Object.hpp"
#include "NullPointerException.hpp"

namespace obotcha {

#define __SIMPLE_CONTAINER_VALUE(X) \
template<>\
class ContainerValue<X> {\
public:\
    template<typename U>\
    ContainerValue(U v) {\
        if(v == nullptr) {\
            Trigger(NullPointerException,"no value");\
        }\
    }\
    ContainerValue(X v) {\
        value = v;\
    }\
    X get() {\
        return value;\
    }\
private:\
    X value;\
};

template<typename T>
class ContainerValue {
public:
    ContainerValue(T v) {
        value = v;
    }

    T get() {
        return value;
    }

private:
    T value;
};

__SIMPLE_CONTAINER_VALUE(int)
__SIMPLE_CONTAINER_VALUE(uint8_t)
__SIMPLE_CONTAINER_VALUE(uint16_t)
__SIMPLE_CONTAINER_VALUE(uint32_t)
__SIMPLE_CONTAINER_VALUE(uint64_t)
__SIMPLE_CONTAINER_VALUE(bool)

}
#endif