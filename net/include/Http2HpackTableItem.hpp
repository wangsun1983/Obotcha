#ifndef __OBOTCHA_HTTP2_HPACK_TABLE_ITEM_HPP__
#define __OBOTCHA_HTTP2_HPACK_TABLE_ITEM_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "List.hpp"

namespace obotcha {

DECLARE_CLASS(Http2HpackTableItem) {
public:
    _Http2HpackTableItem(String name,String value);
    String headerName;
    String headerValue;
};

}
#endif
