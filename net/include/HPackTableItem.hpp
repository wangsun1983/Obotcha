#ifndef __OBOTCHA_HPACK_TABLE_ITEM_HPP__
#define __OBOTCHA_HPACK_TABLE_ITEM_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "List.hpp"

namespace obotcha {

//https://datatracker.ietf.org/doc/html/rfc7541#appendix-A
DECLARE_CLASS(HPackTableItem) {
public:
    _HPackTableItem();
    _HPackTableItem(String name,String value);
    String name;
    String value;
    int id;

    static int sizeOf(String name,String value);
    
    // Section 4.1. Calculating Table Size
    // The additional 32 octets account for an estimated
    // overhead associated with the structure.
    static const int HeaderEntryOverhead;

    int size();
    String toString();
};

}
#endif
