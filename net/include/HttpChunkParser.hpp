#ifndef __OBOTCHA_HTTP_CHUNK_PARSER_HPP__
#define __OBOTCHA_HTTP_CHUNK_PARSER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Pipe.hpp"
#include "Mutex.hpp"
#include "HttpMultiPart.hpp"
#include "ByteRingArrayReader.hpp"
#include "Enviroment.hpp"
#include "FileOutputStream.hpp"
#include "HttpFile.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpChunkParser) {
public:
    _HttpChunkParser(ByteRingArrayReader);

    ByteArray doParse();

private:
    enum ParseStatus {
        Idle = 0,
        Recv,
        RecvEnd,
        End
    };
    
    int mChunkSize;
    int mStatus;
    int mChunkEndCount;
    ByteArray mBuff;
    ByteRingArrayReader mReader;
};

}
#endif
