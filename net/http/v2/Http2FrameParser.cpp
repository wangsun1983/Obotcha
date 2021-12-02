#include "Http2FrameParser.hpp"
#include "ByteArrayReader.hpp"
#include "Http2Frame.hpp"
#include "Http2SettingFrame.hpp"

namespace obotcha {


_Http2FrameParser::_Http2FrameParser(ByteRingArrayReader r) {
    mReader = r;
}

ArrayList<Http2Frame> _Http2FrameParser::doParse() {
    ArrayList<Http2Frame> list = createArrayList<Http2Frame>();
    bool isComplete = false;

    while(!isComplete) {
        switch(status) {
            case ParseHeadPart: {
                if(mReader->getReadableLength() < 9) {
                    isComplete = true;
                    break;
                }

                //read length
                mReader->move(3);
                ByteArray data = mReader->pop();
                uint32_t length = data[0]<<16|data[1]<<8|data[2]; //big endian

                //read type
                mReader->move(1);
                uint32_t type = mReader->pop()[0];

                //flag
                mReader->move(1);
                uint32_t flags = mReader->pop()[0];

                //stream id
                mReader->move(4);
                data = mReader->pop();
                uint32_t streamid = data[0]<<24|data[1]<<16|data[2]<<8|data[3];

                //create frame
                switch(type) {
                    case st(Http2Frame)::TypeData:
                    //TODO
                    break;
                    
                    case st(Http2Frame)::TypeHeaders:
                    //TODO
                    break;

                    case st(Http2Frame)::TypePriority:
                    //TODO
                    break;

                    case st(Http2Frame)::TypeRstStream:
                    //TODO
                    break;

                    case st(Http2Frame)::TypeSettings:
                        mFrame = createHttp2SettingFrame();
                    break;

                    case st(Http2Frame)::TypePushPromise:
                    //TODO
                    break;

                    case st(Http2Frame)::TypePing:
                    //TODO
                    break;

                    case st(Http2Frame)::TypeGoAway:
                    //TODO
                    break;

                    case st(Http2Frame)::TypeWindowUpdate:
                    //TODO
                    break;

                    case st(Http2Frame)::TypeContinuation:
                    //TODO
                    break;
                }

                mFrame->setLength(length);
                mFrame->setFlags(flags);
                if(length == 0) {
                    //there is no payload!!!,save it to http pack
                }
                break;
            }

            case ParsePayload:
            break;
        }
    }

    return list;
}


}
