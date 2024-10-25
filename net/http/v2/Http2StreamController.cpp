#include "Http2StreamController.hpp"
#include "Http2Frame.hpp"
#include "HttpMethod.hpp"
#include "Log.hpp"
#include "AutoLock.hpp"
#include "Http2SettingFrame.hpp"
#include "Http2WindowUpdateFrame.hpp"
#include "HttpPacketWriterImpl.hpp"

#include "Http2DataFrame.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

_Http2StreamController::_Http2StreamController(OutputStream param_out,[[maybe_unused]]Http2FrameOption option):
                                                out(param_out) {
    mRingArray = ByteRingArray::New(st(Http)::Config::kBufferSize);
    shakeHandFrame = Http2ShakeHandFrame::New(mRingArray);
    mReader = ByteRingArrayReader::New(mRingArray);
    mFrameParser = Http2FrameParser::New(mReader,decoder);
    mSender = Http2StreamSender::New(out);
    mSender->start();
    mRemoteController = Http2RemoteFlowController::New(out,mMutex,streams);
    //some code smells~
    mLocalController = Http2LocalFlowController::New();
    mDataDispatcher = Http2FrameTransmitter::New(mLocalController);
    mLocalController->bindDispatcher(mDataDispatcher);
    mDataDispatcher->start();
}

int _Http2StreamController::pushData(ByteArray data) {
    try {
        mRingArray->push(data);
    } catch (ArrayIndexOutOfBoundsException &) {
        LOG(ERROR) << "Http2PacketParserImpl error ,data overflow";
        return -1;
    }

    return 0;
}

ArrayList<HttpPacket> _Http2StreamController::doParse() {
    while(mReader->getReadableLength() >= 9) {
        switch(mStatus) {
            case Status::ShakeHand:{
                ArrayList<HttpPacket> packets = shakeHandFrame->doParser();
                if(packets->size() > 1) {
                    LOG(ERROR)<<"HttpV2 parse shake message size > 1";
                    return nullptr;
                }
                //start shake hand
                HttpPacket packet = packets->get(0);
                HttpHeader header = packet->getHeader();
                if((header->getMethod() == st(HttpMethod)::Id::Get ||
                   header->getMethod() == st(HttpMethod)::Id::Post) 
                    && header->getUpgrade()->toString()->sameAs("h2c")) {
                    //we should decode it's setting frame
                    String settingframe = header->get("http2-settings");
                    ByteArray data = mBase64->decodeBase64Url(settingframe->toByteArray());
                    Http2SettingFrame frame = Http2SettingFrame::New();
                    frame->load(data);
                    //TODO

                    HttpPacketWriterImpl impl = HttpPacketWriterImpl::New(out);
                    auto shakeHande = Http2ShakeHandFrame::New();
                    int ret = impl->write(shakeHande->toShakeHandPacket(st(Net)::Protocol::Http_H2));
                    mStatus = Status::Preface;
                } else if(header->getMethod() == st(HttpMethod)::Id::Pri 
                    && packet->getEntity()->getContent()->toString()->equalsIgnoreCase("SM")) {
                    mStatus = Status::WaitFirstSetting;
                    // Http2SettingFrame settingFrame = Http2SettingFrame::New();
                    // settingFrame->setAsDefault();
                    // out->write(settingFrame->toFrameData());

                    //update test wangsl
                    // Http2WindowUpdateFrame updateFrame = Http2WindowUpdateFrame::New();
                    // updateFrame->setWindowSize(983041);
                    // out->write(updateFrame->toFrameData());
                    //update test wangsl
                    if(mRingArray->getStoredDataSize() != 0) {
                        mReader->setCursor(mRingArray->getStartIndex());
                        continue;
                    } else {
                        mRingArray->reset();
                    }
                }

                return nullptr;
            }

            case Status::Preface:{
                ArrayList<HttpPacket> packets = shakeHandFrame->doParser();
                if(packets->size() > 1) {
                    LOG(ERROR)<<"HttpV2 parse Preface size > 1";
                    return nullptr;
                }

                HttpPacket packet = packets->get(0);
                HttpHeader header = packet->getHeader();
                if(header->getMethod() == st(HttpMethod)::Id::Pri 
                    && packet->getEntity()->getContent()->toString()->equalsIgnoreCase("SM")) {
                    mStatus = Status::WaitFirstSetting;
                    //we should send a http setting frame;
                    // Http2SettingFrame ackFrame = Http2SettingFrame::New();
                    // ackFrame->setAsDefault();
                    // out->write(ackFrame->toFrameData());

                    if(mRingArray->getStoredDataSize() != 0) {
                        mReader->setCursor(mRingArray->getStartIndex());
                        continue;
                    } else {
                        mRingArray->reset();
                    }
                }
            }
            break;

            case Status::WaitFirstSetting: //{
//                 ArrayList<Http2Frame> frames = mFrameParser->doParse();
//                 bool isHit = false;
//                 if(frames != nullptr && frames->size() != 0) {
//                     ForEveryOne(frame,frames) {
//                         switch(frame->getType()) {
//                             case st(Http2Frame)::Type::Settings:
//                             if(frame->isAck()) {
//                                 //TODO？ do not send ack as client
//                                 isHit = true;
//                                 out->write(frame->toFrameData());
//                             } else {
//                                 //TODO
// #if 0                                
//                                 Http2SettingFrame settingFrame = Cast<Http2SettingFrame>(frame);
//                                 auto v = settingFrame->getMaxConcurrentStreams();
//                                 if(v != 0) {
//                                     mStatistics->setMaxStreamCount(v);
//                                 }

//                                 v = settingFrame->getMaxConcurrentStreams();
//                                 if(v != 0) {
//                                     mStatistics->setMaxFrameSize(v);
//                                 }

//                                 v = settingFrame->getInitialWindowSize();
//                                 if(v != 0) {
//                                     mStatistics->setWindowSize(v);
//                                 }
//                                 printf("i send setting frame!!!!!! \n");
//                                 Http2SettingFrame ackFrame = Http2SettingFrame::New();
//                                 ackFrame->setAck(true);
//                                 out->write(ackFrame->toFrameData());
// #endif                                
//                             }
//                             break;

//                             case st(Http2Frame)::Type::Data:
//                             case st(Http2Frame)::Type::Headers:
//                                 mFirstSettingCaches->add(frame);
//                             break;
//                         }
//                     }
//                 }

//                 if(!isHit) {
//                     break;
//                 } else {
//                     mStatus = Status::Comunicate;
//                 }
//             }
//             [[fallthrough]];

            case Status::Comunicate: {
                ArrayList<Http2Frame> frames = mFrameParser->doParse();
                if(mFirstSettingCaches->size() != 0) {
                    if(frames == nullptr) {
                        frames = ArrayList<Http2Frame>::New();
                    }
                    frames->add(mFirstSettingCaches);
                    mFirstSettingCaches->clear();
                }

                ArrayList<HttpPacket> packets  = ArrayList<HttpPacket>::New();
                if(frames != nullptr && frames->size() != 0) {    
                    auto iterator = frames->getIterator();
                    while(iterator->hasValue()) {
                        //we should check every frame to do some action
                        //only data/header frame should send user.
                        Http2Frame frame = iterator->getValue();
                        Http2Stream stream = streams->get(Integer::New(frame->getStreamId()));
                        if(stream == nullptr) {
                            stream = newStream(frame->getStreamId());
                            streams->put(Integer::New(frame->getStreamId()),stream);
                        }
                        
                        if(frame != nullptr) {
                            auto pack = stream->applyFrame(frame);
                            if(pack != nullptr) {
                                packets->add(pack);
                            }
                        }
                        iterator->next();
                    }
                    return packets;
                }
            }
            break;
        }
    }

    return nullptr;
}

void _Http2StreamController::postProcessing(ArrayList<HttpPacket> packets) {
    ForEveryOne(packet,packets) {
        auto p2 = Cast<Http2Packet>(packet);
        if(p2->isEnd()) {
           streams->remove(Integer::New(p2->getStreamId()));
        }
    }
}

HttpPacket _Http2StreamController::parseEntireRequest(ByteArray request) {
    //TODO
    return nullptr;
}

void _Http2StreamController::reset() {
    //do nothing
}

Http2Stream _Http2StreamController::newStream() {
    Http2Stream stream = Http2Stream::New(encoder,decoder,mDataDispatcher,true,mSender);
    stream->setFlowController(mRemoteController,mLocalController);
    mRemoteController->monitor(stream->getStreamId());
    mLocalController->monitor(stream->getStreamId());
    AutoLock l(mMutex);
    streams->put(Integer::New(stream->getStreamId()),stream);
    return stream;
}

Http2Stream _Http2StreamController::newStream(uint32_t streamid) {
    Http2Stream stream = Http2Stream::New(encoder,decoder,mDataDispatcher,streamid,mSender);
    stream->setFlowController(mRemoteController,mLocalController);
    mRemoteController->monitor(stream->getStreamId());
    mLocalController->monitor(stream->getStreamId());
    AutoLock l(mMutex);
    streams->put(Integer::New(stream->getStreamId()),stream);
    return stream;
}

Http2Stream _Http2StreamController::getStream(uint32_t id) {
    AutoLock l(mMutex);
    return streams->get(Integer::New(id));
}

_Http2StreamController::~_Http2StreamController() {
    mLocalController->destroy();
    mDataDispatcher->destroy();
}

}
