#include "FilaFuture.hpp"

namespace obotcha {

ConcurrentHashMap<uint64_t,Object> _FilaFuture::FilaExecuteResults 
                = createConcurrentHashMap<uint64_t,Object>();

_FilaFuture::_FilaFuture() {
    mMutex = createMutex();
    mCond = createCondition();
    mResultType = ResultType::Success;
}

void _FilaFuture::setOwner(stCoRoutine_t *owner) {
    this->owner = owner;
}

int _FilaFuture::getResultType() {
    return mResultType;
}

void _FilaFuture::setResultType(int type) {
    mResultType = type;
}

void _FilaFuture::setResult(int v) {
    auto coa = GetCurrThreadCo();
    FilaExecuteResults->put((uint64_t)coa,createInteger(v));
}

void _FilaFuture::setResult(byte v) {
    auto coa = GetCurrThreadCo();
    FilaExecuteResults->put((uint64_t)coa,createByte(v));
}

void _FilaFuture::setResult(double v) {
    auto coa = GetCurrThreadCo();
    FilaExecuteResults->put((uint64_t)coa,createDouble(v));
}

void _FilaFuture::setResult(bool v) {
    auto coa = GetCurrThreadCo();
    FilaExecuteResults->put((uint64_t)coa,createBoolean(v));
}

void _FilaFuture::setResult(long v) {
    auto coa = GetCurrThreadCo();
    FilaExecuteResults->put((uint64_t)coa,createLong(v));
}

void _FilaFuture::setResult(uint16_t v) {
    auto coa = GetCurrThreadCo();
    FilaExecuteResults->put((uint64_t)coa,createUint16(v));
}

void _FilaFuture::setResult(uint32_t v) {
    auto coa = GetCurrThreadCo();
    FilaExecuteResults->put((uint64_t)coa,createUint32(v));
}

void _FilaFuture::setResult(uint64_t v) {
    auto coa = GetCurrThreadCo();
    FilaExecuteResults->put((uint64_t)coa,createUint64(v));
}

void _FilaFuture::wake() {
    mCond->notify();
}

void _FilaFuture::wakeAll() {
    mCond->notifyAll();
}

} // namespace obotcha
