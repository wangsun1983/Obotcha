#ifndef __OBOTCHA_SERIALIZABLE_H__
#define __OBOTCHA_SERIALIZABLE_H__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "JsonValue.hpp"
#include "JsonReader.hpp"
#include "String.hpp"
#include "Reflect.hpp"

namespace obotcha {

/**
 * 
 * [|size|data1,size|data2,size|data3 ...]
 * 
 */
DECLARE_CLASS(Serializable) {

public:
    ByteArray serialize();
    
    void deserialize(ByteArray);

private:

    ByteArray serialize(Object obj);

    void deserialize(Object,ByteArray);
};

#define Serialize(X) X->serialize()

template <typename T>
T DeSerialize(ByteArray data) {
    T t = AutoCreate<T>();
    t->deserialize(data);
    return t;
}

}
#endif
