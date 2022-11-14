#ifndef __OBOTCHA_HTTP_V2_PRIORITY_BYTEARRAY_HPP__
#define __OBOTCHA_HTTP_V2_PRIORITY_BYTEARRAY_HPP__

#include "Object.hpp"
#include "ByteArray.hpp"

namespace obotcha {

DECLARE_CLASS(Http2PriorityByteArray) IMPLEMENTS(ByteArray){
public:
    _Http2PriorityByteArray(int);
    void setPriorityWeight(int);
    int getPriorityWeight();

private:
    int priority;
};

}

#endif
