#include "HPackTableItem.hpp"

namespace obotcha {

const int _HPackTableItem::HeaderEntryOverhead = 32;

_HPackTableItem::_HPackTableItem() {
    name = nullptr;
    value = nullptr;
}

_HPackTableItem::_HPackTableItem(String name,String value) {
    this->name = name;
    this->value = value;
}

//4.1.  Calculating Table Size
//The size of an entry is the sum of its name's length in octets (as
//defined in Section 5.2), its value's length in octets, and 32.
int _HPackTableItem::size() {
    return name->size() + value->size() + HeaderEntryOverhead;
}

int _HPackTableItem::sizeOf(String name,String value) {
    return name->size() + value->size() + HeaderEntryOverhead;
}

String _HPackTableItem::toString() {
    return name->append(": ",value);
}

}
