#include "Http2StreamController.hpp"
#include "Http2Frame.hpp"
#include "HttpMethod.hpp"
#include "Log.hpp"
#include "AutoLock.hpp"
#include "Enviroment.hpp"
#include "Http2SettingFrame.hpp"
#include "HttpPacketWriterImpl.hpp"
#include "NetProtocol.hpp"
#include "Http2DataFrame.hpp"

namespace obotcha {

_Http2StreamController::_Http2StreamController(OutputStream out) {
    mStatus = ShakeHand;
    mRingArray = createByteRingArray(st(Enviroment)::getInstance()->getInt(st(Enviroment)::gHttpBufferSize, 4 * 1024));
    shakeHandFrame = createHttp2ShakeHandFrame(mRingArray);
    mReader = createByteRingArrayReader(mRingArray);
    mBase64 = createBase64();
    mIndex = 0;

    encoder = createHPackEncoder();
    decoder = createHPackDecoder();
    mFrameParser = createHttp2FrameParser(mReader,decoder);
    
    mMutex = createMutex();
    streams = createHashMap<Integer,Http2Stream>();
    this->out = out;

    mSender = createHttp2StreamSender(out);
    mSender->start();
}

int _Http2StreamController::pushData(ByteArray data) {
    try {
        //printf("Http2StreamController,data size is %d \n",data->size());
        mRingArray->push(data);
    } catch (ArrayIndexOutOfBoundsException &e) {
        LOG(ERROR) << "Http2PacketParserImpl error ,data overflow";
        return -1;
    }

    return 0;
}

ArrayList<HttpPacket> _Http2StreamController::doParse() {
    ArrayList<HttpPacket> packets = createArrayList<HttpPacket>();
    //printf("Http2StreamController::doParse,status is %d length is %d \n",mStatus,mReader->getReadableLength());
    while(mReader->getReadableLength() > 9) {
        printf("Http2StreamController,doParse status is %d \n",mStatus);
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
                    data->dump("Http2StreamController http settings!!!");
                    //response get method
                    mStatus = Preface;
                } else if(header->getMethod() == st(HttpMethod)::Pri 
                    && packet->getEntity()->getContent()->toString()->equalsIgnoreCase("SM")) {
                    //printf("move to comunication \n");
                    mStatus = Comunicate;
                    //TODO
                    //mRingArray->reset();
                    //mReader->reset();
                    //we should send a http setting frame;
                    Http2SettingFrame ackFrame = createHttp2SettingFrame();
                    //TODO
                    ackFrame->setMaxFrameSize(128*1024);
                    ackFrame->setMaxConcurrentStreams(250);
                    ackFrame->setInitialWindowSize(128*1024);
                    ackFrame->setMaxHeaderListSize(250);
                    out->write(ackFrame->toFrameData());
                    //printf("rest size is %d \n",mRingArray->getStoredDataSize());

                    if(mRingArray->getStoredDataSize() != 0) {
                        mReader->setCursor(mRingArray->getStartIndex());
                        printf("mReadable size is %d \n",mReader->getReadableLength());
                        continue;
                    } else {
                        mRingArray->reset();
                    }
                }

                return nullptr;
            }
            break;

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
                    mStatus = Comunicate;
                    //we should send a http setting frame;
                    //mRingArray->reset();
                    Http2SettingFrame ackFrame = createHttp2SettingFrame();
                    int ret = out->write(ackFrame->toFrameData());
                    
                    if(mRingArray->getStoredDataSize() != 0) {
                        mReader->setCursor(mRingArray->getStartIndex());
                        //printf("mReadable size is %d \n",mReader->getReadableLength());
                        continue;
                    } else {
                        mRingArray->reset();
                    }
                    //printf("write ret is %d \n",ret);
                }
            }
            break;

            case Comunicate: {
                //printf("start comunication \n");
                ArrayList<Http2Frame> frames = mFrameParser->doParse();
                if(frames != nullptr && frames->size() != 0) {
                    ArrayList<HttpPacket> packets  = createArrayList<HttpPacket>();
                    auto iterator = frames->getIterator();
                    while(iterator->hasValue()) {
                        //we should check every frame to do some action
                        //only data/header frame should send user.
                        Http2Frame frame = iterator->getValue();
                        printf("frame id is %d,frame type is %d \n",frame->getStreamId(),frame->getType());
                        Http2Stream stream = streams->get(createInteger(frame->getStreamId()));
                        if(stream == nullptr) {
                            stream = newStream(frame->getStreamId());
                            streams->put(createInteger(frame->getStreamId()),stream);
                        }

                        stream->applyFrame(frame); //update stream status;

                        //HttpPacket p = stream->applyFrame(frame);
                        HttpPacket pack = nullptr;
                        if(frame->getType() == st(Http2Frame)::TypeData) {
                            Http2DataFrame dataFrame = Cast<Http2DataFrame>(frame);
                            pack = createHttp2Packet(frame->getStreamId(),stream->getHeader(),dataFrame->getData());
                        } else if(frame->getType() == st(Http2Frame)::TypeHeaders
                            && frame->isEndStream()) {
                            pack = createHttp2Packet(frame->getStreamId(),stream->getHeader(),nullptr);
                        }

                        if(pack != nullptr) {
                            packets->add(pack);
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

HttpPacket _Http2StreamController::parseEntireRequest(ByteArray request) {
    //TODO
    return nullptr;
}

void _Http2StreamController::reset() {

}

Http2Stream _Http2StreamController::newStream() {
    Http2Stream stream = createHttp2Stream(encoder,decoder,true,mSender);

    AutoLock l(mMutex);
    streams->put(createInteger(stream->getStreamId()),stream);
    return stream;
}

Http2Stream _Http2StreamController::newStream(uint32_t streamid) {
    Http2Stream stream = createHttp2Stream(encoder,decoder,(uint32_t)streamid,mSender);
    AutoLock l(mMutex);
    streams->put(createInteger(stream->getStreamId()),stream);
    return stream;
}

Http2Stream _Http2StreamController::getStream(uint32_t id) {
    AutoLock l(mMutex);
    return streams->get(createInteger(id));
}

}
