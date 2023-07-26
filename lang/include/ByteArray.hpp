#ifndef __OBOTCHA_BYTE_ARRAY_HPP__
#define __OBOTCHA_BYTE_ARRAY_HPP__

#include <functional>
#include <memory>
#include <stdlib.h>
#include <vector>

#include "Byte.hpp"
#include "Object.hpp"
#include "Inspect.hpp"

namespace obotcha {
class _String;

DECLARE_CLASS(ByteArray) {
public:
    explicit _ByteArray();
    
    explicit _ByteArray(int length);
    
    explicit _ByteArray(byte *data, uint32_t len,bool mapped = false);
    
    explicit _ByteArray(sp<_ByteArray> &, int start = 0, int len = 0);

    ~_ByteArray() override;

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
    
    int fillFrom(byte *input,int destStart,int len);
    
    int append(const sp<_ByteArray> &);
    
    int append(const sp<_ByteArray> &, int len);
    
    int append(byte * data, int len);

    //convert struct start
    template <typename U> U *get() {
      return (U *)mBuff;
    }

    template <typename U> int apply(U * p) {
        Inspect(mSize < sizeof(U),-1)
        memcpy(mBuff, p, sizeof(U));
        return sizeof(U);
    }
    //convert struct end

    sp<_String> toString() override;
    
    void dump(const char *tag);
    
    void dump(const sp<_String> &tag);
    
    void dumpToFile(const char *path);
    
    void dumpToFile(const sp<_String> &path);

    sp<_ByteArray> clone();

    bool equals(Object p) override;

    //convert struct start
    template <typename T> static ByteArray Alloc() {
        return createByteArray(sizeof(T));
    }

    static void Combine(ByteArray &dest,ByteArray appenddata);

    //convert struct start
    static const int kDefaultSize;

private:
    byte *mBuff;
    int mSize;
    int mPreviousSize;
    bool mMapped;
};

} // namespace obotcha
#endif
