#ifndef __HTTP_MULTI_PART_PARSER_HPP__
#define __HTTP_MULTI_PART_PARSER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Pipe.hpp"
#include "Mutex.hpp"
#include "HttpMultiPart.hpp"
#include "ByteRingArrayReader.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpMultiPartParser) {
public:
    _HttpMultiPartParser(int,ByteRingArrayReader);

    int parse();

    HttpMultiPart getMultiPart();
    
    static const int ParseComplete;
    static const int ParseContinue;

private:
    HttpMultiPart mMultiPart;

    ByteRingArrayReader mReader;

    int mContentLength;


};

}
#endif
