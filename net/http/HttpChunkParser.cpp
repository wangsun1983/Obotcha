#include "HttpChunkParser.hpp"
#include "HttpText.hpp"

namespace obotcha {

/*
HTTP/1.1 200 OK
Content-Type: text/plain
Transfer-Encoding: chunked

25 => (37个字符，包含有"\r\n")
This is the data in the first chunk

1C => (28个字符，包含有"\r\n")
and this is the second one

3
con

8
sequence

0 => ("0\r\n\r\n")
*/
_HttpChunkParser::_HttpChunkParser(ByteRingArrayReader r) {
    mChunkSize = -1;
    mStatus = Idle;
    mCRLFIndex = 0;
    mReader = r;
    mBuff = nullptr;
}

bool _HttpChunkParser::isLineEnd(byte &v) {
    if(v == '\r' && mCRLFIndex == 0) {
        mCRLFIndex = 1;
    } else if(v == '\n' && mCRLFIndex == 1) {
        mCRLFIndex = 0;
        return true;
    } else {
        mCRLFIndex = 0;
    }

    return false;
}

ByteArray _HttpChunkParser::doParse() {
    static byte *CRLF = (byte *)st(HttpText)::CRLF->toChars();
    byte v = 0;

    while (mReader->readNext(v) != st(ByteRingArrayReader)::NoContent) {
        // printf("v is %x,status is %d \n",v,mStatus);
        switch (mStatus) {
            case Idle: {
                if(isLineEnd(v)) {
                    String chunklength = mReader->pop()->toString();
                    if (chunklength->size() == 2) {
                        // first two is /r/n,return direct
                        return nullptr;
                    }

                    chunklength = chunklength->subString(0, chunklength->size() - 2);
                    mChunkSize = chunklength->toHexInt()->toValue();
                    if (mChunkSize == 0) {
                        printf("chunck get finished!!!!");
                        return mBuff;
                    }
                    mStatus = Recv;
                    printf("i get chunksize is %d \n",mChunkSize);
                }
                continue;
            }

            case Recv: {
                int readablelength = mReader->getReadableLength();
                int popsize =
                    (readablelength > mChunkSize) ? mChunkSize : readablelength;
                printf("popsize is %d \n",popsize);

                mReader->move(popsize - 1); //one byte already read by readNext
                ByteArray data = mReader->pop();
                // printf("recv ...... data is %s \n",data->toString()->toChars());
                if (mBuff == nullptr) {
                    mBuff = data;
                } else {
                    mBuff->append(data);
                }

                mChunkSize -= popsize;
                printf("after mChunkSize is %d \n",mChunkSize);

                if (mChunkSize == 0) {
                    mStatus = RecvEnd;
                    continue;
                } else {
                    return nullptr;
                }

                break;
            }

            case RecvEnd: {
                if(isLineEnd(v)) {
                    mReader->pop();
                    mStatus = Idle;
                }
                break;
            }
        }
    }

    return nullptr;
}

} // namespace obotcha
