#ifndef __OBOTCHA_ORPC_SERIALIZABLE_H__
#define __OBOTCHA_ORPC_SERIALIZABLE_H__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "JsonValue.hpp"
#include "JsonReader.hpp"
#include "String.hpp"
#include "Reflect.hpp"

namespace obotcha {

DECLARE_CLASS(OrpcSerializable) {

public:
    ByteArray toByteArray();
    
    void import(ByteArray);

private:
    int caculateSize();
};

}
#endif
