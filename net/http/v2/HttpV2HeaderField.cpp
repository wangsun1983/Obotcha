#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Byte.hpp"
#include "List.hpp"
#include "ByteArray.hpp"
#include "HttpV2HeaderField.hpp"
#include "HttpV2HpackUtil.hpp"

namespace obotcha {


_HttpV2HeaderField::_HttpV2HeaderField(String name,String value) {
    this->mName = name->toByteArray();
    this->mValue = value->toByteArray();
}
    
int _HttpV2HeaderField::sizeOf(ByteArray name, ByteArray value) {
    return name->size() + value->size() + HeaderEntryOverhead;
}
    
int _HttpV2HeaderField::size() {
    return mName->size() + mValue->size() + HeaderEntryOverhead;
}

bool _HttpV2HeaderField::equals(HttpV2HeaderField f) {
    bool nameEquals = st(HttpV2HpackUtil)::equals(createByteArray(mName), createByteArray(f->mName));
    bool valueEquals = st(HttpV2HpackUtil)::equals(createByteArray(mValue), createByteArray(f->mValue));
    return nameEquals && valueEquals;
}


}
