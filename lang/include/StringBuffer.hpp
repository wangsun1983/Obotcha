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
    explicit _StringBuffer(int length = 256);
    ~_StringBuffer();

    char charAt(int);

    template <class... Args>
    _StringBuffer *append(Args... args) {
        _append(args...);
        return this;
    }

    String toString();

    String toString(int start,int length);

    _StringBuffer* subString(int start,int length);

    int size();

    int capacity();

    void reset();

private:
    template <class... Args>
    _StringBuffer *_append(String v, Args... args) {
        _base_append(v->toChars(),v->size());
        return _append(args...);
    }

    template <class... Args>
    _StringBuffer *_append(const char *v, Args... args) {
        _base_append(v,strlen(v));
        return _append(args...);
    }

    template <class... Args>
    _StringBuffer *_append(char v, Args... args) {
        _base_append((const char *)&v,1);
        return _append(args...);
    }

    _StringBuffer *_append();

    void _base_append(const char *p,int size);

    int mCapacity;

    int mNextIndex;

    int mStartIndex;

    char *mContent;
};

} // namespace obotcha
#endif
