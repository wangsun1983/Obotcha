#include "Http2Stream.hpp"

namespace obotcha {

_Http2Stream::_Http2Stream(int id) {
    mId = id;
}

int _Http2Stream::getId() {
    return mId;
}

void _Http2Stream::setId(int id) {
    mId = id;
}

}
