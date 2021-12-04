#include "HttpPriContentParser.hpp"

namespace obotcha {

_HttpPriContentParser::_HttpPriContentParser(ByteRingArrayReader r) {
  completeIndex = 0;
  mReader = r;
  mBuff = nullptr;
}

ByteArray _HttpPriContentParser::doParse() {
  byte v = 0;
  while (mReader->readNext(v) != st(ByteRingArrayReader)::NoContent) {
      if(isComplete(v)) {
        ByteArray result = mReader->pop();
        if(mBuff != nullptr) {
            mBuff->append(result);
        }
        result->quickShrink(result->size() - 4);
        return result;
      }
  }
  
  if(mBuff == nullptr) {
    mBuff = mReader->pop();
  } else {
    mBuff->append(mReader->pop());
  }
  return nullptr;
}

bool _HttpPriContentParser::isComplete(byte &v) {
    if(v == '\r'|| v == '\n') {
      completeIndex++;
    } else {
      completeIndex = 0;
    }

    return completeIndex == 4;
}



} // namespace obotcha
