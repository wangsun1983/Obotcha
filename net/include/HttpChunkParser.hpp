#ifndef __OBOTCHA_HTTP_CHUNK_PARSER_HPP__
#define __OBOTCHA_HTTP_CHUNK_PARSER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ByteRingArrayReader.hpp"
#include "Enviroment.hpp"
#include "FileOutputStream.hpp"
#include "HttpMultiPart.hpp"
#include "Mutex.hpp"
#include "Pipe.hpp"
#include "String.hpp"
#include "CRLFDetector.hpp"

namespace obotcha {

DECLARE_CLASS(HttpChunkParser) {
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

    ByteArray currentBuff;
    ByteRingArrayReader mReader;
    CRLFDetector endDetector;
};

} // namespace obotcha
#endif
