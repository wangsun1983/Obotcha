#include "Http2HpackTableItem.hpp"

namespace obotcha {

_Http2HpackTableItem::_Http2HpackTableItem(String name,String value) {
    this->headerName = name;
    this->headerValue = value;
}

}