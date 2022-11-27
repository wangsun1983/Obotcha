#ifndef __OBOTCHA_HTTP_PRI_CONTENT_PARSER_HPP__
#define __OBOTCHA_HTTP_PRI_CONTENT_PARSER_HPP__

#include "Object.hpp"
#include "Byte.hpp"
#include "ByteRingArrayReader.hpp"

namespace obotcha {

DECLARE_CLASS(HttpPriContentParser) {
  public:
    _HttpPriContentParser(ByteRingArrayReader);

    ByteArray doParse();

  private:
    bool isComplete(byte &v);

    ByteArray mBuff;

    ByteRingArrayReader mReader;

    int mCompleteIndex;
};

} // namespace obotcha
#endif
