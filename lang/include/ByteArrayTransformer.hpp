#ifndef __OBOTCHA_BYTEARRAY_TRANSFORMER_HPP__
#define __OBOTCHA_BYTEARRAY_TRANSFORMER_HPP__

#include <exception>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <regex>

#include "Object.hpp"
#include "ByteArray.hpp"
#include "TransformException.hpp"

namespace obotcha {

DECLARE_CLASS(ByteArrayTransformer) {
public:
    template <typename T>
    static ByteArray Alloc() {
        return createByteArray(sizeof(T));
    }

    template<typename T>
    static ByteArray Convert(T *data) {
        return createByteArray((byte *)data,sizeof(T),true);
    }

    template<typename T>
    static T* Convert(ByteArray data) {
        Inspect(data->size() < sizeof(T),nullptr)
        return (T*)(data->toValue());
    }

    template<typename T>
    static ByteArray Duplicate(T *data) {
        auto result = createByteArray(sizeof(T));
        memcpy(result->toValue(),data,sizeof(T)); 
        return result;
    }
};

} // namespace obotcha

#endif
