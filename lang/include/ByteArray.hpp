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
    
    explicit _ByteArray(int length);
    
    explicit _ByteArray(byte *data, uint32_t len,bool mapped = false);
    
    explicit _ByteArray(sp<_ByteArray> &, int start = 0, int len = 0);

    ~_ByteArray() override;

    byte *toValue(bool copy = false);
    
    int size() const;
    
    void clear();
    
    byte &operator[](int i);
    
    int growTo(int size);
    
    int growBy(int size);
    
    int quickShrink(int size);
    
    int quickRestore();
    
    bool isEmpty() const;
    
    byte at(int) const;
    
    int fill(byte v);
    
    int fill(int start, int length, byte v);
    
    int fillFrom(const byte *input,int destStart,int len);
    
    int append(const sp<_ByteArray> &);
    
    int append(const sp<_ByteArray> &, int len);
    
    int append(const byte * data, int len);

    // //convert struct start
    // template <typename U> U *get() {
    //   return (U *)mBuff;
    // }

    // template <typename U> int apply(U * p) {
    //     Inspect(mSize < sizeof(U),-1)
    //     memcpy(mBuff, p, sizeof(U));
    //     return sizeof(U);
    // }
    // //convert struct end

    sp<_String> toString() override;
    
    void dump(const char *tag) const;
    
    void dump(const sp<_String> &tag) const;
    
    void dumpToFile(const char *path) const;
    
    void dumpToFile(const sp<_String> &path) const;

    sp<_ByteArray> clone();

    bool equals(Object p) override;

    //convert struct start
    // template <typename T> static ByteArray Alloc() {
    //     return createByteArray(sizeof(T));
    // }
    class Transformer {
        public:
            template <typename T>
            static ByteArray Alloc() {
                return createByteArray(sizeof(T));
            }

            template<typename T>
            static ByteArray Convert(T &data) {
                auto result = createByteArray(sizeof(T));
                memcpy(result->toValue(),&data,sizeof(T)); 
                return result;
            }

            template<typename T>
            static T* Convert(ByteArray data) {
                Inspect(data->size() < sizeof(T),nullptr)
                return (T*)(data->toValue());
            }
    };

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
