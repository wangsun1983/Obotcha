#ifndef __OBOTCHA_HTTP_V2_FRAME_BYTEARRAY_HPP__
#define __OBOTCHA_HTTP_V2_FRAME_BYTEARRAY_HPP__

#include "Object.hpp"
#include "ByteArray.hpp"
#include "Http2Frame.hpp"

namespace obotcha {

DECLARE_CLASS(Http2FrameByteArray) IMPLEMENTS(ByteArray){
public:
    explicit _Http2FrameByteArray(int size);
    _Http2FrameByteArray(sp<_Http2FrameByteArray>,int,int);
    void setPriorityWeight(int);
    int getPriorityWeight() const;

    void setType(st(Http2Frame)::Type);
    st(Http2Frame)::Type getType() const;
private:
    int priority;
    st(Http2Frame)::Type type;
};

}

#endif
