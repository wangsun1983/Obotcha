#include "HttpMultiPartParser.hpp"

namespace obotcha {

const int _HttpMultiPartParser::ParseComplete = 0;
const int _HttpMultiPartParser::ParseContinue = 1;  

_HttpMultiPartParser::_HttpMultiPartParser(int length,ByteRingArrayReader reader) {
    mMultiPart = createHttpMultiPart();
    mContentLength = length;
}

int _HttpMultiPartParser::parse() {
    //TODO
    return ParseComplete;
}

HttpMultiPart _HttpMultiPartParser::getMultiPart() {
    //TODO
    return nullptr;
}

}