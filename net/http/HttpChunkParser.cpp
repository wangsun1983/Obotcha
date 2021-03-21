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
    mChunkEndCount = 0;
    mReader = r;
    mBuff = nullptr;
}

ByteArray _HttpChunkParser::doParse() {
    static byte* CRLF = (byte*)st(HttpText)::CRLF->toChars();
    //static byte* END = (byte*)st(HttpText)::HttpEnd->toChars();
    byte v = 0;

    while(mReader->readNext(v) != ByteRingArrayReadComplete) {
        switch(mStatus) {
            case End: {
                printf("end mChunkEndCount is %d,v is %d \n",mChunkEndCount,v);
                if(v == CRLF[mChunkEndCount]) {
                    mChunkEndCount++;
                } else {
                    mChunkEndCount = 0;
                }

                if(mChunkEndCount == 2) {
                    return mBuff;
                } else {
                    continue;
                }

                break;
            }

            case Idle: {
                if(v == CRLF[mChunkEndCount]) {
                    mChunkEndCount++;
                } else {
                    mChunkEndCount = 0;
                }

                if(mChunkEndCount != 2) {
                    continue;
                } else {
                    mChunkEndCount = 0;
                    String chunklength = mReader->pop()->toString();
                    chunklength = chunklength->subString(0,chunklength->size() - 2);
                    printf("chunklength str is %s \n",chunklength->toChars());
                    mChunkSize = chunklength->toHexInt();
                    printf("mChunkSize is %d \n",mChunkSize);
                    if(mChunkSize == 0) {
                        mStatus = End;
                        continue;
                    }
                    mStatus = Recv;
                }
            }
            
            case Recv: {
                int readablelength = mReader->getReadableLength();
                int popsize = (readablelength > mChunkSize)?mChunkSize:readablelength;

                mReader->move(popsize);
                ByteArray data = mReader->pop();
                printf("data size is %d,mChunkSize is %d,popsize is %d \n",data->size(),mChunkSize,popsize);
                if(mBuff == nullptr) {
                    mBuff = data;
                } else {
                    mBuff->append(data);
                }

                mChunkSize -= popsize;
                if(mChunkSize == 0) {
                    mStatus = RecvEnd;
                    continue;
                } else {
                    return nullptr;
                }

                break;
            }

            case RecvEnd:{
                if(v == CRLF[mChunkEndCount]) {
                    mChunkEndCount++;
                } else {
                    mChunkEndCount = 0;
                }

                if(mChunkEndCount != 2) {
                    continue;
                }

                mChunkEndCount = 0;
                mReader->pop();
                mStatus = Idle;
                break;
            }
        } 
    }

    return nullptr;
}



}
