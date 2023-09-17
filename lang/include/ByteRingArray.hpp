#ifndef __OBOTCHA_BYTE_RING_ARRAY_HPP__
#define __OBOTCHA_BYTE_RING_ARRAY_HPP__

#include <memory>
#include <stdlib.h>

#include "ByteArray.hpp"
#include "Object.hpp"
#include "String.hpp"
#include "OStdImportantNote.hpp"

namespace obotcha {

DECLARE_CLASS(ByteRingArray) {
public:
    explicit _ByteRingArray(size_t size);
    
    explicit _ByteRingArray(sp<_ByteRingArray>);

    ~_ByteRingArray() override;
    
    bool push(byte b);
    
    byte pop();
    
    bool push(const ByteArray &);
    
    bool push(const ByteArray &, size_t start, size_t length);
    
    bool push(const byte *data, size_t start, size_t length);
    
    ByteArray pop(size_t size);
    
    ByteArray popTo(size_t index);
    
    size_t getStoredDataSize() const;
    
    size_t getCapacity() const;
    
    size_t getStartIndex() const;
    
    size_t getEndIndex() const;
    
    ByteArray popAll();
    
    byte at(size_t m) const;
    
    void reset();
    
    void dump(const char * tag = nullptr) const;
    
    void dumpFull(const char *tag = nullptr) const;

    InterfaceForTest(void setStartIndex(size_t));
    InterfaceForTest(void setEndIndex(size_t));
    InterfaceForTest(size_t getNextIndex()) const;
    InterfaceForTest(void setNextIndex(size_t));
    InterfaceForTest(void setSize(size_t));

private:
    byte *mBuff = nullptr;
    size_t mNext = 0;
    size_t mCapacity = 0;
    size_t mSize = 0;
};

} // namespace obotcha
#endif
