#include <stdio.h>
#include "Runnable.hpp"
#include "AutoLock.hpp"
#include "IllegalStateException.hpp"
#include "InterruptedException.hpp"
#include "Field.hpp"

namespace obotcha {

void _Runnable::setResult(int v) {
    mResult = createInteger(v);
}

void _Runnable::setResult(byte v) {
    mResult = createByte(v);
}

void _Runnable::setResult(double v) {
    mResult = createDouble(v);
}

void _Runnable::setResult(bool v) {
    mResult = createBoolean(v);
}

void _Runnable::setResult(long v) {
    mResult = createLong(v);
}

void _Runnable::setResult(uint16_t v) {
    mResult = createUint16(v);
}

void _Runnable::setResult(uint32_t v) {
    mResult = createUint32(v);
}

void _Runnable::setResult(uint64_t v) {
    mResult = createUint64(v);
}

}
