#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

sp<_String> _Object::toString() {
    return String::New((uint64_t)this);
}

}
