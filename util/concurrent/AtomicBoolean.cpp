#include "AtomicBoolean.hpp"

namespace obotcha {


_AtomicBoolean::_AtomicBoolean(bool val) {
    mValue = val;
}
    
void _AtomicBoolean::set(bool val) {
    mValue = val;
}

bool _AtomicBoolean::get() {
    return mValue;
}

}
