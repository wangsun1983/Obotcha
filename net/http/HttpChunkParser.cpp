#include "HttpChunkParser.hpp"
#include "HttpText.hpp"
#include "Log.hpp"

namespace obotcha {

/**
 * [chunk size][\r\n]
 * [chunk data][\r\n]
 * [chunk size][\r\n]
 * [chunk data][\r\n]
 * [chunk size = 0][\r\n]
 * [\r\n]
 * */
_HttpChunkParser::_HttpChunkParser(ByteRingArrayReader r) {
    mChunkSize = -1;
    mStatus = Idle;
    endDetector = createCRLFDetector();
    mReader = r;
    currentBuff = nullptr;
}

int _HttpChunkParser::calculateChunkSize(String lenString) {
    const char *p = lenString->toChars();
    int size = lenString->size();
    int index = 0;
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
                break;
        }
    }
    return -1;
}

HttpChunk _HttpChunkParser::doParse() {
    byte v = 0;

    while (mReader->readNext(v) != st(ByteRingArrayReader)::NoContent) {
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

                    //chunklength = chunklength->subString(0, chunklength->size() - 2);
                    mChunkSize = calculateChunkSize(chunklength); //chunklength->toHexInt()->toValue();
                    if (mChunkSize == 0) {
                        //finish chunk parse
                        mStatus = RecvEnd;
                    } else {
                        mStatus = Recv;
                    }
                }
                continue;
            }

            case Recv: {
                int readablelength = mReader->getReadableLength();
                int popsize =
                    (readablelength > mChunkSize) ? mChunkSize - 1 : readablelength;
                
                mReader->move(popsize); 
                ByteArray data = mReader->pop();
                if (currentBuff == nullptr) {
                    currentBuff = data;
                } else {
                    currentBuff->append(data);
                }

                mChunkSize -= (popsize + 1);//one byte already read by readNext
                if (mChunkSize == 0) {
                    mStatus = Idle;
                    continue;
                } else {
                    return nullptr;
                }

                break;
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
                break;
            }

            case TrailingHeader: {
                if(endDetector->isOnlyCRLF(v)) {
                    ByteArray tailingContent = mReader->pop();
                    ByteRingArray ringArray = createByteRingArray(tailingContent->size());
                    ringArray->push(tailingContent);

                    mHeaderParser = createHttpHeaderParser(createByteRingArrayReader(ringArray),st(HttpHeaderParser)::Header);
                    
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
        }
    }

    return nullptr;
}

} // namespace obotcha
