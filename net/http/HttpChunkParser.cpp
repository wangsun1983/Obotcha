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
    byte v = 0;

    while(mReader->readNext(v) != st(ByteRingArrayReader)::NoContent) {
        //printf("v is %x,status is %d \n",v,mStatus);
        switch(mStatus) {
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
                    if(chunklength->size() == 2) {
                        //first two is /r/n,return direct
                        return nullptr;
                    }

                    chunklength = chunklength->subString(0,chunklength->size() - 2);
                    mChunkSize = chunklength->toHexInt();
                    if(mChunkSize == 0) {
                        mChunkEndCount = 0;
                        return mBuff;
                    }
                    mStatus = Recv;
                }
            }
            
            case Recv: {
                int readablelength = mReader->getReadableLength();
                int popsize = (readablelength > mChunkSize)?mChunkSize:readablelength;

                mReader->move(popsize);
                ByteArray data = mReader->pop();
                //printf("recv ...... data is %s \n",data->toString()->toChars());
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
