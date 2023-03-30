#include "HttpPriContentParser.hpp"

namespace obotcha {

_HttpPriContentParser::_HttpPriContentParser(ByteRingArrayReader r) {
    mCompleteIndex = 0;
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
    MakeUp(mBuff,mReader->pop());
    return nullptr;
}

bool _HttpPriContentParser::isComplete(byte &v) {
    if(v == '\r'|| v == '\n') {
        mCompleteIndex++;
    } else {
        mCompleteIndex = 0;
    }

    return mCompleteIndex == 4;
}

} // namespace obotcha
