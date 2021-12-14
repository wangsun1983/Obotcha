#include <mutex>
#include <thread>

#include "Http2Stream.hpp"

namespace obotcha {

_Http2Stream::_Http2Stream(HPackEncoder e,HPackDecoder d,int id):_Http2Stream(e,d,(id%2) == 0) {
    mStreamId = id;
}

_Http2Stream::_Http2Stream(HPackEncoder e,HPackDecoder d,bool isServer) {
    static std::once_flag flag;
    std::call_once(flag, [&]() {
        mServerStreamId = 2;
        mClientStreamId = 3;
    });

    if(isServer) {
        mStreamId = mServerStreamId++;
    } else {
        mStreamId = mClientStreamId++;
    }

    encoder = e;
    decoder = d;
    
    mStatus = Idle;
}

int _Http2Stream::getStreamId() {
    return mStreamId;
}

void _Http2Stream::setStreamId(int id) {
    mStreamId = id;
}


}
