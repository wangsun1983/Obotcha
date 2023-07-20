#ifndef __OBOTCHA_BYTE_RING_ARRAY_HPP__
#define __OBOTCHA_BYTE_RING_ARRAY_HPP__

#include <memory.h>
#include <stdlib.h>

#include "ByteArray.hpp"
#include "Object.hpp"
#include "String.hpp"
#include "OStdImportantNote.hpp"

namespace obotcha {

DECLARE_CLASS(ByteRingArray) {
public:
    explicit _ByteRingArray(int size);
    
    explicit _ByteRingArray(sp<_ByteRingArray>);

    ~_ByteRingArray();
    
    bool push(byte b);
    
    byte pop();
    
    bool push(const ByteArray &);
    
    bool push(const ByteArray &, int start, int length);
    
    bool push(byte *data, int start, int length);
    
    ByteArray pop(int size);
    
    ByteArray popTo(int index);
    
    int getStoredDataSize();
    
    int getCapacity();
    
    int getStartIndex();
    
    int getEndIndex();
    
    ByteArray popAll();
    
    byte at(int m);
    
    void reset();
    
    void dump(const char * tag = nullptr);
    
    void dumpFull(const char *tag = nullptr);

    InterfaceForTest(void setStartIndex(int));
    InterfaceForTest(void setEndIndex(int));
    InterfaceForTest(int getNextIndex());
    InterfaceForTest(void setNextIndex(int));
    InterfaceForTest(void setSize(int));

private:
    byte *mBuff;
    int mNext;
    int mCapacity;
    int mSize;
};

} // namespace obotcha
#endif
