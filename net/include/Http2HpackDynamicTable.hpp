#ifndef __OBOTCHA_HTTP2_HPACK_DYNAMIC_TABLE_HPP__
#define __OBOTCHA_HTTP2_HPACK_DYNAMIC_TABLE_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "List.hpp"
#include "Http2HpackTableItem.hpp"
#include "ArrayList.hpp"

namespace obotcha {

//https://datatracker.ietf.org/doc/html/rfc7541#appendix-A
DECLARE_CLASS(Http2HpackDynamicTable) {
public:
    _Http2HpackDynamicTable();
    
private:
    ArrayList<Http2HpackTableItem> tables;
};

}
#endif
