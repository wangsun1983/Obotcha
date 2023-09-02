#ifndef __OBOTCHA_BYTE_ARRAY_HPP__
#define __OBOTCHA_BYTE_ARRAY_HPP__

#include <memory>
#include <stdlib.h>
#include <string.h>

#include "Byte.hpp"
#include "Object.hpp"
#include "Inspect.hpp"

namespace obotcha {
class _String;

DECLARE_CLASS(ByteArray) {
public:
    explicit _ByteArray();
    
    explicit _ByteArray(uint64_t length);
    
    explicit _ByteArray(byte *data, uint64_t len,bool mapped = false);
    
    explicit _ByteArray(sp<_ByteArray> &, uint64_t start = 0, uint64_t len = 0);

    ~_ByteArray() override;

    byte *toValue(bool copy = false);
    
    uint64_t size() const;
    
    void clear();
    
    byte &operator[](uint64_t i);
    
    int growTo(uint64_t size);
    
    int growBy(uint64_t size);
    
    int quickShrink(uint64_t size);
    
    int quickRestore();
    
    bool isEmpty() const;
    
    byte at(uint64_t) const;
    
    int fill(byte v);
    
    int fill(uint64_t start, uint64_t length, byte v);
    
    int fillFrom(const byte *input,uint64_t destStart,uint64_t len);
    
    uint64_t append(const sp<_ByteArray> &);
    
    uint64_t append(const sp<_ByteArray> &, uint64_t len);
    
    uint64_t append(const byte * data, uint64_t len);

    sp<_String> toString() override;
    
    void dump(const char *tag) const;
    
    void dump(const sp<_String> &tag) const;
    
    void dumpToFile(const char *path) const;
    
    void dumpToFile(const sp<_String> &path) const;

    sp<_ByteArray> clone();

    bool equals(Object p) override;

    static void Combine(ByteArray &dest,ByteArray appenddata);

    static const uint64_t kDefaultSize;

private:
    byte *mBuff;
    uint64_t mSize;
    uint64_t mPreviousSize;
    bool mMapped;
};

} // namespace obotcha
#endif
