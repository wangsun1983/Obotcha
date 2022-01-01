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
    enum Type {
        safe = 0,
        unsafe,
    };

    explicit _ByteArray(int length);

    explicit _ByteArray(const byte *data, uint32_t len,bool mapped = false);

    explicit _ByteArray(sp<_ByteArray> &, int start = 0, int len = 0);

    template <typename T> static ByteArray alloc() {
        return createByteArray(sizeof(T));
    }

    ~_ByteArray();

    byte *toValue();

    int size();

    void clear();

    byte &operator[](int i);

    void setSafe();

    void setUnSafe();

    bool isSafeMode();

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

    template <typename U> U *get() { return (U *)buff; }

    template <typename U> int apply(U * p) {
        if (mSize < sizeof(U)) {
            return -1;
        }

        memcpy(buff, p, sizeof(U));
        return 0;
    }

    // add foreach lambda
    using foreachCallback = std::function<int(byte &)>;
    inline void foreach (foreachCallback callback) {
        for (int i = 0; i < mSize; i++) {
            if (callback(buff[i]) == Global::Break) {
                break;
            }
        }
    }

    sp<_String> toString();

    void dump(const char *tag);

    void dump(const sp<_String> &tag);

    void dumpToFile(const char *path);

    void dumpToFile(const sp<_String> &path);

    void setPriorityWeight(int);
    int getPriorityWeight();

private:
    byte *buff;

    int mSize;

    bool isSafe;

    int mOriginalSize;

    bool mMapped;

    int mPriority;
};

} // namespace obotcha
#endif
