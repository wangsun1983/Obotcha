#ifndef __OBOTCHA_HPACK_DYNAMIC_TABLE_HPP__
#define __OBOTCHA_HPACK_DYNAMIC_TABLE_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

//https://datatracker.ietf.org/doc/html/rfc7541#appendix-A
DECLARE_CLASS(HPackDynamicTable) {
public:
    _HPackDynamicTable();
    
private:
    //ArrayList<Http2HpackTableItem> tables;
};

}
#endif
