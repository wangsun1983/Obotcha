#include "StringBuffer.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"

namespace obotcha {

_StringBuffer::_StringBuffer(int length) {
    mIndex = 0;
    mCapacity = length;
    mContent = (char *)malloc(length);
    memset(mContent,0,mCapacity);
}

const char _StringBuffer::charAt(int index) {
    return (const char)mContent[index];
}

String _StringBuffer::toString() {
    if(mIndex == 0) {
        return createString("");
    }
    return createString(mContent,0,mIndex);
}

String _StringBuffer::toString(int start,int length) {
    if(length == 0) {
        return createString("");
    }
    return createString(mContent,start,length);
}

_StringBuffer * _StringBuffer::subString(int start,int length) {
    if(start + length > mIndex) {
        Trigger(ArrayIndexOutOfBoundsException,"out of boundary");
    }

    if(start == 0) {
        //use origin data
        mIndex = length;
        memset(&mContent[mIndex],0,mCapacity - mIndex);
    } else {
        char *data = (char *)malloc(length + 1);
        memset(data,0,length + 1);
        memcpy(data,&mContent[start],length);
        free(mContent);
        mContent = data;
        mCapacity = length + 1;
        mIndex = length;
    }
    return this;
}

 _StringBuffer::~_StringBuffer() {
    if(mContent != nullptr) {
        free(mContent);
        mContent = nullptr;
    }
}

void _StringBuffer::_base_append(const char *p,int size) {
    if(size + mIndex >= mCapacity) {
        //mContent = (char *)realloc(mContent,(mCapacity + size)*2);
        char * data = (char *)malloc((mCapacity + size)*2);
        memset(data,0,(mCapacity + size)*2);
        memcpy(data,mContent,mCapacity);
        free(mContent);
        mContent = data;
        mCapacity = (mCapacity + size)*2;
    }
    memcpy(&mContent[mIndex],p,size);
    mIndex += size; 
}

_StringBuffer *_StringBuffer::_append() {
    return this;
}

void _StringBuffer::reset() {
    mIndex = 0;
    memset(mContent,0,mCapacity);
}

int _StringBuffer::size() {
    return mIndex;
}

int _StringBuffer::capacity() {
    return mCapacity;
}

} 