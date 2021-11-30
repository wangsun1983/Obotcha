#include "Http2FrameParser.hpp"

namespace obotcha {


_Http2FrameParser::_Http2FrameParser(ByteRingArrayReader r) {
    mReader = r;
}

ArrayList<Http2Frame> _Http2FrameParser::doParse() {
    ArrayList<Http2Frame> list = createArrayList<Http2Frame>();

    while(mReader->getReadableLength() > 9) {
        
    }

    return nullptr;
}


}
