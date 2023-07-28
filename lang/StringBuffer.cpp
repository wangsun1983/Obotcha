#include "StringBuffer.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"

namespace obotcha {

_StringBuffer::_StringBuffer(size_t length):mCapacity(length) {
    mContent = (char *)zmalloc(length);
}

char _StringBuffer::charAt(int index) const {
    Panic(index > mNextIndex,ArrayIndexOutOfBoundsException,"out of boundary")
    return mContent[index];
}

String _StringBuffer::toString() {
    return (mNextIndex == 0)?createString("")
                        :createString(mContent,mStartIndex,mNextIndex - mStartIndex);
}

String _StringBuffer::toString(int start,int length) {
    return (length == 0)?createString("")
                        :createString(mContent,start,length);
}

_StringBuffer * _StringBuffer::subString(int start,int length) {
    Panic(mStartIndex + start + length > mNextIndex,
            ArrayIndexOutOfBoundsException,"out of boundary")
    mStartIndex += start;
    mNextIndex = mStartIndex + length;
    return this;
}

 _StringBuffer::~_StringBuffer() {
    if(mContent != nullptr) {
        free(mContent);
        mContent = nullptr;
    }
}

void _StringBuffer::_base_append(const char *p,size_t size) {
    if(mNextIndex + size >= mCapacity) {
        size_t enlarge = (mCapacity + size)*2;
        mContent = (char *)realloc(mContent, enlarge);
        mCapacity = enlarge;
        memset(mContent + mNextIndex, 0, enlarge - mNextIndex);
    }
    memcpy(&mContent[mNextIndex],p,size);
    mNextIndex += size;
}

_StringBuffer *_StringBuffer::_append() {
    return this;
}

void _StringBuffer::reset() {
    mNextIndex = mStartIndex = 0;
    memset(mContent,0,mCapacity);
}

int _StringBuffer::size() const {
    return mNextIndex - mStartIndex;
}

int _StringBuffer::capacity() const {
    return mCapacity;
}

}
