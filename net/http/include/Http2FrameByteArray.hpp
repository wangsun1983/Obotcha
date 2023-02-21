#ifndef __OBOTCHA_HTTP_V2_FRAME_BYTEARRAY_HPP__
#define __OBOTCHA_HTTP_V2_FRAME_BYTEARRAY_HPP__

#include "Object.hpp"
#include "ByteArray.hpp"

namespace obotcha {

DECLARE_CLASS(Http2FrameByteArray) IMPLEMENTS(ByteArray){
public:
    _Http2FrameByteArray(int size);
    _Http2FrameByteArray(sp<_Http2FrameByteArray>,int,int);
    void setPriorityWeight(int);
    int getPriorityWeight();

    void setType(int);
    int getType();
private:
    int priority;
    int type;
};

}

#endif
