#ifndef __OBOTCHA_HTTP_PRI_CONTENT_PARSER_HPP__
#define __OBOTCHA_HTTP_PRI_CONTENT_PARSER_HPP__

#include "Object.hpp"
#include "Byte.hpp"
#include "ByteRingArrayReader.hpp"

namespace obotcha {

DECLARE_CLASS(HttpPriContentParser) {
  public:
    explicit _HttpPriContentParser(ByteRingArrayReader);

    ByteArray doParse();

  private:
    bool isComplete(const byte &v);

    ByteArray mBuff = nullptr;

    ByteRingArrayReader mReader;

    int mCompleteIndex = 0;
};

} // namespace obotcha
#endif
