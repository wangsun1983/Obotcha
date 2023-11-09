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
#include "Http2RstFrame.hpp"
#include "Http2ContinuationFrame.hpp"

namespace obotcha {

_Http2StreamState::_Http2StreamState(_Http2Stream * p):stream(p) {
}

int _Http2StreamState::state() const {
    return mState;
}

//------------------ state:Idle -------------------------
_Http2StreamIdle::_Http2StreamIdle(_Http2Stream *p):_Http2StreamState(p) {
    mState = st(Http2Stream)::Idle;
}

Http2Packet _Http2StreamIdle::onReceived(Http2Frame frame) {
    switch(auto type = frame->getType();type) {
        case st(Http2Frame)::Type::Headers:{
            printf("i accept a header \n");
            Http2HeaderFrame headerFrame = Cast<Http2HeaderFrame>(frame);
            if(headerFrame->isEndHeaders()) {
                stream->header = headerFrame->getHeader();      
                stream->moveTo(stream->OpenState);
            } else {
                stream->mHeadBlockFragment = headerFrame->getSavedData();
            }

            if(headerFrame->isEndStream()) {
                //recv H->open->recv ES->half closed remote
                printf("i move to half closed remoteState \n");
                stream->moveTo(stream->HalfClosedRemoteState);
                if(headerFrame->isEndHeaders()) {
                    return createHttp2Packet(frame->getStreamId(),stream->header);
                }
            }
        } break;

        case st(Http2Frame)::Type::PushPromise: {
            Http2PushPromiseFrame pushpromiseFrame = Cast<Http2PushPromiseFrame>(frame);
            stream->header = pushpromiseFrame->getHttpHeaders();
            stream->moveTo(stream->ReservedRemoteState);
        } break;

        case st(Http2Frame)::Type::Settings: {
            printf("http2frame idle get a settings frame \n");
            Http2SettingFrame settingsFrame = Cast<Http2SettingFrame>(frame);
            if(settingsFrame->isAck()) {
                //stream->directWrite(settingsFrame);
                stream->mDataDispatcher->submitSetting(stream,settingsFrame);
            } else {
                //update remote flow control
                stream->mRemoteController->setDefaultWindowSize(settingsFrame->getInitialWindowSize());

                //send outself settings
                Http2SettingFrame responseSettings = createHttp2SettingFrame();
                responseSettings->setAsDefault();
                printf("setting initialwindow size is %d \n",responseSettings->getInitialWindowSize());
                stream->mLocalController->setDefaultWindowSize(responseSettings->getInitialWindowSize());
                //stream->directWrite(responseSettings);
                stream->mDataDispatcher->submitSetting(stream,responseSettings);
            }
        } break;

        case st(Http2Frame)::Type::WindowUpdate: {
            Http2WindowUpdateFrame updateFrame = Cast<Http2WindowUpdateFrame>(frame);
            stream->mRemoteController->onReceive(updateFrame->getStreamId(),
                                                updateFrame->getWindowSize());
        } break;

        case st(Http2Frame)::Type::Continuation: {
            printf("i accept a continuation frame \n");
        } break;

        default:
            LOG(ERROR)<<"Http2Stream Receive Illegal Frame,Current :Idle , FrameType :"<<static_cast<int>(type);
        break;
    }

    return nullptr;
}

bool _Http2StreamIdle::onSend(Http2Frame frame) {
    auto type = frame->getType();
    switch(type) {
        case st(Http2Frame)::Type::Headers:{
            stream->directWrite(frame);
            stream->moveTo(stream->OpenState);
            return true;
        }

        case st(Http2Frame)::Type::PushPromise:{
            stream->directWrite(frame);
            stream->moveTo(stream->ReservedLocalState);
            return true;
        }

        case st(Http2Frame)::Type::Settings: {
            stream->directWrite(frame);
            return true;
        }

        default:
            LOG(ERROR)<<"Http2Stream Send Illegal Frame,Current :Idle , FrameType :"
                        <<static_cast<int>(type);
        break;
    }

    return false;
}

//------------------ state:ReservedLocal -------------------------
_Http2StreamReservedLocal::_Http2StreamReservedLocal(_Http2Stream *p):_Http2StreamState(p) {
    mState = st(Http2Stream)::ReservedLocal;
}

Http2Packet _Http2StreamReservedLocal::onReceived(Http2Frame frame) {
    auto type = frame->getType();
    switch(frame->getType()) {
        case st(Http2Frame)::Type::RstStream:{
            stream->moveTo(stream->ClosedState);
            break;
        }

        default:
            LOG(ERROR)<<"Http2Stream Receive Illegal Frame,Current :ReservedLocal , FrameType :"
                        <<static_cast<int>(type);
        break;
    }
    return nullptr;
}

bool _Http2StreamReservedLocal::onSend(Http2Frame frame) {
    auto type = frame->getType();
    switch(frame->getType()) {
        case st(Http2Frame)::Type::Headers: {
            stream->moveTo(stream->HalfClosedRemoteState);
            return true;
        }

        case st(Http2Frame)::Type::RstStream: {
            stream->moveTo(stream->ClosedState);
            return true;
        }

        default:
            LOG(ERROR)<<"Http2Stream Send Illegal Frame,Current :ReservedLocal , FrameType :"
                        <<static_cast<int>(type);
        break;
    }

    return false;
}

//------------------ state:ReservedRemote -------------------------
_Http2StreamReservedRemote::_Http2StreamReservedRemote(_Http2Stream *p):_Http2StreamState(p) {
    mState = st(Http2Stream)::ReservedRemote;
}

Http2Packet _Http2StreamReservedRemote::onReceived(Http2Frame frame) {
    auto type = frame->getType();
    switch(type) {
        case st(Http2Frame)::Type::Headers: {
            Http2HeaderFrame headerFrame = Cast<Http2HeaderFrame>(frame);
            stream->header = headerFrame->getHeader();
            stream->moveTo(stream->HalfClosedLocalState);
            return nullptr;
        }

        case st(Http2Frame)::Type::RstStream: {
            stream->moveTo(stream->ClosedState);
        }
        break;

        case st(Http2Frame)::Type::Continuation: {
            //TODO
        }

        break;

        default:
            LOG(ERROR)<<"Http2Stream Receive Illegal Frame,Current :ReservedRemote , FrameType :"
                <<static_cast<int>(type);
        break;
    }
    return nullptr;
}

bool _Http2StreamReservedRemote::onSend(Http2Frame frame) {
    auto type = frame->getType();
    switch(type) {
        case st(Http2Frame)::Type::RstStream: {
            stream->moveTo(stream->ClosedState);
        }
        break;

        default:
            LOG(ERROR)<<"Http2Stream Send Illegal Frame,Current :ReservedRemote , FrameType :"
                        <<static_cast<int>(type);
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
        case st(Http2Frame)::Type::Continuation: {
            // Http2ContinuationFrame continuationFrame = Cast<Http2ContinuationFrame>(frame);
            // stream->header->append(continuationFrame->getHeaders());
            // if(continuationFrame->isEndHeaders()) {
            //     //return createHttp2Packet(continuationFrame->getStreamId(),stream->header,nullptr);
            //     ArrayList<Http2Frame> frames = createArrayList<Http2Frame>();
            //     frames->add(frame);
            //     return frames;
            // }
            //TODO
            break;
        }

        case st(Http2Frame)::Type::RstStream: {
            stream->moveTo(stream->ClosedState);
            return nullptr;
        }

        case st(Http2Frame)::Type::Data: {
            printf("frame data \n");
            Http2DataFrame dataFrame = Cast<Http2DataFrame>(frame);
            auto recvdata = dataFrame->getData();
            if(stream->mCacheData == nullptr) {
                stream->mCacheData = recvdata;
            } else {
                if(recvdata != nullptr) {
                    stream->mCacheData->append(recvdata);
                }
            }

            if(stream->mRemoteController != nullptr) {
                stream->mRemoteController->onReceive(stream->getStreamId(),
                                                recvdata == nullptr?0:recvdata->size());
            }
            
            if(dataFrame->isEndStream()) {
                auto packet = createHttp2Packet(frame->getStreamId(),stream->header);
                HttpEntity entity = createHttpEntity();
                packet->setEntity(entity);
                //check whether it is multipart
                auto multipart = stream->header->getContentType();
                printf("multipart trace1 \n");
                if(multipart != nullptr) {
                    //TODO
                    printf("multipart trace2,boundary is %s \n",multipart->getBoundary()->toChars());
                    HttpMultiPartParser parser = createHttpMultiPartParser(multipart->getBoundary());
                    ByteRingArray ringArray = createByteRingArray(stream->mCacheData->size());
                    ringArray->push(stream->mCacheData);
                    ByteRingArrayReader r = createByteRingArrayReader(ringArray);
                    HttpMultiPart part = parser->parse(r);
                    entity->setMultiPart(part);
                } else {
                    entity->setContent(stream->mCacheData);
                }
                printf("multipart trace3 \n");
                stream->mCacheData = nullptr;
                return packet;
            }
            
            return nullptr;
        }

        case st(Http2Frame)::Type::WindowUpdate: {
            //update windwo size
            Http2WindowUpdateFrame updateFrame = Cast<Http2WindowUpdateFrame>(frame);
            printf("Http2Frame open,accept window update,id is %d,size is %ld \n",updateFrame->getStreamId(),updateFrame->getWindowSize());
            stream->mLocalController->updateWindowSize(updateFrame->getStreamId(),updateFrame->getWindowSize());
        }
        break;

        case st(Http2Frame)::Type::Settings: {
            Http2SettingFrame settingsFrame = Cast<Http2SettingFrame>(frame);
            if(settingsFrame->isAck()) {
                //Send ackframe
                //stream->directWrite(settingsFrame);
                stream->mDataDispatcher->submitSetting(stream,settingsFrame);
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
    auto type = frame->getType();
    switch(type) {
        case st(Http2Frame)::Type::RstStream: {
            stream->moveTo(stream->ClosedState);
        }
        break;

        case st(Http2Frame)::Type::Data:
        case st(Http2Frame)::Type::Headers:  {
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

Http2Packet _Http2StreamHalfClosedLocal::onReceived(Http2Frame frame) {
    auto type = frame->getType();
    switch(type) {
        case st(Http2Frame)::Type::RstStream:
            stream->moveTo(stream->ClosedState);
        break;
    }

    if(frame->isEndStream()) {
        stream->moveTo(stream->ClosedState);
    }

    return nullptr;
}

bool _Http2StreamHalfClosedLocal::onSend(Http2Frame frame) {
    printf("_Http2StreamHalfClosedLocal onSend \n");
    auto type = frame->getType();
    switch(type) {
        case st(Http2Frame)::Type::RstStream:
            stream->moveTo(stream->ClosedState);
        break;

        default:
            LOG(ERROR)<<"Http2Stream Send Illegal Frame,Current :HalfClosedLocal , FrameType :"
                        <<static_cast<int>(type);
        break;
    }
    return false;
}

//------------------ state:HalfClosedRemote -------------------------
_Http2StreamHalfClosedRemote::_Http2StreamHalfClosedRemote(_Http2Stream *p):_Http2StreamState(p) {
    mState = st(Http2Stream)::HalfClosedRemote;
}

Http2Packet _Http2StreamHalfClosedRemote::onReceived(Http2Frame frame) {
    auto type = frame->getType();
    switch(type) {
        case st(Http2Frame)::Type::RstStream:
            stream->moveTo(stream->ClosedState);
        break;

        case st(Http2Frame)::Type::WindowUpdate: {
            Http2WindowUpdateFrame windowSizeFrame = Cast<Http2WindowUpdateFrame>(frame);
            stream->mLocalController->updateWindowSize(windowSizeFrame->getStreamId(),windowSizeFrame->getWindowSize());
        } break;

        case st(Http2Frame)::Type::Continuation: {
            printf("half_closed_remote accept a continuation \n");
            Http2ContinuationFrame continuationFrame = Cast<Http2ContinuationFrame>(frame);
            if(continuationFrame != nullptr) {
                printf("half_closed_remote accept a continuation trace2 \n");
                if(stream->mHeadBlockFragment == nullptr) {
                    stream->mHeadBlockFragment = continuationFrame->getHeadBlockFragment();
                } else {
                    stream->mHeadBlockFragment->append(continuationFrame->getHeadBlockFragment());
                }

                if(continuationFrame->isEndHeaders()) {
                    stream->header = createHttpHeader(st(Net)::Protocol::Http_H2);
                    stream->decoder->decode(continuationFrame->getStreamId(),
                                            stream->mHeadBlockFragment,
                                            stream->header,true);
                    return createHttp2Packet(frame->getStreamId(),stream->header);
                }
            }
        } break;
    }
    return nullptr;
}

bool _Http2StreamHalfClosedRemote::onSend(Http2Frame frame) {
    printf("_Http2StreamHalfClosedRemote onSend \n");
    auto type = frame->getType();
    switch(type) {
        case st(Http2Frame)::Type::RstStream:
            stream->moveTo(stream->ClosedState);
        break;

        case st(Http2Frame)::Type::Data:
        case st(Http2Frame)::Type::Headers:
        case st(Http2Frame)::Type::Continuation:
            //send data to HalfClosedRemote
            printf("_Http2StreamHalfClosedRemote onSend trace1 \n");
            stream->directWrite(frame);
        break;
    }

    return false;
}

//------------------ state:Closed -------------------------
_Http2StreamClosed::_Http2StreamClosed(_Http2Stream *p):_Http2StreamState(p) {
    mState = st(Http2Stream)::Closed;
}

Http2Packet _Http2StreamClosed::onReceived(Http2Frame frame) {
    LOG(ERROR)<<"Http2Stream Receive Illegal Frame,Current :Closed , FrameType :"
                <<static_cast<int>(frame->getType());
    return nullptr;
}

bool _Http2StreamClosed::onSend(Http2Frame frame) {
    LOG(ERROR)<<"Http2Stream Send Illegal Frame,Current :Closed , FrameType :"
                <<static_cast<int>(frame->getType());
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
    
_Http2Stream::_Http2Stream(HPackEncoder e,
                           HPackDecoder d,
                           Http2FrameTransmitter dispatcher,
                           uint32_t id,Http2StreamSender stream):
                           mStreamId(id),mDataDispatcher(dispatcher),encoder(e),
                           decoder(d),out(stream) {
    init();
}

_Http2Stream::_Http2Stream(HPackEncoder e,
                           HPackDecoder d,
                           Http2FrameTransmitter dispatcher,
                           bool isServer,Http2StreamSender stream):
                           mDataDispatcher(dispatcher),encoder(e),decoder(d),out(stream) {
    mStreamId = isServer?mServerStreamId++:mClientStreamId++;
    init();
}

void _Http2Stream::init() {
    IdleState = createHttp2StreamIdle(this);
    ReservedLocalState = createHttp2StreamReservedLocal(this);
    ReservedRemoteState = createHttp2StreamReservedRemote(this);
    OpenState = createHttp2StreamOpen(this);
    HalfClosedLocalState = createHttp2StreamHalfClosedLocal(this);
    HalfClosedRemoteState = createHttp2StreamHalfClosedRemote(this);
    ClosedState = createHttp2StreamClosed(this);
    mState = IdleState;
}

void _Http2Stream::setFlowController(Http2RemoteFlowController remote,Http2LocalFlowController local) {
    mRemoteController = remote;
    mLocalController = local;
}

int _Http2Stream::getStreamId() const {
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

int _Http2Stream::directWrite(Http2Frame frame) {
    out->write(frame);
    return 0;
}

int _Http2Stream::directWriteData(Http2FrameByteArray framedata) {
    out->write(framedata);
    return 0;
}

Http2StreamState _Http2Stream::getStreamState() {
    return mState;
}

int _Http2Stream::write(HttpPacket packet) {
    Http2Packet pack = createHttp2Packet(this->getStreamId(),packet->getHeader());
    pack->setEntity(packet->getEntity());
    auto entity =  packet->getEntity();
    bool containsData = false;

    if(entity != nullptr) {

        if((entity->getContent() != nullptr && entity->getContent()->size() != 0)
            ||entity->getChunk() != nullptr && 
                    (entity->getChunk()->size() != 0 || entity->getChunk()->isFile())) {
            printf("wangsl,_Http2Stream trace0,not contain data\n");
            containsData = true;
        }
    }
    //this is called from user's Http2ResponseWriter....
    Http2HeaderFrame frame  = createHttp2HeaderFrame(decoder,encoder);
    //we should calculate content length
    HttpHeader h = pack->getHeader();
    h->setType(st(Http)::PacketType::Response);
    auto data = pack->getEntity()->getContent();
    int length = (data == nullptr?0:data->size());
    if(length != 0) {
        h->setContentLength(createHttpHeaderContentLength(length));
    }
    frame->setHeader(h);    
    frame->setStreamId(this->getStreamId());
    frame->setEndStream(!containsData);
    Http2FrameByteArray framedata = frame->toFrameData();
    auto actualSize = mLocalController->computeSendSize(getStreamId(),mDataDispatcher->getDefaultSendSize());
    printf("wangsl,_Http2Stream trace1,data size is %ld,actualsize is %ld \n",framedata->size(),actualSize);
    if(framedata->size() >= actualSize) {
        printf("wangsl,_Http2Stream trace2\n");
        //frame->setEndHeaders(false);
        printf("before frame data is %x \n",framedata[4]);
        framedata[4] &= ~0x4;
        printf("after frame data is %x \n",framedata[4]);
    } else {
        printf("wangsl,_Http2Stream trace3\n");
        //frame->setEndHeaders(true);
        framedata[4] |= 0x4;
    }
    //framedata = frame->toFrameData();

    mDataDispatcher->submitHeader(AutoClone(this),framedata);

    if(containsData) {
        if(entity->getContent() != nullptr) {
            printf("wangsl,_Http2Stream trace3\n");
            mDataDispatcher->submitContent(AutoClone(this),entity->getContent());
        } else {
            mDataDispatcher->submitFile(AutoClone(this),
                                        Cast<FileInputStream>(entity->getChunk()->getInputStream()));
        }
    }

    return 0;
}

HttpHeader _Http2Stream::getHeader() {
    return header;
}

}
