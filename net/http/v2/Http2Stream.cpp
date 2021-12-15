#include <mutex>
#include <thread>

#include "Http2Stream.hpp"
#include "Http2HeaderFrame.hpp"
#include "Http2ContinuationFrame.hpp"

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

bool _Http2Stream::applyFrame(Http2Frame frame) {
    
    switch(frame->getType()) {
        case st(Http2Frame)::TypeData:
            return true;
        break;
        
        case st(Http2Frame)::TypeHeaders:{
            Http2HeaderFrame headerFrame = Cast<Http2HeaderFrame>(frame);
            header = headerFrame->getHeader();
            if(frame->isEndHeaders()) {
                mStatus = Open;
            }
        }
        break;

        case st(Http2Frame)::TypePriority:
            //TODO
        break;

        case st(Http2Frame)::TypeRstStream:
            //TODO
        break;

        case st(Http2Frame)::TypeSettings:
            //TODO
        break;

        case st(Http2Frame)::TypePushPromise:
            //TODO
        break;

        case st(Http2Frame)::TypePing:
            //TODO
        break;

        case st(Http2Frame)::TypeGoAway:
            //TODO
        break;

        case st(Http2Frame)::TypeWindowUpdate:
            //TODO
        break;

        case st(Http2Frame)::TypeContinuation:{
            Http2ContinuationFrame continueFrame = Cast<Http2ContinuationFrame>(frame);
            header->addHttpHeader(continueFrame->getHeaders());
        }
        break;
    }
    
    return false;
}

}
