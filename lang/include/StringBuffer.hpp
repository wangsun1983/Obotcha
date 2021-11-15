#ifndef __OBOTCHA_STRING_BUFFER_HPP__
#define __OBOTCHA_STRING_BUFFER_HPP__

#include <iostream>
#include <stdarg.h>
#include <string>
#include <stdlib.h>


#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(StringBuffer) {
public:
    _StringBuffer(int length = 256);
    ~_StringBuffer();

    const char charAt(int);

    template <class... Args>
    _StringBuffer *append(Args... args) {
        _append(std::forward<Args>(args)...);
        return this;
    }

    String toString();

private:
    template <class... Args>
    _StringBuffer *_append(String &v, Args... args) {
        if(v->size() + mIndex >= mSize) {
            mContent = (char *)realloc(mContent,(mSize + v->size())*2);
        }

        memcpy(&mContent[mIndex],v->toChars(),v->size());
        mIndex += v->size();
        return _append(std::forward<Args>(args)...); 
    }

    template <class... Args>
    _StringBuffer *_append(const char *v, Args... args) {
        int size = strlen(v);

        if(size + mIndex >= mSize) {
            mContent = (char *)realloc(mContent,(mSize + size)*2);
        }

        memcpy(&mContent[mIndex],v,size);
        mIndex += size; 
        return _append(std::forward<Args>(args)...); 
    }

    _StringBuffer *_append() {
        return this;
    }
    
    int mSize;
    int mIndex;
    char *mContent;
};

} // namespace obotcha
#endif