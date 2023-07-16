#include "Http2StreamController.hpp"
#include "Http2Frame.hpp"
#include "HttpMethod.hpp"
#include "Log.hpp"
#include "AutoLock.hpp"
#include "Enviroment.hpp"
#include "Http2SettingFrame.hpp"
#include "Http2WindowUpdateFrame.hpp"
#include "HttpPacketWriterImpl.hpp"
#include "NetProtocol.hpp"
#include "Http2DataFrame.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

_Http2StreamController::_Http2StreamController(OutputStream out,Http2FrameOption option) {
    mStatus = ShakeHand;
    mStatistics = createHttp2StreamStatistics();
    
    mRingArray = createByteRingArray(st(Enviroment)::getInstance()->getInt(st(Enviroment)::gHttpBufferSize, 4 * 1024));
    shakeHandFrame = createHttp2ShakeHandFrame(mRingArray);
    mReader = createByteRingArrayReader(mRingArray);
    mBase64 = createBase64();
    mIndex = 0;
    //mDefaultOptions = ((option == nullptr)?createHttp2FrameOption():option);
    encoder = createHPackEncoder();
    decoder = createHPackDecoder();
    mFrameParser = createHttp2FrameParser(mReader,decoder);
    
    mMutex = createMutex();
    streams = createHashMap<Integer,Http2Stream>();
    this->out = out;

    mSender = createHttp2StreamSender(out,mStatistics);
    mSender->start();

    mFirstSettingCaches = createArrayList<Http2Frame>();
}

int _Http2StreamController::pushData(ByteArray data) {
    try {
        mRingArray->push(data);
    } catch (ArrayIndexOutOfBoundsException &e) {
        LOG(ERROR) << "Http2PacketParserImpl error ,data overflow";
        return -1;
    }

    return 0;
}

ArrayList<HttpPacket> _Http2StreamController::doParse() {
    ArrayList<HttpPacket> packets = createArrayList<HttpPacket>();

    while(mReader->getReadableLength() >= 9) {
        switch(mStatus) {
            case ShakeHand:{
                ArrayList<HttpPacket> packets = shakeHandFrame->doParser();
                if(packets->size() > 1) {
                    LOG(ERROR)<<"HttpV2 parse shake message size > 1";
                    return nullptr;
                }
                //start shake hand
                HttpPacket packet = packets->get(0);
                HttpHeader header = packet->getHeader();
                if((header->getMethod() == st(HttpMethod)::Get ||
                   header->getMethod() == st(HttpMethod)::Post) 
                    && header->getUpgrade()->toString()->equals("h2c")) {
                    //we should decode it's setting frame
                    String settingframe = header->get("http2-settings");
                    ByteArray data = mBase64->decodeBase64Url(settingframe->toByteArray());
                    data->dump("Http2StreamController http settings!!!");
                    //TEST
                    Http2SettingFrame frame = createHttp2SettingFrame();
                    frame->import(data);

                    HttpPacketWriterImpl impl = createHttpPacketWriterImpl(out);
                    auto shakeHande = createHttp2ShakeHandFrame();
                    int ret = impl->write(shakeHande->toShakeHandPacket(st(NetProtocol)::Http_H2));
                    //data->dump("Http2StreamController http settings!!!");
                    //response get method
                    mStatus = Preface;
                } else if(header->getMethod() == st(HttpMethod)::Pri 
                    && packet->getEntity()->getContent()->toString()->equalsIgnoreCase("SM")) {
                    printf("move to comunication \n");
                    mStatus = WaitFirstSetting;
                    Http2SettingFrame settingFrame = createHttp2SettingFrame();
                    settingFrame->setAsDefault();

                    //  ackFrame->setHeaderTableSize(0);
                    //  ackFrame->setMaxFrameSize(1024*1024*32);
                    //  ackFrame->setMaxConcurrentStreams(250);
                    //  ackFrame->setInitialWindowSize(1048896);
                    //  ackFrame->setMaxHeaderListSize(1048896);
                    int len = out->write(settingFrame->toFrameData());
                    printf("len is %d \n",len);
                    
                    if(mRingArray->getStoredDataSize() != 0) {
                        mReader->setCursor(mRingArray->getStartIndex());
                        continue;
                    } else {
                        mRingArray->reset();
                    }
                }

                return nullptr;
            }

            case Preface:{
                ArrayList<HttpPacket> packets = shakeHandFrame->doParser();
                if(packets->size() > 1) {
                    LOG(ERROR)<<"HttpV2 parse Preface size > 1";
                    return nullptr;
                }

                HttpPacket packet = packets->get(0);
                HttpHeader header = packet->getHeader();
                //printf("Preface action!!!! \n");
                if(header->getMethod() == st(HttpMethod)::Pri 
                    && packet->getEntity()->getContent()->toString()->equalsIgnoreCase("SM")) {
                    mStatus = WaitFirstSetting;
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

            case WaitFirstSetting: {
                ArrayList<Http2Frame> frames = mFrameParser->doParse();
                bool isHit = false;
                if(frames != nullptr && frames->size() != 0) {
                    ForEveryOne(frame,frames) {
                        printf("WaitFirstSetting on frames,frame type is %d \n",frame->getType());
                        switch(frame->getType()) {
                            case st(Http2Frame)::TypeSettings:
                            if(frame->isAck()) {
                                //TODO？ do not send ack as client
                                isHit = true;
                                out->write(frame->toFrameData());
                                printf("windowUpdateFrame streamid,setting stream id is %d \n",frame->getStreamId());                             
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

                            case st(Http2Frame)::TypeData:
                            case st(Http2Frame)::TypeHeaders:
                                mFirstSettingCaches->add(frame);
                            break;
                        }
                    }
                }

                if(!isHit) {
                    break;
                } else {
                    printf("WaitFirstSetting on hit,mFirstSettingCaches size is %d \n",mFirstSettingCaches->size());
                    mStatus = Comunicate;
                }
            }

            case Comunicate: {
                printf("start comunication \n");
                ArrayList<Http2Frame> frames = mFrameParser->doParse();
                if(mFirstSettingCaches->size() != 0) {
                    printf("start comunication trace1 \n");
                    if(frames == nullptr) {
                        frames = createArrayList<Http2Frame>();
                    }
                    frames->add(mFirstSettingCaches);
                    mFirstSettingCaches->clear();
                    printf("start comunication trace2,frames size is %d \n",frames->size());
                }

                if(frames != nullptr && frames->size() != 0) {
                    ArrayList<HttpPacket> packets  = createArrayList<HttpPacket>();
                    printf("start comunication trace1,frame size is %d \n",frames->size());
                    auto iterator = frames->getIterator();
                    while(iterator->hasValue()) {
                        //we should check every frame to do some action
                        //only data/header frame should send user.
                        Http2Frame frame = iterator->getValue();
                        Http2Stream stream = streams->get(createInteger(frame->getStreamId()));
                        if(stream == nullptr) {
                            printf("start create Stream,frame id is %d",frame->getStreamId());
                            stream = newStream(frame->getStreamId());
                            streams->put(createInteger(frame->getStreamId()),stream);
                        }

                        printf("update stream status \n");
                        ArrayList<Http2Frame> frames = stream->applyFrame(frame); //update stream status;

                        if(frames != nullptr) {
                            ForEveryOne(myFrame,frames) {
                                printf("start do frame loop \n");
                                if(myFrame != frame) {
                                    stream->applyFrame(frame);
                                }

                                HttpPacket pack = nullptr;
                                if(frame->getType() == st(Http2Frame)::TypeData) {
                                    printf("start do frame loop 1\n");
                                    Http2DataFrame dataFrame = Cast<Http2DataFrame>(frame);
                                    pack = createHttp2Packet(frame->getStreamId(),stream->getHeader(),dataFrame->getData());

                                    //TODO?we should send an ack to 
                                    Http2WindowUpdateFrame updateFrame = createHttp2WindowUpdateFrame();
                                    updateFrame->setWindowSize(frame->getLength());
                                    out->write(updateFrame->toFrameData());
                                } else if(frame->getType() == st(Http2Frame)::TypeHeaders && frame->isEndStream()) {
                                    printf("start do frame loop 2\n");
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

    return packets;
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

}

Http2Stream _Http2StreamController::newStream() {
    if(mStatistics->incStreamCount()  < 0) {
        LOG(ERROR) << "Http2StreamController stream overflow";
        return nullptr;
    }
    
    Http2Stream stream = createHttp2Stream(encoder,decoder,mStatistics,true,mSender);
    printf("new stream trace2 id is %d \n",stream->getStreamId());
    //TODO
    AutoLock l(mMutex);
    streams->put(createInteger(stream->getStreamId()),stream);
    return stream;
}

Http2Stream _Http2StreamController::newStream(uint32_t streamid) {
    if(mStatistics->incStreamCount()  < 0) {
        LOG(ERROR) << "Http2StreamController newStream by id overflow";
        return nullptr;
    }
    printf("new stream trace1 id is %d \n",streamid);
    Http2Stream stream = createHttp2Stream(encoder,decoder,mStatistics,(uint32_t)streamid,mSender);
    AutoLock l(mMutex);
    printf("add to streams,stream id is %d \n",stream->getStreamId());
    streams->put(createInteger(stream->getStreamId()),stream);
    return stream;
}

Http2Stream _Http2StreamController::getStream(uint32_t id) {
    AutoLock l(mMutex);
    printf("add to streams,getStream id is %d,stream size is %d \n",id,streams->size());
    return streams->get(createInteger(id));
}

}
