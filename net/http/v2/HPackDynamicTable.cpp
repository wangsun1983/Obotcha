#include "HPackDynamicTable.hpp"
#include "HPack.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"
#include "IllegalArgumentException.hpp"

namespace obotcha {

_HPackDynamicTable::_HPackDynamicTable(int cap) {
    hpackHeaderFields = createList<HPackTableItem>(cap);
}

int _HPackDynamicTable::length() const {
    return (head < tail)?hpackHeaderFields->size() - tail + head:
                        head - tail;
}

long _HPackDynamicTable::size() const {
    return mSize;
}

long _HPackDynamicTable::capacity() const {
    return mCapacity;
}

HPackTableItem _HPackDynamicTable::getEntry(int index) {
    if (index <= 0 || index > length()) {
        Trigger(ArrayIndexOutOfBoundsException,"index too large")
    }
    int i = head - index;
    if (i < 0) {
        return hpackHeaderFields[i + hpackHeaderFields->size()];
    } else {
        return hpackHeaderFields[i];
    }
}

void _HPackDynamicTable::add(HPackTableItem header) {
    int headerSize = header->size();
    if (headerSize > mCapacity) {
        clear();
        return;
    }
    while (mCapacity - mSize < headerSize) {
        remove();
    }
    hpackHeaderFields[head] = header;
    head++;
    mSize += headerSize;
    if (head == hpackHeaderFields->size()) {
        head = 0;
    }
}

HPackTableItem _HPackDynamicTable::remove() {
    HPackTableItem removed = hpackHeaderFields[tail];
    if (removed == nullptr) {
        return nullptr;
    }
    mSize -= removed->size();
    hpackHeaderFields[tail] = nullptr;
    tail++;
    if (tail == hpackHeaderFields->size()) {
        tail = 0;
    }
    return removed;
}

void _HPackDynamicTable::clear() {
    while (tail != head) {
        hpackHeaderFields[tail] = nullptr;
        tail++;
        if (tail == hpackHeaderFields->size()) {
            tail = 0;
        }
    }
    head = 0;
    tail = 0;
    mSize = 0;
}

void _HPackDynamicTable::setCapacity(long capacity) {
    if (capacity < st(HPack)::MinHeaderTableSize || capacity > st(HPack)::MaxHeaderTableSize) {
        Trigger(IllegalArgumentException,"error")
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

    auto maxEntries = (int) (capacity / st(HPackTableItem)::HeaderEntryOverhead);
    if (capacity % st(HPackTableItem)::HeaderEntryOverhead != 0) {
        maxEntries++;
    }

    // check if capacity change requires us to reallocate the array
    if (hpackHeaderFields != nullptr && hpackHeaderFields->size() == maxEntries) {
        return;
    }

    List<HPackTableItem> tmp = createList<HPackTableItem>(maxEntries);

    // initially length will be 0 so there will be no copy
    int len = length();
    if (hpackHeaderFields != nullptr) {
        int cursor = tail;
        for (int i = 0; i < len; i++) {
            HPackTableItem entry = hpackHeaderFields[cursor];
            cursor++;
            tmp[i] = entry;
            if (cursor == hpackHeaderFields->size()) {
                cursor = 0;
            }
        }
    }

    tail = 0;
    head = tail + len;
    hpackHeaderFields = tmp;
}

}
