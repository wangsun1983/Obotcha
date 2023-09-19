#include "HPackTableItem.hpp"

namespace obotcha {

const int _HPackTableItem::HeaderEntryOverhead = 32;

_HPackTableItem::_HPackTableItem(String paramName,String paramValue):name(paramName),value(paramValue) {
}

//4.1.  Calculating Table Size
//The size of an entry is the sum of its name's length in octets (as
//defined in Section 5.2), its value's length in octets, and 32.
size_t _HPackTableItem::size() {
    return name->size() + value->size() + HeaderEntryOverhead;
}

size_t _HPackTableItem::sizeOf(String name,String value) {
    return name->size() + value->size() + HeaderEntryOverhead;
}

String _HPackTableItem::toString() {
    return name->append(": ",value);
}

}
