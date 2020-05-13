#ifndef __OBOTCHA_HTTP_V2_HEADER_FIELD_HPP__
#define __OBOTCHA_HTTP_V2_HEADER_FIELD_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Byte.hpp"
#include "List.hpp"
#include "ByteArray.hpp"

namespace obotcha {


DECLARE_SIMPLE_CLASS(HttpV2HeaderField) {

public:
    _HttpV2HeaderField(String,String);
    
    static int sizeOf(ByteArray name, ByteArray value);
    
    int size();

    bool equals(HttpV2HeaderField);

    // Section 4.1. Calculating Table Size
    // The additional 32 octets account for an estimated
    // overhead associated with the structure.
    static const int HeaderEntryOverhead = 32;
    
private:

    ByteArray mName;
    ByteArray mValue;    
};



}

#endif
