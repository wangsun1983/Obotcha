#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

sp<_String> _Object::toString() {
    return createString((uint64_t)this);
}

bool _Object::equals(void *m) {
    if(m == this) {
        return true;
    }

    Object obj;
    obj.set_pointer((_Object *)m);
    return this->equals(obj);
}

}
