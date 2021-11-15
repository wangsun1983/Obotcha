#include "StringBuffer.hpp"

namespace obotcha {

_StringBuffer::_StringBuffer(int length) {
    mIndex = 0;
    mSize = length;
    mContent = (char *)malloc(length);
    memset(mContent,0,mSize);
}

const char _StringBuffer::charAt(int index) {
    return (const char)mContent[index];
}

String _StringBuffer::toString() {
    return createString(mContent,0,mIndex);
}

 _StringBuffer::~_StringBuffer() {
    free(mContent);
    mContent = nullptr;
 }

} 