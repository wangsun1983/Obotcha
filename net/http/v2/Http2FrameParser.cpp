#include "Http2FrameParser.hpp"
#include "ByteArrayReader.hpp"
#include "Http2Frame.hpp"
#include "Http2SettingFrame.hpp"
#include "Http2WindowUpdateFrame.hpp"
#include "Http2HeaderFrame.hpp"
#include "Http2RstFrame.hpp"
#include "Http2PriorityFrame.hpp"
#include "Http2PushPromiseFrame.hpp"
#include "Http2PingFrame.hpp"
#include "Http2GoAwayFrame.hpp"
#include "Http2ContinuationFrame.hpp"

namespace obotcha {

_Http2FrameParser::_Http2FrameParser(ByteRingArrayReader r,HPackDecoder d) {
    mReader = r;
    mCurrentFrame = nullptr;
    mCache = nullptr;
    status = ParseHeadPart;

    decoder = d;
}

ArrayList<Http2Frame> _Http2FrameParser::doParse() {
    ArrayList<Http2Frame> list = createArrayList<Http2Frame>();
    bool isComplete = false;
    printf("http2frame doParse \n");
    while(!isComplete) {
        printf("http2frame status is %d \n",status);
        switch(status) {
            case ParseHeadPart: {
                if(mReader->getReadableLength() < 9) {
                    isComplete = true;
                    break;
                }

                //read length
                mReader->move(3);
                ByteArray data = mReader->pop();
                printf("data[0] is %x,data[1] is %x,data[2] is %x",data[0],data[1],data[2]);
                uint32_t length = data[0]<<16|data[1]<<8|data[2]; //big endian
                printf("parse length is %x \n",length);
                //read type
                mReader->move(1);
                uint32_t type = mReader->pop()[0];
                printf("parse type is %d \n",type);

                //flag
                mReader->move(1);
                uint32_t flags = mReader->pop()[0];
                printf("parse flags is %d \n",flags);

                //stream id
                mReader->move(4);
                data = mReader->pop();
                uint32_t streamid = data[0]<<24|data[1]<<16|data[2]<<8|data[3];
                printf("streamid is %d \n",streamid);

                //create frame
                switch(type) {
                    case st(Http2Frame)::TypeData:
                    //TODO
                    break;
                    
                    case st(Http2Frame)::TypeHeaders:
                        mCurrentFrame = createHttp2HeaderFrame(decoder);
                    break;

                    case st(Http2Frame)::TypePriority:
                        mCurrentFrame = createHttp2PriorityFrame();
                    break;

                    case st(Http2Frame)::TypeRstStream:
                        mCurrentFrame = createHttp2RstFrame();
                    break;

                    case st(Http2Frame)::TypeSettings:
                        mCurrentFrame = createHttp2SettingFrame();
                    break;

                    case st(Http2Frame)::TypePushPromise:
                        mCurrentFrame = createHttp2PushPromiseFrame(decoder);
                    break;

                    case st(Http2Frame)::TypePing:
                        mCurrentFrame = createHttp2PingFrame();
                    break;

                    case st(Http2Frame)::TypeGoAway:
                        mCurrentFrame = createHttp2GoAwayFrame();
                    break;

                    case st(Http2Frame)::TypeWindowUpdate:
                        mCurrentFrame = createHttp2WindowUpdateFrame();
                    break;

                    case st(Http2Frame)::TypeContinuation:
                        mCurrentFrame = createHttp2ContinuationFrame(decoder);
                    break;
                }

                mCurrentFrame->setLength(length);
                mCurrentFrame->setFlags(flags);
                mCurrentFrame->setStreamId(streamid);
                if(length == 0) {
                    //there is no payload!!!,save it to http pack
                    list->add(mCurrentFrame);
                    mCurrentFrame = nullptr;
                    continue;
                }

                status = ParsePayload;
                break;
            }

            case ParsePayload: {
                int rest = (mCache == nullptr)?mCurrentFrame->getLength():mCurrentFrame->getLength() - mCache->size();
                printf("rest is %d ,readable length is %d \n",rest,mReader->getReadableLength());
                if(rest > mReader->getReadableLength()) {
                    //we should save bytearray;
                    mReader->move(mReader->getReadableLength());
                    ByteArray data = mReader->pop();
                    if(mCache == nullptr) {
                        mCache = data;
                    } else {
                        mCache->append(data);
                    }
                    isComplete = true;
                } else {
                    mReader->move(rest);
                    ByteArray data = mReader->pop();
                    if(mCache == nullptr) {
                        mCache = data;
                    } else {
                        mCache->append(data);
                    }
                    
                    mCurrentFrame->import(mCache);
                    list->add(mCurrentFrame);
                    mCache = nullptr;
                    mCurrentFrame = nullptr;
                    status = ParseHeadPart;
                }
            }
            break;
        }
    }

    return list;
}


}
