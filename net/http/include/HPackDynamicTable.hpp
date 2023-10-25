#ifndef __OBOTCHA_HPACK_DYNAMIC_TABLE_HPP__
#define __OBOTCHA_HPACK_DYNAMIC_TABLE_HPP__

#include "Object.hpp"
#include "HPackTableItem.hpp"
#include "List.hpp"
#include "HPack.hpp"

namespace obotcha {

//https://datatracker.ietf.org/doc/html/rfc7541#appendix-A
DECLARE_CLASS(HPackDynamicTable) {
public:
    explicit _HPackDynamicTable(size_t);
    
    /**
     * Return the number of header fields in the dynamic table.
     */
    size_t length() const;

    /**
     * Return the current size of the dynamic table. This is the sum of the size of the entries.
     */
    size_t size() const;
    
    size_t capacity() const;
    
    HPackTableItem getEntry(size_t index);

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
    void setCapacity(size_t capacity);


private:
    List<HPackTableItem> hpackHeaderFields;
    size_t head = 0;
    size_t tail = 0;
    size_t mSize = 0;
    size_t mCapacity = st(HPack)::DefaultHeaderTableSize; 
};

}
#endif
