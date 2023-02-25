#ifndef __OBOTCHA_BYTE_ARRAY_HPP__
#define __OBOTCHA_BYTE_ARRAY_HPP__

#include <functional>
#include <memory.h>
#include <stdlib.h>

#include "Byte.hpp"
#include "Object.hpp"

namespace obotcha {
class _String;

DECLARE_CLASS(ByteArray) {
public:
    explicit _ByteArray();

    explicit _ByteArray(int length);

    explicit _ByteArray(const byte *data, uint32_t len,bool mapped = false);

    explicit _ByteArray(sp<_ByteArray> &, int start = 0, int len = 0);

    ~_ByteArray();

    byte *toValue(bool copy = false);

    int size();

    void clear();

    byte &operator[](int i);

    int growTo(int size);

    int growBy(int size);

    int quickShrink(int size);

    int quickRestore();

    bool isEmpty();

    byte at(int);

    int fill(byte v);

    int fill(int start, int length, byte v);

    int fillFrom(byte *input,int start,int len);

    int append(const sp<_ByteArray> &);

    int append(const sp<_ByteArray> &, int len);

    int append(byte * data, int len);

    //convert struct start
    template <typename T> static ByteArray alloc() {
        return createByteArray(sizeof(T));
    }

    template <typename U> U *get() {
      return (U *)buff;
    }

    template <typename U> int apply(U * p) {
        if (mSize < sizeof(U)) {
            return -1;
        }

        memcpy(buff, p, sizeof(U));
        return 0;
    }
    //convert struct end

    sp<_String> toString();

    void dump(const char *tag);

    void dump(const sp<_String> &tag);

    void dumpToFile(const char *path);

    void dumpToFile(const sp<_String> &path);

    sp<_ByteArray> clone();

    bool equals(const ByteArray &s);

    static const int kDefaultSize;

private:
    byte *buff;

    int mSize;

    int mOriginalSize;

    bool mMapped;
};

} // namespace obotcha
#endif
