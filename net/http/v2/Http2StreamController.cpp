#include "Http2StreamController.hpp"
#include "Http2Frame.hpp"
#include "Log.hpp"
#include "AutoLock.hpp"

namespace obotcha {

_Http2StreamController::_Http2StreamController() {
    mStatus = ShakeHand;
    mRingArray = createByteRingArray(st(Enviroment)::getInstance()->getInt(st(Enviroment)::gHttpBufferSize, 4 * 1024));
    shakeHandFrame = createHttp2ShakeHandFrame(mRingArray);
    mReader = createByteRingArrayReader(mRingArray);
    mFrameParser = createHttp2FrameParser(mReader,decoder);
    mIndex = 0;

    encoder = createHPackEncoder();
    decoder = createHPackDecoder();
    mMutex = createMutex();
    streams = createHashMap<Integer,Http2Stream>();
}

int _Http2StreamController::pushHttpData(ByteArray data) {
    try {
        printf("push data,size is %d,\n",data->size());
        mRingArray->push(data);
    } catch (ArrayIndexOutOfBoundsException &e) {
        LOG(ERROR) << "Http2PacketParserImpl error ,data overflow";
        return -1;
    }

    return 0;
}

ArrayList<HttpPacket> _Http2StreamController::doParse() {
    ArrayList<HttpPacket> packets = createArrayList<HttpPacket>();
    while(mReader->getReadableLength() > 9) {
        switch(mStatus) {
            case ShakeHand:{
                ArrayList<HttpPacket> packets = shakeHandFrame->doParser();
                if(packets->size() > 1) {
                    LOG(ERROR)<<"HttpV2 parse shake message size > 1";
                    return nullptr;
                }
                mStatus = Preface;
                mRingArray->reset();
                //mReader->reset();
                return packets;
            }
            break;

            case Preface:{
                printf("preface start parse \n");
                byte v = 0;
                const char *p = st(Http2ShakeHandFrame)::PreFace->toChars();
                int size = st(Http2ShakeHandFrame)::PreFace->size();
                while(mReader->readNext(v) == st(ByteRingArrayReader)::Continue) {
                    if(v != p[mIndex] || mIndex == size - 1) {
                        break;
                    }
                    mIndex++;
                }
                printf("mIndex is %d,size is %d \n",mIndex,size);
                if(mIndex == size - 1) {
                    mIndex = 0;
                    mStatus = Comunicated;
                    mReader->pop();
                }
            }
            break;

            case Comunicated: {
                printf("Comunicated start \n");
                ArrayList<Http2Frame> frames = mFrameParser->doParse();
                printf("Comunicated trace frames size is %d \n",frames->size());
                if(frames != nullptr && frames->size() != 0) {
                    ArrayList<HttpPacket> packets  = createArrayList<HttpPacket>();
                    auto iterator = frames->getIterator();
                    while(iterator->hasValue()) {
                        //we should check every frame to do some action
                        //only data/header frame should send user.
                        Http2Frame frame = iterator->getValue();
                        Http2Stream stream = streams->get(createInteger(frame->getStreamId()));
                        //TODO
                        HttpPacket p = stream->applyFrame(frame);
                        if(p != nullptr) {
                            packets->add(p);
                        }
                        //if(stream->applyFrame(frame)) {
                        //    Http2Packet p = createHttp2Packet();
                            //p->setFrame(frame);
                        //    packets->add(p);
                        //   iterator->next();
                        //}
                    }
                    return packets;
                }
            }
            break;
        }
    }

    return nullptr;
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



}
