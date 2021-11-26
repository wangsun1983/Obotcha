#include "Http2FrameTypes.hpp"

namespace obotcha {

const int _Http2FrameTypes::DATA = 0x0;
const int _Http2FrameTypes::HEADERS = 0x1;
const int _Http2FrameTypes::PRIORITY = 0x2;
const int _Http2FrameTypes::RST_STREAM = 0x3;
const int _Http2FrameTypes::SETTINGS = 0x4;
const int _Http2FrameTypes::PUSH_PROMISE = 0x5;
const int _Http2FrameTypes::PING = 0x6;
const int _Http2FrameTypes::GO_AWAY = 0x7;
const int _Http2FrameTypes::WINDOW_UPDATE = 0x8;
const int _Http2FrameTypes::CONTINUATION = 0x9;

}

