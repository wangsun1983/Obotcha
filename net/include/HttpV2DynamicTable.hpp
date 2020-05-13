#ifndef __OBOTCHA_HTTP_V2_DYNAMIC_TABLE_HPP__
#define __OBOTCHA_HTTP_V2_DYNAMIC_TABLE_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Byte.hpp"
#include "List.hpp"
#include "ByteArray.hpp"
#include "HttpV2HeaderField.hpp"
#include "ArrayList.hpp"

namespace obotcha {


DECLARE_SIMPLE_CLASS(HttpV2DynamicTable) {

public:
    _HttpV2DynamicTable(int initialCapacity);
    int length();
    int size();
    int capacity();
    HttpV2HeaderField getEntry(int index);
    void add(HttpV2HeaderField header);
    HttpV2HeaderField remove();
    void clear();
    void setCapacity(int capacity);

private:
    ArrayList<HttpV2HeaderField> mHeaderFields;
    int mHead;
    int mTail;
    int mSize;
    int mCapacity;

 
};

}

#endif
