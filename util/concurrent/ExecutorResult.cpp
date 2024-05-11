#include "ExecutorResult.hpp"

namespace obotcha {

void _ExecutorResult::update(int v) {
    mResult = Integer::New(v);
}

void _ExecutorResult::update(byte v) {
    mResult = Byte::New(v);
}

void _ExecutorResult::update(double v) {
    mResult = Double::New(v);
}

void _ExecutorResult::update(float v) {
    mResult = Float::New(v);
}

void _ExecutorResult::update(bool v) {
    mResult = Boolean::New(v);
}

void _ExecutorResult::update(long v) {
    mResult = Long::New(v);
}

void _ExecutorResult::update(uint16_t v) {
    mResult = Uint16::New(v);
}

void _ExecutorResult::update(uint32_t v) {
    mResult = Uint32::New(v);
}

void _ExecutorResult::update(uint64_t v) {
    mResult = Uint64::New(v);
}

} // namespace obotcha
