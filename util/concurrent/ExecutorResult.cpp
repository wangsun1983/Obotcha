#include "ExecutorResult.hpp"

namespace obotcha {

void _ExecutorResult::update(int v) {
    mResult = createInteger(v);
}

void _ExecutorResult::update(byte v) {
    mResult = createByte(v);
}

void _ExecutorResult::update(double v) {
    mResult = createDouble(v);
}

void _ExecutorResult::update(bool v) {
    mResult = createBoolean(v);
}

void _ExecutorResult::update(long v) {
    mResult = createLong(v);
}

void _ExecutorResult::update(uint16_t v) {
    mResult = createUint16(v);
}

void _ExecutorResult::update(uint32_t v) {
    mResult = createUint32(v);
}

void _ExecutorResult::update(uint64_t v) {
    mResult = createUint64(v);
}

} // namespace obotcha
