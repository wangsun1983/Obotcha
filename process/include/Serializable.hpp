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
    ByteArray toByteArray();
    
    void import(ByteArray);

    int calculateSize();

private:

    ByteArray toByteArray(Object obj);

    void import(Object,ByteArray);
};

}
#endif
