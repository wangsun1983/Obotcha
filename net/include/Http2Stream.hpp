#ifndef __OBOTCHA_HTTP_V2_STREAM_HPP__
#define __OBOTCHA_HTTP_V2_STREAM_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

DECLARE_CLASS(Http2Stream) {
public:
    _Http2Stream(int);

    int getId();
    void setId(int);

private:
    int mId;
};

}

#endif
