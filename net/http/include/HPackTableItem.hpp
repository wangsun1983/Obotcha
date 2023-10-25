#ifndef __OBOTCHA_HPACK_TABLE_ITEM_HPP__
#define __OBOTCHA_HPACK_TABLE_ITEM_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

//https://datatracker.ietf.org/doc/html/rfc7541#appendix-A
DECLARE_CLASS(HPackTableItem) {
public:
    _HPackTableItem() = default;
    _HPackTableItem(String name,String value);
    String name = nullptr;
    String value = nullptr;
    int id = 0;

    static size_t sizeOf(String name,String value);
    
    // Section 4.1. Calculating Table Size
    // The additional 32 octets account for an estimated
    // overhead associated with the structure.
    static const int HeaderEntryOverhead;

    size_t size();
    String toString();
};

}
#endif
