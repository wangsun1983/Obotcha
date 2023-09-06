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
    explicit _StringBuffer(size_t length = 256);
    ~_StringBuffer() override;

    char charAt(size_t) const;

    template <class... Args>
    _StringBuffer *append(Args... args) {
        _append(args...);
        return this;
    }

    String toString() override;

    String toString(size_t start,size_t length);

    sp<_StringBuffer> crop(size_t start,size_t length);
    
    String subString(size_t start,size_t length);

    size_t size() const;

    size_t capacity() const;

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

    void _base_append(const char *p,size_t size);

    size_t mCapacity;

    size_t mNextIndex = 0;

    size_t mStartIndex = 0;

    char *mContent;
};

} // namespace obotcha
#endif
