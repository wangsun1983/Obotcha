#ifndef __OBOTCHA_HPACK_DYNAMIC_TABLE_HPP__
#define __OBOTCHA_HPACK_DYNAMIC_TABLE_HPP__

#include "Object.hpp"
#include "HPackTableItem.hpp"
#include "List.hpp"

namespace obotcha {

//https://datatracker.ietf.org/doc/html/rfc7541#appendix-A
DECLARE_CLASS(HPackDynamicTable) {
public:
    explicit _HPackDynamicTable(int);
    
    /**
     * Return the number of header fields in the dynamic table.
     */
    int length();

    /**
     * Return the current size of the dynamic table. This is the sum of the size of the entries.
     */
    long size();
    
    long capacity();
    
    HPackTableItem getEntry(int index);

    void add(HPackTableItem header);
    
    /**
     * Remove and return the oldest header field from the dynamic table.
     */
    HPackTableItem remove();

    /**
     * Remove all entries from the dynamic table.
     */
    void clear();

    /**
     * Set the maximum size of the dynamic table. Entries are evicted from the dynamic table until
     * the size of the table is less than or equal to the maximum size.
     */
    void setCapacity(long capacity);


private:
    List<HPackTableItem> hpackHeaderFields;
    int head;
    int tail;
    long mSize;
    long mCapacity; 
};

}
#endif
