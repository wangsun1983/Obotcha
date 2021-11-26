#include "Http2ShakeHandFrameParser.hpp"

namespace obotcha {

_Http2ShakeHandFrameParser::_Http2ShakeHandFrameParser(ByteRingArray data) {
    v1Parser = createHttpPacketParserImpl(data);
}

ArrayList<HttpPacket> _Http2ShakeHandFrameParser::doParser() {
    return v1Parser->doParse();
}

}
