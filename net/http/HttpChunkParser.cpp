#include "HttpChunkParser.hpp"
#include "HttpText.hpp"
#include "Log.hpp"
#include "Definations.hpp"

namespace obotcha {

/**
 * [chunk size][\r\n]
 * [chunk data][\r\n]
 * [chunk size][\r\n]
 * [chunk data][\r\n]
 * [chunk size = 0][\r\n]
 * [\r\n]
 * */
_HttpChunkParser::_HttpChunkParser(ByteRingArrayReader r):mReader(r) {
}

int _HttpChunkParser::calculateChunkSize(String lenString) const {
    const char *p = lenString->toChars();
    size_t size = lenString->size();
    size_t index = 0;
    for(;index < size;index++) {
        switch(p[index]) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case 'a':
            case 'A':
            case 'b':
            case 'B':
            case 'c':
            case 'C':
            case 'd':
            case 'D':
            case 'e':
            case 'E':
            case 'f':
            case 'F':
                break;
            
            default: {
                String len = createString(p,0,index);
                return len->toHexInt()->toValue();
            }
        }
    }
    return -1;
}

HttpChunk _HttpChunkParser::doParse() {
    byte v = 0;

    while (mReader->readNext(v) != st(Defination)::NoContentRead) {
        switch (mStatus) {
            case Idle: {
                if(endDetector->isEnd(v)) {
                    String chunklength = mReader->pop()->toString();
                    if (chunklength->size() <= 2) {
                        if(chunklength->equals(st(HttpText)::CRLF)) {
                            continue;
                        }
                        
                        // first two is /r/n,return direct
                        LOG(ERROR)<<"HttpChunkParser invalid content size";
                        return nullptr;
                    }
                    mChunkSize = calculateChunkSize(chunklength);
                    mStatus = (mChunkSize == 0)?RecvEnd:Recv;
                }
                continue;
            }

            case Recv: {
                int readablelength = mReader->getReadableLength();
                int popsize =
                    (readablelength > mChunkSize) ? mChunkSize - 1 : readablelength;
                
                mReader->move(popsize); 
                ByteArray data = mReader->pop();
                st(ByteArray)::Combine(currentBuff,data);
                mChunkSize -= (popsize + 1);//one byte already read by readNext
                if (mChunkSize == 0) {
                    mStatus = Idle;
                    continue;
                } 
                return nullptr;
            }

            case RecvEnd: {
                if(endDetector->isEnd(v)) {
                    mReader->pop();
                    mStatus = Idle;
                    auto rs = createHttpChunk(currentBuff);
                    currentBuff = nullptr;
                    return rs;
                } else if(v != '\r') {
                    //it is a tailing Header
                    mStatus = TrailingHeader;
                    continue;
                }
            } break;

            case TrailingHeader: {
                if(endDetector->isOnlyCRLF(v)) {
                    ByteArray tailingContent = mReader->pop();
                    ByteRingArray ringArray = createByteRingArray(tailingContent->size());
                    ringArray->push(tailingContent);
                    mHeaderParser = createHttpHeaderParser(createByteRingArrayReader(ringArray),
                                                           st(HttpHeaderParser)::ParseStatus::Header);
                    HttpHeader header = mHeaderParser->doParse();
                    if(header != nullptr) {
                        auto rs = createHttpChunk(currentBuff);
                        currentBuff = nullptr;
                        rs->setTrailingHeader(header);
                        mHeaderParser = nullptr;
                        mStatus = Idle;
                        return rs;
                    }
                }
                continue;
            }

            default:
                LOG(ERROR)<<"HttpChunkParser unknow status:"<<mStatus;
            break;
        }
    }

    return nullptr;
}

} // namespace obotcha
