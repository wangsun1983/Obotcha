#ifndef __OBOTCHA_BYTEARRAY_TRANSFORMER_HPP__
#define __OBOTCHA_BYTEARRAY_TRANSFORMER_HPP__

#include <string>

#include "Object.hpp"
#include "ByteArray.hpp"
#include "TransformException.hpp"

namespace obotcha {

DECLARE_CLASS(ByteArrayTransformer) {
public:
    template <typename T>
    static ByteArray Alloc() {
        return ByteArray::New(sizeof(T));
    }

    template<typename T>
    static ByteArray Convert(T *data) {
        return ByteArray::New((byte *)data,sizeof(T),true);
    }

    template<typename T>
    static T* Convert(ByteArray data) {
        Inspect(data->size() < sizeof(T),nullptr)
        return (T*)(data->toValue());
    }

    template<typename T>
    static ByteArray Duplicate(T *data) {
        auto result = ByteArray::New(sizeof(T));
        memcpy(result->toValue(),data,sizeof(T)); 
        return result;
    }
};

} // namespace obotcha

#endif
