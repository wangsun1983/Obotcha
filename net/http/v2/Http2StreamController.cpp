#include "Http2StreamController.hpp"
#include "Http2Frame.hpp"
#include "Log.hpp"
#include "AutoLock.hpp"

#include "Http2SettingFrame.hpp"
#include "HttpPacketWriterImpl.hpp"
#include "HttpProtocol.hpp"
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
}

int _Http2StreamController::pushHttpData(ByteArray data) {
    try {
        printf("Http2StreamController push data,size is %d,\n",data->size());
        mRingArray->push(data);
    } catch (ArrayIndexOutOfBoundsException &e) {
        LOG(ERROR) << "Http2PacketParserImpl error ,data overflow";
        return -1;
    }

    return 0;
}

ArrayList<HttpPacket> _Http2StreamController::doParse() {
    ArrayList<HttpPacket> packets = createArrayList<HttpPacket>();
    printf("Http2StreamController doParse\n");
    while(mReader->getReadableLength() > 9) {
        switch(mStatus) {
            case ShakeHand:{
                printf("Http2StreamController doParse ShakeHand start\n");
                ArrayList<HttpPacket> packets = shakeHandFrame->doParser();
                if(packets->size() > 1) {
                    LOG(ERROR)<<"HttpV2 parse shake message size > 1";
                    return nullptr;
                }
                //start shake hand
                HttpPacket packet = packets->get(0);
                HttpHeader header = packet->getHeader();
                if(header->getMethod() == st(HttpMethod)::Get
                    && header->getUpgrade()->toString()->equals("h2c")) {
                    //we should decode it's setting frame
                    String settingframe = header->get("http2-settings");
                    printf("Http2StreamController settingframe is %s \n",settingframe->toChars());
                    ByteArray data = mBase64->decodeBase64Url(settingframe->toByteArray());
                    data->dump("Http2StreamController http settings!!!");
                    //TEST
                    Http2SettingFrame frame = createHttp2SettingFrame();
                    frame->import(data);

                    HttpPacketWriterImpl impl = createHttpPacketWriterImpl(out);
                    auto shakeHande = createHttp2ShakeHandFrame();
                    int ret = impl->write(shakeHande->toShakeHandPacket(st(HttpProtocol)::Http_H2));
                    printf("Http2StreamController ret is %d \n",ret);
                    data->dump("Http2StreamController http settings!!!");
                    //response get method
                    mStatus = Preface;
                } else if(header->getMethod() == st(HttpMethod)::Pri 
                    && packet->getEntity()->getContent()->toString()->equalsIgnoreCase("SM")) {
                    mStatus = Comunicate;
                    mRingArray->reset();
                    //we should send a http setting frame;
                    Http2SettingFrame ackFrame = createHttp2SettingFrame();
                    out->write(ackFrame->toFrameData());
                }

                return nullptr;
            }
            break;

            case Preface:{
                printf("Http2StreamController Preface start \n");
                ArrayList<HttpPacket> packets = shakeHandFrame->doParser();
                if(packets->size() > 1) {
                    LOG(ERROR)<<"HttpV2 parse Preface size > 1";
                    return nullptr;
                }
                printf("Http2StreamController Preface trace1 \n");
                HttpPacket packet = packets->get(0);
                HttpHeader header = packet->getHeader();
                if(header->getMethod() == st(HttpMethod)::Pri 
                    && packet->getEntity()->getContent()->toString()->equalsIgnoreCase("SM")) {
                    mStatus = Comunicate;
                    //we should send a http setting frame;
                    mRingArray->reset();
                    Http2SettingFrame ackFrame = createHttp2SettingFrame();
                    out->write(ackFrame->toFrameData());
                }
                printf("Http2StreamController Preface trace2 \n");
            }
            break;

            case Comunicate: {
                printf("Http2StreamController Comunicated start \n");
                ArrayList<Http2Frame> frames = mFrameParser->doParse();
                printf("Http2StreamController Comunicated trace frames size is %d \n",frames->size());
                if(frames != nullptr && frames->size() != 0) {
                    ArrayList<HttpPacket> packets  = createArrayList<HttpPacket>();
                    auto iterator = frames->getIterator();
                    while(iterator->hasValue()) {
                        //we should check every frame to do some action
                        //only data/header frame should send user.
                        Http2Frame frame = iterator->getValue();
                        printf("Http2StreamController frame type is %d,streamid is %d \n",frame->getType(),frame->getStreamId());
                        Http2Stream stream = streams->get(createInteger(frame->getStreamId()));
                        if(stream == nullptr) {
                            stream = newStream(frame->getStreamId());
                        }

                        stream->applyFrame(frame); //update stream status;

                        //HttpPacket p = stream->applyFrame(frame);
                        HttpPacket pack = nullptr;
                        if(frame->getType() == st(Http2Frame)::TypeData) {
                            Http2DataFrame dataFrame = Cast<Http2DataFrame>(frame);
                            pack = createHttp2Packet(frame->getStreamId(),stream->getHeader(),dataFrame->getData());
                        } else if(frame->getType() == st(Http2Frame)::TypeHeaders) {
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
    Http2Stream stream = createHttp2Stream(encoder,decoder);
    AutoLock l(mMutex);
    streams->put(createInteger(stream->getStreamId()),stream);
    return stream;
}

Http2Stream _Http2StreamController::newStream(uint32_t streamid) {
    Http2Stream stream = createHttp2Stream(encoder,decoder,streamid);
    AutoLock l(mMutex);
    streams->put(createInteger(stream->getStreamId()),stream);
    return stream;
}

Http2Stream _Http2StreamController::getStream(uint32_t id) {
    AutoLock l(mMutex);
    return streams->get(createInteger(id));
}

}