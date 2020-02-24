#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Byte.hpp"
#include "List.hpp"
#include "ByteArray.hpp"
#include "HttpV2HeaderField.hpp"
#include "ArrayList.hpp"
#include "HttpV2DynamicTable.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"
#include "IllegalArgumentException.hpp"

namespace obotcha {

_HttpV2DynamicTable::_HttpV2DynamicTable(int initialCapacity) {
    setCapacity(initialCapacity);
}

int _HttpV2DynamicTable::length() {
    int length;
    if (mHead < mTail) {
        length = mHeaderFields->size() - mTail + mHead;
    } else {
        length = mHead - mTail;
    }
    return length;
}

int _HttpV2DynamicTable::size() {
    return mSize;
}

int _HttpV2DynamicTable::capacity() {
    return mCapacity;
}

HttpV2HeaderField _HttpV2DynamicTable::getEntry(int index) {
    if (index <= 0 || index > length()) {
        throw ArrayIndexOutOfBoundsException("DynamicTable getEntry Error");
    }

    int i = mHead - index;
    if (i < 0) {
        return mHeaderFields->get(i + mHeaderFields->size());
    } else {
        return mHeaderFields->get(i);
    }
}

void _HttpV2DynamicTable::add(HttpV2HeaderField header) {
    int headerSize = header->size();
    if (headerSize > mCapacity) {
        clear();
        return;
    }
    while (mSize + headerSize > mCapacity) {
        remove();
    }

    mHeaderFields->set(mHead++,header);
    mSize += header->size();
    if (mHead == mHeaderFields->size()) {
        mHead = 0;
    }
}

HttpV2HeaderField _HttpV2DynamicTable::remove() {
    HttpV2HeaderField removed = mHeaderFields->get(mTail);
    if (removed == nullptr) {
      return nullptr;
    }

    mSize -= removed->size();
    mHeaderFields->set(mTail++,nullptr);
    if (mTail == mHeaderFields->size()) {
      mTail = 0;
    }
    return removed;
}

void _HttpV2DynamicTable::clear() {
    while (mTail != mHead) {
        mHeaderFields->set(mTail++,nullptr);
        if (mTail == mHeaderFields->size()) {
            mTail = 0;
        }
    }
    mHead = 0;
    mTail = 0;
    mSize = 0;
}

void _HttpV2DynamicTable::setCapacity(int capacity) {
    if (mCapacity < 0) {
      throw IllegalArgumentException("Illegal Capacity");
    }

    // initially capacity will be -1 so init won't return here
    if (mCapacity == capacity) {
      return;
    }

    mCapacity = capacity;

    if (capacity == 0) {
        clear();
    } else {
      // initially size will be 0 so remove won't be called
      while (mSize > capacity) {
          remove();
      }
    }

    int maxEntries = capacity / st(HttpV2HeaderField)::HeaderEntryOverhead;
    if (capacity % st(HttpV2HeaderField)::HeaderEntryOverhead != 0) {
      maxEntries++;
    }

    // check if capacity change requires us to reallocate the array
    if (mHeaderFields != nullptr && mHeaderFields->size() == maxEntries) {
      return;
    }

    ArrayList<HttpV2HeaderField>tmp = createArrayList<HttpV2HeaderField>(maxEntries);

    // initially length will be 0 so there will be no copy
    int len = length();
    int cursor = mTail;
    for (int i = 0; i < len; i++) {
      HttpV2HeaderField entry = mHeaderFields->get(cursor++);
      tmp->set(i,entry);
      if (cursor == mHeaderFields->size()) {
        cursor = 0;
      }
    }

    mTail = 0;
    mHead = mTail + len;
    mHeaderFields = tmp;
}


}


