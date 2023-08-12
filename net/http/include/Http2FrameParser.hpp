#ifndef __OBOTCHA_HTTP_V2_FRAME_PARSER_HPP__
#define __OBOTCHA_HTTP_V2_FRAME_PARSER_HPP__

#include "Object.hpp"
#include "Http2Frame.hpp"
#include "ByteRingArrayReader.hpp"
#include "ArrayList.hpp"
#include "ByteArray.hpp"
#include "HPackDecoder.hpp"

namespace obotcha {


DECLARE_CLASS(Http2FrameParser) {

public:
    _Http2FrameParser(ByteRingArrayReader,HPackDecoder);
    ArrayList<Http2Frame> doParse();

private:
    enum class Status {
        //first 9 byte(length[24 bit] + type[8 bit] + flag[8 bit] + streamId[32 bit])
        ParseHeadPart,
        ParsePayload,
    };
    ByteRingArrayReader mReader;
    Status status = Status::ParseHeadPart;
    int rest;

    Http2Frame mCurrentFrame = nullptr;
    ByteArray mCache = nullptr;
    HPackDecoder decoder;
};

}

#endif
