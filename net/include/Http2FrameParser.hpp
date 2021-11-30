#ifndef __OBOTCHA_HTTP_V2_FRAME_PARSER_HPP__
#define __OBOTCHA_HTTP_V2_FRAME_PARSER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "Http2Frame.hpp"
#include "ByteRingArrayReader.hpp"
#include "ArrayList.hpp"

namespace obotcha {


DECLARE_CLASS(Http2FrameParser) {

public:
    _Http2FrameParser(ByteRingArrayReader);
    ArrayList<Http2Frame> doParse();

private:
    ByteRingArrayReader mReader;
    Http2Frame mFrame;

};

}

#endif
