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
#include "Http2SettingFrame.hpp"
#include "Http2WindowUpdateFrame.hpp"

namespace obotcha {

//Http2StreamState
_Http2StreamState::_Http2StreamState(_Http2Stream * p) {
    stream = p;
    mState = -1;
}

int _Http2StreamState::state() {
    return mState;
}

//------------------ state:Idle -------------------------
_Http2StreamIdle::_Http2StreamIdle(_Http2Stream *p):_Http2StreamState(p) {
    mState = st(Http2Stream)::Idle;
}

ArrayList<Http2Frame> _Http2StreamIdle::onReceived(Http2Frame frame) {
    int type = frame->getType();
    switch(type) {
        case st(Http2Frame)::TypeHeaders:{
            Http2HeaderFrame headerFrame = Cast<Http2HeaderFrame>(frame);
            stream->header = headerFrame->getHeader();
            stream->moveTo(stream->OpenState);
            if(headerFrame->isEndStream()) {
                ArrayList<Http2Frame> frames = createArrayList<Http2Frame>();
                frames->add(frame);
                return frames;
                //return createHttp2Packet(headerFrame->getStreamId(),stream->header,nullptr);
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
            Http2SettingFrame settingsFrame = Cast<Http2SettingFrame>(frame);
            if(settingsFrame->isAck()) {
                //Send ackframe
                printf("send ack frame!! \n");
                stream->directWrite(settingsFrame);
            }
        }
        break;

        //case st(Http2Frame)::TypeWindowUpdate: {
            // Http2WindowUpdateFrame windowUpdateFrame = Cast<Http2WindowUpdateFrame>(frame);
            // //TODO
            // windowUpdateFrame->setWindowSize(1024*1024*1024);
            // stream->directWrite(windowUpdateFrame->toFrameData());
            // printf("send window update frame \n");
            // //send ack to client
            // Http2SettingFrame settingsFrame = createHttp2SettingFrame();
            // settingsFrame->setAck(true);
            // stream->out->write(settingsFrame->toFrameData());
        //}
        //break;

        default:
            LOG(ERROR)<<"Http2Stream Receive Illegal Frame,Current :Idle , FrameType :"<<type;
        break;
    }

    return nullptr;
}

bool _Http2StreamIdle::onSend(Http2Frame frame) {
    int type = frame->getType();
    switch(type) {
        case st(Http2Frame)::TypeHeaders:{
            stream->directWrite(frame);
            stream->moveTo(stream->OpenState);
            return true;
        }

        case st(Http2Frame)::TypePushPromise:{
            stream->directWrite(frame);
            stream->moveTo(stream->ReservedLocalState);
            return true;
        }

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

ArrayList<Http2Frame> _Http2StreamReservedLocal::onReceived(Http2Frame frame) {
    int type = frame->getType();
    printf("_Http2StreamReservedLocal onreceived type is %d \n",type);
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

ArrayList<Http2Frame> _Http2StreamReservedRemote::onReceived(Http2Frame frame) {
    int type = frame->getType();
    printf("_Http2StreamReservedRemote onreceived type is %d \n",type);
    switch(type) {
        case st(Http2Frame)::TypeHeaders: {
            Http2HeaderFrame headerFrame = Cast<Http2HeaderFrame>(frame);
            stream->header = headerFrame->getHeader();
            stream->moveTo(stream->HalfClosedLocalState);
            return nullptr;
        }

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

ArrayList<Http2Frame> _Http2StreamOpen::onReceived(Http2Frame frame) {
    switch(frame->getType()) {
        case st(Http2Frame)::TypeContinuation: {
            Http2ContinuationFrame continuationFrame = Cast<Http2ContinuationFrame>(frame);
            stream->header->append(continuationFrame->getHeaders());
            if(continuationFrame->isEndHeaders()) {
                //return createHttp2Packet(continuationFrame->getStreamId(),stream->header,nullptr);
                ArrayList<Http2Frame> frames = createArrayList<Http2Frame>();
                frames->add(frame);
                return frames;
            }
            break;
        }

        case st(Http2Frame)::TypeRstStream: {
            stream->moveTo(stream->ClosedState);
            return nullptr;
        }

        case st(Http2Frame)::TypeData: {
            ArrayList<Http2Frame> frames = createArrayList<Http2Frame>();
            frames->add(frame);
            return frames;
        }

        case st(Http2Frame)::TypeWindowUpdate: {
            //update windwo size
            Http2WindowUpdateFrame updateFrame = Cast<Http2WindowUpdateFrame>(frame);
            stream->mStatistics->incWindowSize(updateFrame->getWindowSize());
            printf("http2stream,onupdate windowsize is %d \n",updateFrame->getWindowSize());
            stream->out->onUpdateWindowSize();
        }
        break;

        case st(Http2Frame)::TypeSettings: {
            Http2SettingFrame settingsFrame = Cast<Http2SettingFrame>(frame);
            if(settingsFrame->isAck()) {
                //Send ackframe
                stream->directWrite(settingsFrame);
            }
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
    printf("Http2StreamOpen::onSend,type is %d,length is %d\n",type,frame->getLength());
    switch(type) {
        case st(Http2Frame)::TypeRstStream: {
            stream->moveTo(stream->ClosedState);
        }
        break;

        case st(Http2Frame)::TypeData:
        case st(Http2Frame)::TypeHeaders:  {
            //auto data = frame->toFrameData();
            //if(data != nullptr) {
            stream->directWrite(frame);
            //}
        }
        break;
    }

    return false;
}

//------------------ state:HalfClosedLocal -------------------------
_Http2StreamHalfClosedLocal::_Http2StreamHalfClosedLocal(_Http2Stream *p):_Http2StreamState(p) {
    mState = st(Http2Stream)::HalfClosedLocal;
}

ArrayList<Http2Frame> _Http2StreamHalfClosedLocal::onReceived(Http2Frame frame) {
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

ArrayList<Http2Frame> _Http2StreamHalfClosedRemote::onReceived(Http2Frame frame) {
    int type = frame->getType();
    printf("_Http2StreamHalfClosedRemote onreceived type is %d \n",type);
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

ArrayList<Http2Frame> _Http2StreamClosed::onReceived(Http2Frame frame) {
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
    
_Http2Stream::_Http2Stream(HPackEncoder e,HPackDecoder d,Http2StreamStatistics statistic,uint32_t id,Http2StreamSender stream) {
    mStreamId = id;
    mStatistics = statistic;
    encoder = e;
    decoder = d;
    out = stream;

    init();
}

_Http2Stream::_Http2Stream(HPackEncoder e,HPackDecoder d,Http2StreamStatistics statistic,bool isServer,Http2StreamSender stream) {
    if(isServer) {
        mStreamId = mServerStreamId++;
    } else {
        mStreamId = mClientStreamId++;
    }
    mStatistics = statistic;
    encoder = e;
    decoder = d;
    out = stream;
    init();
}

void _Http2Stream::init() {
    //FirstSettingState = createHttp2StreamFirstSetting(this);
    IdleState = createHttp2StreamIdle(this);
    ReservedLocalState = createHttp2StreamReservedLocal(this);
    ReservedRemoteState = createHttp2StreamReservedRemote(this);
    OpenState = createHttp2StreamOpen(this);
    HalfClosedLocalState = createHttp2StreamHalfClosedLocal(this);
    HalfClosedRemoteState = createHttp2StreamHalfClosedRemote(this);
    ClosedState = createHttp2StreamClosed(this);

    //FirstSettingState->doFirstSend();
    mState = IdleState;
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

ArrayList<Http2Frame> _Http2Stream::applyFrame(Http2Frame frame) {
    return mState->onReceived(frame);
}

//int _Http2Stream::directWrite(Http2PriorityByteArray data,uint32_t datalength) {
int _Http2Stream::directWrite(Http2Frame frame) {
    //we should check and update whether send data
    //printf("directWrite trace1,data length is %d \n",datalength);
    if(frame->getType() == st(Http2Frame)::TypeData 
        && mStatistics->updateFrameSize(this->getStreamId(),frame->getLength()) != 0) {
        LOG(ERROR)<<"Http2Stream write frame oversize!!!";
        return -1;
    } 
    
    out->write(frame);
    return 0;
}

int _Http2Stream::write(HttpPacket packet) {
    //TODO
    //Http2Packet pack = Cast<Http2Packet>(packet);
    Http2Packet pack = createHttp2Packet(this->getStreamId(),packet->getHeader(),packet->getEntity()->getContent());
    bool containsData = ((pack->getData() != nullptr) && (pack->getData()->size() != 0));
    //this is called from user's Http2ResponseWriter....
    Http2HeaderFrame frame  = createHttp2HeaderFrame(decoder,encoder);
    //we should calculate content length
    HttpHeader h = pack->getHeader();
    h->setType(st(HttpHeader)::Response);
    auto data = pack->getData();
    int length = (data == nullptr?0:data->size());
    if(length != 0) {
        h->setContentLength(createHttpHeaderContentLength(length));
    }
    frame->setHeader(h);    
    frame->setStreamId(this->getStreamId());
    frame->setEndHeaders(true);

    frame->setEndStream(!containsData);
    mState->onSend(frame);

    if(containsData) {
        //TODO
        Http2DataFrame dataFrame = createHttp2DataFrame();
        dataFrame->setData(pack->getData());
        dataFrame->setLength(pack->getData()->size());
        dataFrame->setStreamId(this->getStreamId());
        dataFrame->setEndStream(true);
        mState->onSend(dataFrame);
    }

    return 0;
}

HttpHeader _Http2Stream::getHeader() {
    return header;
}

}
