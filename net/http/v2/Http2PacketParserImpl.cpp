#include "Http2PacketParserImpl.hpp"
#include "Http2ShakeHandFrame.hpp"
#include "Enviroment.hpp"
#include "Log.hpp"

namespace obotcha {

_Http2PacketParserImpl::_Http2PacketParserImpl() {
    mStatus = ShakeHand;
    mRingArray = createByteRingArray(st(Enviroment)::getInstance()->getInt(st(Enviroment)::gHttpBufferSize, 4 * 1024));
    shakeHandFrame = createHttp2ShakeHandFrame(mRingArray);
    mReader = createByteRingArrayReader(mRingArray);
    mFrameParser = createHttp2FrameParser(mReader);
    mIndex = 0;
}

int _Http2PacketParserImpl::pushHttpData(ByteArray data) {
    try {
        printf("push data,size is %d,\n",data->size());
        mRingArray->push(data);
    } catch (ArrayIndexOutOfBoundsException &e) {
        LOG(ERROR) << "Http2PacketParserImpl error ,data overflow";
        return -1;
    }

    return 0;
}

ArrayList<HttpPacket> _Http2PacketParserImpl::doParse() {
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
            printf("available size is %d \n",mReader->getReadableLength());
            while(mReader->readNext(v) == st(ByteRingArrayReader)::Continue) {
                printf("preface parse trace1,v is %c,p is %c \n",v,p[mIndex]);
                if(v != p[mIndex] || mIndex == size) {
                    break;
                }
                mIndex++;
            }
            printf("available size is %d \n",mReader->getReadableLength());
            if(mIndex == size) {
                return createArrayList<HttpPacket>();
            }

            //TODO
            mIndex = 0;
        }
        break;

        case Comunicated: {
            ArrayList<Http2Frame> frames = mFrameParser->doParse();
            if(frames != nullptr && frames->size() != 0) {
                ArrayList<HttpPacket> packets  = createArrayList<HttpPacket>();
                auto iterator = frames->getIterator();
                while(iterator->hasValue()) {
                    HttpPacket p = createHttpPacket();
                    p->setFrame(iterator->getValue());
                    packets->add(p);
                    iterator->next();
                }
                return packets;
            }
        }
        break;
    }

    return nullptr;
}

HttpPacket _Http2PacketParserImpl::parseEntireRequest(ByteArray request) {
    return nullptr;
}

void _Http2PacketParserImpl::reset() {

}

} // namespace obotcha
