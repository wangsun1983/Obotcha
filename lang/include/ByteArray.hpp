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
    
    explicit _ByteArray(size_t length);
    
    explicit _ByteArray(byte *data, size_t len,bool mapped = false);
    
    explicit _ByteArray(sp<_ByteArray> &, size_t start = 0, size_t len = 0);

    ~_ByteArray() override;

    byte *toValue(bool copy = false);
    
    size_t size() const;
    
    void clear();
    
    byte &operator[](size_t i);
    
    int growTo(size_t size);
    
    int growBy(size_t size);
    
    int quickShrink(size_t size);
    
    size_t quickRestore();
    
    bool isEmpty() const;
    
    byte at(size_t) const;
    
    int fill(byte v);
    
    int fill(size_t start, size_t length, byte v);
    
    int fillFrom(const byte *input,size_t destStart,size_t len);
    
    size_t append(const sp<_ByteArray> &);
    
    size_t append(const sp<_ByteArray> &, size_t len);
    
    size_t append(const byte * data, size_t len);

    sp<_String> toString() override;
    
    void dump(const char *tag) const;
    
    void dump(const sp<_String> &tag) const;
    
    void dumpToFile(const char *path) const;
    
    void dumpToFile(const sp<_String> &path) const;

    sp<_ByteArray> clone();

    bool equals(Object p) override;

    void slice(size_t start,size_t length = 0);
	
	bool isOverflow(size_t start,size_t length);

    static void Combine(ByteArray &dest,ByteArray appenddata);

    static const size_t kDefaultSize;

    template <typename T>
    static ByteArray Translate(T *data) {
        ByteArray value = ByteArray::New(sizeof(T));
        memcpy(value->toValue(),(void *)data,sizeof(T));
        return value;
    }

    template <typename T>
    static T* Translate(ByteArray data) {
        T *value = (T *)malloc(sizeof(T));
        memcpy(value,data->toValue(),data->size());
        return value;
    }

private:
    byte *mBuff;
    size_t mSize;
    size_t mStart = 0;
    size_t mPreviousSize;
    bool mMapped;
};

} // namespace obotcha
#endif
