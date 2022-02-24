#ifndef __OBOTCHA_SERIALIZABLE_H__
#define __OBOTCHA_SERIALIZABLE_H__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "JsonValue.hpp"
#include "JsonReader.hpp"
#include "String.hpp"
#include "Reflect.hpp"

namespace obotcha {

DECLARE_CLASS(Serializable) {

public:
    ByteArray serialize();
    
    void deserialize(ByteArray);

    int calculateSize();

private:

    ByteArray serialize(Object obj);

    void deserialize(Object,ByteArray);
};

}
#endif
