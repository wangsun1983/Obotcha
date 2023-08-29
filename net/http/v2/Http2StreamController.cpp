#include "Http2StreamController.hpp"
#include "Http2Frame.hpp"
#include "HttpMethod.hpp"
#include "Log.hpp"
#include "AutoLock.hpp"
#include "Enviroment.hpp"
#include "Http2SettingFrame.hpp"
#include "Http2WindowUpdateFrame.hpp"
#include "HttpPacketWriterImpl.hpp"

#include "Http2DataFrame.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

_Http2StreamController::_Http2StreamController(OutputStream param_out,[[maybe_unused]]Http2FrameOption option):
                                                out(param_out) {
    mRingArray = createByteRingArray(st(Enviroment)::getInstance()->getInt(st(Enviroment)::gHttpBufferSize, 4 * 1024));
    shakeHandFrame = createHttp2ShakeHandFrame(mRingArray);
    mReader = createByteRingArrayReader(mRingArray);
    mFrameParser = createHttp2FrameParser(mReader,decoder);
    mSender = createHttp2StreamSender(out,mStatistics);
    mSender->start();
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
                    Http2SettingFrame frame = createHttp2SettingFrame();
                    frame->load(data);

                    HttpPacketWriterImpl impl = createHttpPacketWriterImpl(out);
                    auto shakeHande = createHttp2ShakeHandFrame();
                    int ret = impl->write(shakeHande->toShakeHandPacket(st(Net)::Protocol::Http_H2));
                    mStatus = Status::Preface;
                } else if(header->getMethod() == st(HttpMethod)::Id::Pri 
                    && packet->getEntity()->getContent()->toString()->equalsIgnoreCase("SM")) {
                    mStatus = Status::WaitFirstSetting;
                    Http2SettingFrame settingFrame = createHttp2SettingFrame();
                    settingFrame->setAsDefault();
                    out->write(settingFrame->toFrameData());
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
                    Http2SettingFrame ackFrame = createHttp2SettingFrame();
                    ackFrame->setAsDefault();
                    out->write(ackFrame->toFrameData());

                    if(mRingArray->getStoredDataSize() != 0) {
                        mReader->setCursor(mRingArray->getStartIndex());
                        continue;
                    } else {
                        mRingArray->reset();
                    }
                }
            }
            break;

            case Status::WaitFirstSetting: {
                ArrayList<Http2Frame> frames = mFrameParser->doParse();
                bool isHit = false;
                if(frames != nullptr && frames->size() != 0) {
                    ForEveryOne(frame,frames) {
                        switch(frame->getType()) {
                            case st(Http2Frame)::Type::Settings:
                            if(frame->isAck()) {
                                //TODO？ do not send ack as client
                                isHit = true;
                                out->write(frame->toFrameData());
                            } else {
                                //TODO
#if 0                                
                                Http2SettingFrame settingFrame = Cast<Http2SettingFrame>(frame);
                                auto v = settingFrame->getMaxConcurrentStreams();
                                if(v != 0) {
                                    mStatistics->setMaxStreamCount(v);
                                }

                                v = settingFrame->getMaxConcurrentStreams();
                                if(v != 0) {
                                    mStatistics->setMaxFrameSize(v);
                                }

                                v = settingFrame->getInitialWindowSize();
                                if(v != 0) {
                                    mStatistics->setWindowSize(v);
                                }
                                printf("i send setting frame!!!!!! \n");
                                Http2SettingFrame ackFrame = createHttp2SettingFrame();
                                ackFrame->setAck(true);
                                out->write(ackFrame->toFrameData());
#endif                                
                            }
                            break;

                            case st(Http2Frame)::Type::Data:
                            case st(Http2Frame)::Type::Headers:
                                mFirstSettingCaches->add(frame);
                            break;
                        }
                    }
                }

                if(!isHit) {
                    break;
                } else {
                    mStatus = Status::Comunicate;
                }
            }
            [[fallthrough]];

            case Status::Comunicate: {
                ArrayList<Http2Frame> frames = mFrameParser->doParse();
                if(mFirstSettingCaches->size() != 0) {
                    if(frames == nullptr) {
                        frames = createArrayList<Http2Frame>();
                    }
                    frames->add(mFirstSettingCaches);
                    mFirstSettingCaches->clear();
                }

                if(frames != nullptr && frames->size() != 0) {
                    ArrayList<HttpPacket> packets  = createArrayList<HttpPacket>();
                    auto iterator = frames->getIterator();
                    while(iterator->hasValue()) {
                        //we should check every frame to do some action
                        //only data/header frame should send user.
                        Http2Frame frame = iterator->getValue();
                        Http2Stream stream = streams->get(createInteger(frame->getStreamId()));
                        if(stream == nullptr) {
                            stream = newStream(frame->getStreamId());
                            streams->put(createInteger(frame->getStreamId()),stream);
                        }
                        ArrayList<Http2Frame> frames = stream->applyFrame(frame); //update stream status;

                        if(frames != nullptr) {
                            ForEveryOne(myFrame,frames) {
                                if(myFrame != frame) {
                                    stream->applyFrame(frame);
                                }

                                HttpPacket pack = nullptr;
                                if(frame->getType() == st(Http2Frame)::Type::Data) {
                                    Http2DataFrame dataFrame = Cast<Http2DataFrame>(frame);
                                    pack = createHttp2Packet(frame->getStreamId(),stream->getHeader(),dataFrame->getData());

                                    //TODO?we should send an ack to 
                                    Http2WindowUpdateFrame updateFrame = createHttp2WindowUpdateFrame();
                                    updateFrame->setWindowSize(frame->getLength());
                                    out->write(updateFrame->toFrameData());
                                } else if(frame->getType() == st(Http2Frame)::Type::Headers && frame->isEndStream()) {
                                    pack = createHttp2Packet(frame->getStreamId(),stream->getHeader(),nullptr);
                                }

                                if(pack != nullptr) {
                                    packets->add(pack);
                                }
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
           streams->remove(createInteger(p2->getStreamId()));
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
    if(mStatistics->incStreamCount()  < 0) {
        LOG(ERROR) << "Http2StreamController stream overflow";
        return nullptr;
    }
    
    Http2Stream stream = createHttp2Stream(encoder,decoder,mStatistics,true,mSender);
    AutoLock l(mMutex);
    streams->put(createInteger(stream->getStreamId()),stream);
    return stream;
}

Http2Stream _Http2StreamController::newStream(uint32_t streamid) {
    if(mStatistics->incStreamCount()  < 0) {
        LOG(ERROR) << "Http2StreamController newStream by id overflow";
        return nullptr;
    }
    
    Http2Stream stream = createHttp2Stream(encoder,decoder,mStatistics,streamid,mSender);
    AutoLock l(mMutex);
    streams->put(createInteger(stream->getStreamId()),stream);
    return stream;
}

Http2Stream _Http2StreamController::getStream(uint32_t id) {
    AutoLock l(mMutex);
    return streams->get(createInteger(id));
}

}
