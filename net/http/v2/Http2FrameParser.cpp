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
#include "Http2DataFrame.hpp"
#include "Log.hpp"

namespace obotcha {

_Http2FrameParser::_Http2FrameParser(ByteRingArrayReader r,HPackDecoder d):mReader(r),decoder(d) {
}

ArrayList<Http2Frame> _Http2FrameParser::doParse() {
    ArrayList<Http2Frame> list = ArrayList<Http2Frame>::New();
    bool isComplete = false;
    while(!isComplete) {
        switch(status) {
            case _Http2FrameParser::Status::ParseHeadPart: {
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
                auto type = static_cast<st(Http2Frame)::Type>(mReader->pop()[0]);
    
                //flag
                mReader->move(1);
                uint32_t flags = mReader->pop()[0];
    
                //stream id
                mReader->move(4);
                data = mReader->pop();
                uint32_t streamid = data[0]<<24|data[1]<<16|data[2]<<8|data[3];
                //create frame
                switch(type) {
                    case st(Http2Frame)::Type::Data:
                       mCurrentFrame = Http2DataFrame::New();
                    break;
                    
                    case st(Http2Frame)::Type::Headers:
                        mCurrentFrame = Http2HeaderFrame::New(decoder);
                    break;

                    case st(Http2Frame)::Type::Priority:
                        mCurrentFrame = Http2PriorityFrame::New();
                    break;

                    case st(Http2Frame)::Type::RstStream:
                        mCurrentFrame = Http2RstFrame::New();
                    break;

                    case st(Http2Frame)::Type::Settings:
                        mCurrentFrame = Http2SettingFrame::New();
                    break;

                    case st(Http2Frame)::Type::PushPromise:
                        mCurrentFrame = Http2PushPromiseFrame::New(decoder);
                    break;

                    case st(Http2Frame)::Type::Ping:
                        mCurrentFrame = Http2PingFrame::New();
                    break;

                    case st(Http2Frame)::Type::GoAway:
                        mCurrentFrame = Http2GoAwayFrame::New();
                    break;

                    case st(Http2Frame)::Type::WindowUpdate:
                        mCurrentFrame = Http2WindowUpdateFrame::New();
                    break;

                    case st(Http2Frame)::Type::Continuation:
                        mCurrentFrame = Http2ContinuationFrame::New(decoder);
                    break;

                    default:
                        LOG(ERROR)<<"unknow frame type";
                    break;
                }

                mCurrentFrame->setLength(length);
                mCurrentFrame->setFlags(flags);
                mCurrentFrame->setStreamId(streamid);
                status = _Http2FrameParser::Status::ParsePayload;
                break;
            }

            case _Http2FrameParser::Status::ParsePayload: {
                size_t savedLength = (mCache == nullptr)?0:mCache->size();
                size_t readableLength = mReader->getReadableLength();
                size_t frameLength = mCurrentFrame->getLength();

                if(savedLength + readableLength >= frameLength) {
                    mReader->move(frameLength - savedLength);
                    ByteArray data = mReader->pop();
                    if(mCache == nullptr) {
                        mCache = data;
                    } else {
                        mCache->append(data);
                    }

                    if(mCache != nullptr && mCache->size() != 0) {
                        mCurrentFrame->load(mCache);
                    }

                    list->add(mCurrentFrame);
                    mCache = nullptr;
                    mCurrentFrame = nullptr;
                    status = _Http2FrameParser::Status::ParseHeadPart;
                } else {
                    mReader->move(readableLength);
                    ByteArray data = mReader->pop();
                    if(mCache == nullptr) {
                        mCache = data;
                    } else {
                        mCache->append(data);
                    }
                    isComplete = true;
                }
            }
            break;
        }
    }

    return list;
}


}
