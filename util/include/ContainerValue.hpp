#ifndef __OBOTCHA_CONTAINER_VALUE_HPP__
#define __OBOTCHA_CONTAINER_VALUE_HPP__

#include "NullPointerException.hpp"
#include "Object.hpp"

namespace obotcha {

#define __SIMPLE_CONTAINER_VALUE(X)                                            \
    template <> class ContainerValue<X> {                                      \
      public:                                                                  \
        template <typename U> ContainerValue(U v) {                            \
            Panic(v == nullptr,NullPointerException, "no value")               \
        }                                                                      \
        ContainerValue(X v) { value = v; }                                     \
        X get() { return value; }                                              \
      private:                                                                 \
        X value;                                                               \
    };

template <typename T> class ContainerValue {
  public:
    explicit ContainerValue(T v):value(v) {
        //do nothing
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
__SIMPLE_CONTAINER_VALUE(long int)
__SIMPLE_CONTAINER_VALUE(double)
__SIMPLE_CONTAINER_VALUE(float)

} // namespace obotcha
#endif