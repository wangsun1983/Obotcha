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

ByteArray _HttpChunkParser::doParse() {
    byte v = 0;

    while (mReader->readNext(v) != st(ByteRingArrayReader)::NoContent) {
        switch (mStatus) {
            case Idle: {
                if(endDetector->isEnd(v)) {
                    String chunklength = mReader->pop()->toString();
                    if (chunklength->size() <= 2) {
                        // first two is /r/n,return direct
                        LOG(ERROR)<<"HttpChunkParser invalid content size";
                        return nullptr;
                    }

                    chunklength = chunklength->subString(0, chunklength->size() - 2);
                    mChunkSize = chunklength->toHexInt()->toValue();
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
                    (readablelength > mChunkSize) ? mChunkSize : readablelength;
                
                mReader->move(popsize - 1); //one byte already read by readNext
                ByteArray data = mReader->pop();
                if (currentBuff == nullptr) {
                    currentBuff = data;
                } else {
                    currentBuff->append(data);
                }

                mChunkSize -= popsize;
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
                    auto rs = currentBuff;
                    currentBuff = nullptr;
                    return rs;
                }
                break;
            }
        }
    }

    return nullptr;
}

} // namespace obotcha
