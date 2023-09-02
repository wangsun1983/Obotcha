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
    explicit _ByteRingArray(uint64_t size);
    
    explicit _ByteRingArray(sp<_ByteRingArray>);

    ~_ByteRingArray() override;
    
    bool push(byte b);
    
    byte pop();
    
    bool push(const ByteArray &);
    
    bool push(const ByteArray &, uint64_t start, uint64_t length);
    
    bool push(byte *data, uint64_t start, uint64_t length);
    
    ByteArray pop(uint64_t size);
    
    ByteArray popTo(uint64_t index);
    
    uint64_t getStoredDataSize() const;
    
    uint64_t getCapacity() const;
    
    uint64_t getStartIndex() const;
    
    uint64_t getEndIndex() const;
    
    ByteArray popAll();
    
    byte at(uint64_t m) const;
    
    void reset();
    
    void dump(const char * tag = nullptr) const;
    
    void dumpFull(const char *tag = nullptr) const;

    InterfaceForTest(void setStartIndex(uint64_t));
    InterfaceForTest(void setEndIndex(uint64_t));
    InterfaceForTest(uint64_t getNextIndex()) const;
    InterfaceForTest(void setNextIndex(uint64_t));
    InterfaceForTest(void setSize(uint64_t));

private:
    byte *mBuff;
    uint64_t mNext;
    uint64_t mCapacity;
    uint64_t mSize;
};

} // namespace obotcha
#endif
