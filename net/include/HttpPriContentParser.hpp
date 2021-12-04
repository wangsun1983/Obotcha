#ifndef __OBOTCHA_HTTP_PRI_CONTENT_PARSER_HPP__
#define __OBOTCHA_HTTP_PRI_CONTENT_PARSER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ByteRingArrayReader.hpp"
#include "Enviroment.hpp"
#include "FileOutputStream.hpp"
#include "HttpMultiPart.hpp"
#include "Mutex.hpp"
#include "Pipe.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpPriContentParser) {
  public:
    _HttpPriContentParser(ByteRingArrayReader);

    ByteArray doParse();

  private:
    bool isComplete(byte &v);

    ByteArray mBuff;

    ByteRingArrayReader mReader;

    int completeIndex;
};

} // namespace obotcha
#endif
