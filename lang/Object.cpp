#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

sp<_String> _Object::toString() {
    return createString((uint64_t)this);
}

}
