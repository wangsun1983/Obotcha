/**
 * @file AtomibBoolean.cpp
 * @brief  A boolean value that may be updated atomically. An
 * AtomicBoolean is used in applications such as atomically
 * updated flags, and cannot be used as a replacement for a
 * java.lang.Boolean
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2024-01-15
 * @license none
 */

#include "AtomicBoolean.hpp"

namespace obotcha {

_AtomicBoolean::_AtomicBoolean(bool val):mValue(val) {    
}

void _AtomicBoolean::set(bool val) { 
    mValue = val; 
}

bool _AtomicBoolean::get() const { 
    return mValue; 
}

} // namespace obotcha
