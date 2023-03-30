#ifndef __OBOTCHA_HTTP_CHUNK_PARSER_HPP__
#define __OBOTCHA_HTTP_CHUNK_PARSER_HPP__

#include "Object.hpp"
#include "ByteRingArrayReader.hpp"
#include "String.hpp"
#include "CRLFDetector.hpp"
#include "HttpChunk.hpp"
#include "HttpHeaderParser.hpp"

namespace obotcha {

DECLARE_CLASS(HttpChunkParser) {
public:
    _HttpChunkParser(ByteRingArrayReader);
    HttpChunk doParse();

private:
    enum ParseStatus { 
      Idle = 0, 
      Recv, 
      RecvEnd,
      TrailingHeader,
      End 
    };

    int mChunkSize;
    int mStatus;
    ByteArray currentBuff;
    ByteRingArrayReader mReader;
    CRLFDetector endDetector;
    HttpHeaderParser mHeaderParser;

    int calculateChunkSize(String);

};

} // namespace obotcha
#endif
