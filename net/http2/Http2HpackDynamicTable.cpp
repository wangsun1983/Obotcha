#include "Http2HpackDynamicTable.hpp"

namespace obotcha {

_Http2HpackDynamicTable::_Http2HpackDynamicTable() {
    tables = createArrayList<Http2HpackTableItem>();
}

}
