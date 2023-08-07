#include "HttpPriContentParser.hpp"
#include "Definations.hpp"

namespace obotcha {

_HttpPriContentParser::_HttpPriContentParser(ByteRingArrayReader r):mReader(r) {
}

ByteArray _HttpPriContentParser::doParse() {
    byte v = 0;
    while (mReader->readNext(v) != st(Defination)::NoContentRead) {
        if(isComplete(v)) {
            ByteArray result = mReader->pop();
            if(mBuff != nullptr) {
                mBuff->append(result);
            }
            result->quickShrink(result->size() - 4);
            return result;
        }
    }
    st(ByteArray)::Combine(mBuff,mReader->pop());
    return nullptr;
}

bool _HttpPriContentParser::isComplete(const byte &v) {
    if(v == '\r'|| v == '\n') {
        mCompleteIndex++;
    } else {
        mCompleteIndex = 0;
    }

    return mCompleteIndex == 4;
}

} // namespace obotcha
