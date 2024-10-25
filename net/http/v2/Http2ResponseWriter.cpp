#include "Http2ResponseWriter.hpp"

namespace obotcha {

_Http2ResponseWriter::_Http2ResponseWriter(Http2Stream s):stream(s) {
}

long _Http2ResponseWriter::write(HttpPacket p) {
    return stream->write(p);
}

ByteArray _Http2ResponseWriter::data(HttpPacket) {
    return nullptr;
}

}
