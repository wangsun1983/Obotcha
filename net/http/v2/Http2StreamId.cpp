#include "Http2StreamId.hpp"

namespace obotcha {

_Http2StreamId::_Http2StreamId(bool isServer) {
    if(isServer) {
        id = 2;
    } else {
        id = 3;
    }
}

int _Http2StreamId::next() {
    id += 2;
    return id;
}

}
