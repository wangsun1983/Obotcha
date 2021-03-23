#include "HttpResponseParser.hpp"
#include "ArrayList.hpp"
#include "HttpContentType.hpp"
#include "HttpXFormUrlEncodedParser.hpp"

namespace obotcha {

_HttpResponseParser::_HttpResponseParser() {
    mBuff = createByteRingArray(st(Enviroment)::getInstance()->getInt(st(Enviroment)::gHttpBufferSize,64*1024));
    mReader = createByteRingArrayReader(mBuff);
    mStatus = Idle;
    mChunkParser = nullptr;
    mHttpHeaderParser = nullptr;
}

void _HttpResponseParser::pushHttpData(ByteArray data) {
    //write data
#ifdef DUMP_HTTP_DATE\
    File dumpfile = createFile("data.dt");
    //dumpfile->removeAll();
    dumpfile->createNewFile();
    FileOutputStream stream = createFileOutputStream(dumpfile);
    stream->open();
    stream->write(data);
    stream->flush();
#endif
    mBuff->push(data);
}

ArrayList<HttpPacket> _HttpResponseParser::doParse() {
    ArrayList<HttpPacket> packets = createArrayList<HttpPacket>();
    while(1) {
        switch(mStatus) {
            case Idle:{
                if(mHttpHeaderParser == nullptr) {
                    mHttpHeaderParser = createHttpHeaderParser(mReader);
                    mHttpPacket = createHttpPacket();
                }
                HttpHeader header = mHttpHeaderParser->doParse();
                if(header == nullptr) {
                    return packets;
                }
                
                mHttpPacket->setHeader(header);
                mStatus = Body;
                mHttpHeaderParser = nullptr;
                continue;
            }
            
            case Body: {
                //check whether there is a multipart
                String contentlength = mHttpPacket->getHeader()->getValue(st(HttpHeader)::ContentLength);
                String contenttype = mHttpPacket->getHeader()->getValue(st(HttpHeader)::ContentType);
                String encodingtype = mHttpPacket->getHeader()->getValue(st(HttpHeader)::TransferEncoding);
                
                if(encodingtype != nullptr && encodingtype->equalsIgnoreCase(st(HttpHeader)::TransferChunked)) {
                    //this is a chunck parsesr
                    if(mChunkParser == nullptr) {
                        mChunkParser = createHttpChunkParser(mReader);
                    }
                    ByteArray data = mChunkParser->doParse();
                    if(data != nullptr) {
                        mHttpPacket->getEntity()->setContent(data);
                        packets->add(mHttpPacket);
                        mChunkParser = nullptr;
                        mStatus = Idle;
                    }
                    continue;
                }

                if(contentlength == nullptr) {
                    //no contentlength,maybe it is only a html request
                    packets->add(mHttpPacket);
                    mStatus = Idle;
                    continue;
                }
                
                int length = contentlength->toBasicInt();
                if(length <= mReader->getReadableLength()) {
                    //one packet get
                    mReader->move(length);
                    ByteArray content = mReader->pop();
                    //check whether it is a X-URLEncoded
                    if(st(HttpContentType)::XFormUrlEncoded->indexOfIgnoreCase(contenttype) >= 0) {
                        ArrayList<KeyValuePair<String,String>> xFormEncodedPair = st(HttpXFormUrlEncodedParser)::parse(content->toString());
                        mHttpPacket->getEntity()->setEncodedKeyValues(xFormEncodedPair);
                    } else {
                        mHttpPacket->getEntity()->setContent(content);
                    }
                    mStatus = Idle;
                    packets->add(mHttpPacket);
                    printf("BodyStart add packet \n");
                    continue;
                }
            }
            break;
        }
    }
    return packets;
}

int _HttpResponseParser::getStatus() {
    return mStatus;
}

HttpPacket _HttpResponseParser::parseEntireResponse(String response) {
    mBuff->reset();
    mBuff->push((byte *)response->toChars(),0,response->size());
    ArrayList<HttpPacket> result = doParse();
    if(result == nullptr || result->size() != 1) {
        return nullptr;
    }

    return result->get(0);
}

}
