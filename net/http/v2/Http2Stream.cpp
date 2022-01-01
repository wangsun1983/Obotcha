#include <mutex>
#include <thread>

#include "Http2Stream.hpp"
#include "Http2HeaderFrame.hpp"
#include "Http2ContinuationFrame.hpp"
#include "Http2PushPromiseFrame.hpp"
#include "HttpPacketParserImpl.hpp"
#include "Http2DataFrame.hpp"
#include "Http2Packet.hpp"
#include "Log.hpp"

namespace obotcha {

//Http2StreamState
_Http2StreamState::_Http2StreamState(_Http2Stream * p) {
    stream = p;
}

//------------------ state:Idle -------------------------
_Http2StreamIdle::_Http2StreamIdle(_Http2Stream *p):_Http2StreamState(p) {
    mState = st(Http2Stream)::Idle;
}

Http2Packet _Http2StreamIdle::onReceived(Http2Frame frame) {
    int type = frame->getType();
    switch(type) {
        case st(Http2Frame)::TypeHeaders:{
            Http2HeaderFrame headerFrame = Cast<Http2HeaderFrame>(frame);
            stream->header = headerFrame->getHeader();
            stream->moveTo(stream->OpenState);
            if(headerFrame->isEndStream()) {
                return createHttp2Packet(headerFrame->getStreamId(),stream->header,nullptr);
            }
        }
        break;

        case st(Http2Frame)::TypePushPromise: {
            Http2PushPromiseFrame pushpromiseFrame = Cast<Http2PushPromiseFrame>(frame);
            stream->header = pushpromiseFrame->getHttpHeaders();
            stream->moveTo(stream->ReservedRemoteState);
        }
        break;

        case st(Http2Frame)::TypeSettings: {
            //TODO
        }
        break;

        default:
            LOG(ERROR)<<"Http2Stream Receive Illegal Frame,Current :Idle , FrameType :"<<type;
        break;
    }

    return nullptr;
}

bool _Http2StreamIdle::onSend(Http2Frame frame) {
    int type = frame->getType();
    printf("http2streamidle onSend \n");
    switch(type) {
        case st(Http2Frame)::TypeHeaders:{
            stream->out->write(frame->toFrameData());
            stream->moveTo(stream->OpenState);
            return true;
        }
        break;

        case st(Http2Frame)::TypePushPromise:{
            stream->out->write(frame->toFrameData());
            stream->moveTo(stream->ReservedLocalState);
            return true;
        }
        break;

        default:
            LOG(ERROR)<<"Http2Stream Send Illegal Frame,Current :Idle , FrameType :"<<type;
        break;
    }

    return false;
}

//------------------ state:ReservedLocal -------------------------
_Http2StreamReservedLocal::_Http2StreamReservedLocal(_Http2Stream *p):_Http2StreamState(p) {
    mState = st(Http2Stream)::ReservedLocal;
}

Http2Packet _Http2StreamReservedLocal::onReceived(Http2Frame frame) {
    int type = frame->getType();
    switch(frame->getType()) {
        case st(Http2Frame)::TypeRstStream:{
            stream->moveTo(stream->ClosedState);
            break;
        }

        default:
            LOG(ERROR)<<"Http2Stream Receive Illegal Frame,Current :ReservedLocal , FrameType :"<<type;
        break;
    }
    return nullptr;
}

bool _Http2StreamReservedLocal::onSend(Http2Frame frame) {
    int type = frame->getType();
    switch(frame->getType()) {
        case st(Http2Frame)::TypeHeaders: {
            stream->moveTo(stream->HalfClosedRemoteState);
            return true;
        }
        break;

        case st(Http2Frame)::TypeRstStream: {
            stream->moveTo(stream->ClosedState);
            return true;
        }

        default:
            LOG(ERROR)<<"Http2Stream Send Illegal Frame,Current :ReservedLocal , FrameType :"<<type;
        break;
    }

    return false;
}

//------------------ state:ReservedRemote -------------------------
_Http2StreamReservedRemote::_Http2StreamReservedRemote(_Http2Stream *p):_Http2StreamState(p) {
    mState = st(Http2Stream)::ReservedRemote;
}

Http2Packet _Http2StreamReservedRemote::onReceived(Http2Frame frame) {
    int type = frame->getType();
    switch(type) {
        case st(Http2Frame)::TypeHeaders: {
            Http2HeaderFrame headerFrame = Cast<Http2HeaderFrame>(frame);
            stream->header = headerFrame->getHeader();
            stream->moveTo(stream->HalfClosedLocalState);
            return nullptr;
        }
        break;

        case st(Http2Frame)::TypeRstStream: {
            stream->moveTo(stream->ClosedState);
        }
        break;

        case st(Http2Frame)::TypeContinuation: {
            //TODO
        }

        break;

        default:
            LOG(ERROR)<<"Http2Stream Receive Illegal Frame,Current :ReservedRemote , FrameType :"<<type;
        break;
    }
    return nullptr;
}

bool _Http2StreamReservedRemote::onSend(Http2Frame frame) {
    int type = frame->getType();
    switch(type) {
        case st(Http2Frame)::TypeRstStream: {
            stream->moveTo(stream->ClosedState);
        }
        break;

        default:
            LOG(ERROR)<<"Http2Stream Send Illegal Frame,Current :ReservedRemote , FrameType :"<<type;
        break;
    }

    return false;
}

//------------------ state:Open -------------------------
_Http2StreamOpen::_Http2StreamOpen(_Http2Stream *p):_Http2StreamState(p) {
    mState = st(Http2Stream)::Open;
}

Http2Packet _Http2StreamOpen::onReceived(Http2Frame frame) {
    switch(frame->getType()) {
        case st(Http2Frame)::TypeContinuation: {
            Http2ContinuationFrame continuationFrame = Cast<Http2ContinuationFrame>(frame);
            stream->header->addHttpHeader(continuationFrame->getHeaders());
            if(continuationFrame->isEndHeaders()) {
                return createHttp2Packet(continuationFrame->getStreamId(),stream->header,nullptr);
            }
            break;
        }

        case st(Http2Frame)::TypeRstStream: {
            stream->moveTo(stream->ClosedState);
            return nullptr;
        }

        case st(Http2Frame)::TypeData: {
            Http2DataFrame dataFrame = Cast<Http2DataFrame>(frame);
            return createHttp2Packet(stream->getStreamId(),stream->header,dataFrame->getData());
        }
        break;
    }

    if(frame->isEndStream()) {
        stream->moveTo(stream->HalfClosedRemoteState);
    }

    return nullptr;
}

bool _Http2StreamOpen::onSend(Http2Frame frame) {
    int type = frame->getType();
    printf("http2stream open onsend,type is %d \n",type);
    if(stream->out == nullptr) {
        printf("stream out is nullptr \n");
    }
    
    switch(type) {
        case st(Http2Frame)::TypeRstStream: {
            stream->moveTo(stream->ClosedState);
        }
        break;

        case st(Http2Frame)::TypeData:
        case st(Http2Frame)::TypeHeaders:  {
            stream->out->write(frame->toFrameData());
        }
        break;
    }

    return false;
}

//------------------ state:HalfClosedLocal -------------------------
_Http2StreamHalfClosedLocal::_Http2StreamHalfClosedLocal(_Http2Stream *p):_Http2StreamState(p) {
    mState = st(Http2Stream)::HalfClosedLocal;
}

Http2Packet _Http2StreamHalfClosedLocal::onReceived(Http2Frame frame) {
    int type = frame->getType();
    switch(type) {
        case st(Http2Frame)::TypeRstStream:
            stream->moveTo(stream->ClosedState);
        break;
    }

    if(frame->isEndStream()) {
        stream->moveTo(stream->ClosedState);
    }

    return nullptr;
}

bool _Http2StreamHalfClosedLocal::onSend(Http2Frame frame) {
    int type = frame->getType();
    switch(type) {
        case st(Http2Frame)::TypeRstStream:
            stream->moveTo(stream->ClosedState);
        break;

        default:
            LOG(ERROR)<<"Http2Stream Send Illegal Frame,Current :HalfClosedLocal , FrameType :"<<type;
        break;
    }
    return false;
}

//------------------ state:HalfClosedRemote -------------------------
_Http2StreamHalfClosedRemote::_Http2StreamHalfClosedRemote(_Http2Stream *p):_Http2StreamState(p) {
    mState = st(Http2Stream)::HalfClosedRemote;
}

Http2Packet _Http2StreamHalfClosedRemote::onReceived(Http2Frame frame) {
    int type = frame->getType();
    switch(type) {
        case st(Http2Frame)::TypeRstStream:
            stream->moveTo(stream->ClosedState);
        break;
    }
    return nullptr;
}

bool _Http2StreamHalfClosedRemote::onSend(Http2Frame frame) {
    int type = frame->getType();
    switch(type) {
        case st(Http2Frame)::TypeRstStream:
            stream->moveTo(stream->ClosedState);
        break;
    }

    return false;
}

//------------------ state:Closed -------------------------
_Http2StreamClosed::_Http2StreamClosed(_Http2Stream *p):_Http2StreamState(p) {
    mState = st(Http2Stream)::Closed;
}

Http2Packet _Http2StreamClosed::onReceived(Http2Frame frame) {
    LOG(ERROR)<<"Http2Stream Receive Illegal Frame,Current :Closed , FrameType :"<<frame->getType();
    return nullptr;
}

bool _Http2StreamClosed::onSend(Http2Frame frame) {
    LOG(ERROR)<<"Http2Stream Send Illegal Frame,Current :Closed , FrameType :"<<frame->getType();
    return false;
}

//------------------ Http2Stream -------------------------
const char* _Http2Stream::IdleString = "Idle";
const char* _Http2Stream::ReservedLocalString = "ReservedLocal";
const char* _Http2Stream::ReservedRemoteString = "ReservedRemote";
const char* _Http2Stream::OpenString = "Open";
const char* _Http2Stream::HalfClosedLocalString = "HalfClosedLocal";
const char* _Http2Stream::HalfClosedRemoteString = "HalfCLosedRemote";
const char* _Http2Stream::ClosedString = "Closed";

std::atomic_int _Http2Stream::mServerStreamId(2);
std::atomic_int _Http2Stream::mClientStreamId(3);

const char *_Http2Stream::stateToString(int s) {
    switch(s) {
        case Idle:
        return IdleString;

        case ReservedLocal:
        return ReservedLocalString;

        case ReservedRemote:
        return ReservedRemoteString;

        case Open:
        return OpenString;

        case HalfClosedLocal:
        return HalfClosedLocalString;

        case HalfClosedRemote:
        return HalfClosedRemoteString;

        case Closed:
        return ClosedString;
    }

    return nullptr;
}
    
_Http2Stream::_Http2Stream(HPackEncoder e,HPackDecoder d,uint32_t id,OutputStream stream):_Http2Stream(e,d,(id%2) == 0,stream) {
    mStreamId = id;
}

_Http2Stream::_Http2Stream(HPackEncoder e,HPackDecoder d,bool isServer,OutputStream stream) {
    if(isServer) {
        mStreamId = mServerStreamId++;
    } else {
        mStreamId = mClientStreamId++;
    }

    encoder = e;
    decoder = d;
    
    IdleState = createHttp2StreamIdle(this);
    ReservedLocalState = createHttp2StreamReservedLocal(this);
    ReservedRemoteState = createHttp2StreamReservedRemote(this);
    OpenState = createHttp2StreamOpen(this);
    HalfClosedLocalState = createHttp2StreamHalfClosedLocal(this);
    HalfClosedRemoteState = createHttp2StreamHalfClosedRemote(this);
    ClosedState = createHttp2StreamClosed(this);

    mState = IdleState;
    
    out = stream;
}

int _Http2Stream::getStreamId() {
    return mStreamId;
}

void _Http2Stream::setStreamId(int id) {
    mStreamId = id;
}

void _Http2Stream::moveTo(Http2StreamState s) {
    mState = s;
}

Http2Packet _Http2Stream::applyFrame(Http2Frame frame) {
    return mState->onReceived(frame);
}


int _Http2Stream::write(HttpPacket packet) {
    //TODO
    Http2Packet pack = Cast<Http2Packet>(packet);
    printf("http2stream write start \n");
    //this is called from user's Http2ResponseWriter....
    Http2HeaderFrame frame  = createHttp2HeaderFrame(decoder,encoder);
    HttpHeader h = pack->getHeader();
    h->setType(st(HttpHeader)::Response);
    frame->setHeader(h);
    
    frame->setStreamId(this->getStreamId());
    frame->setEndHeaders(true);
    mState->onSend(frame);

    printf("http2stream write trace1 \n");
    Http2DataFrame dataFrame = createHttp2DataFrame();
    dataFrame->setData(pack->getData());
    dataFrame->setStreamId(this->getStreamId());
    dataFrame->setEndStream(true);
    mState->onSend(dataFrame);

    return 0;
}

HttpHeader _Http2Stream::getHeader() {
    return header;
}

}
