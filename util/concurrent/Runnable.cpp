#include <stdio.h>
#include "Runnable.hpp"
#include "AutoLock.hpp"
#include "IllegalStateException.hpp"
#include "InterruptedException.hpp"

namespace obotcha {

#define SET_RESULT_FUNC(Param,V) \
    AutoLock l(mResultMutex);\
    if(resultComplete == ResultWaiting) {\
        Param = V;\
        resultComplete = ResultComplete;\
        mResultCond->notifyAll();\
        return;\
    }\
    throwIllegalStateException("already set int result");

#define GET_RESULT_FUNC(Param,V) \
    AutoLock l(mResultMutex);\
    if(resultComplete == ResultWaiting) {\
        mResultCond->wait(mResultMutex);\
    }\
    if(resultComplete == ResultInterrupt) {\
        throwInterruptedException("Runnable Interrupt");\
    }\
    v = Param;


_Runnable::_Runnable() {
    mResultMutex = createMutex("RunnableResultMutex");
    mResultCond = createCondition();
    resultComplete = ResultWaiting;
}

void _Runnable::interruptResultWait() {
    AutoLock l(mResultMutex);
    resultComplete = ResultInterrupt;
    mResultCond->notifyAll();
}

void _Runnable::setResult(int v) {
    SET_RESULT_FUNC(intValue,v)
}

void _Runnable::setResult(byte v) {
    SET_RESULT_FUNC(byteValue,v)
}

void _Runnable::setResult(double v) {
    SET_RESULT_FUNC(doubleValue,v)
}

void _Runnable::setResult(bool v) {
    SET_RESULT_FUNC(boolValue,v)
}

void _Runnable::setResult(float v) {
    SET_RESULT_FUNC(floatValue,v)
}

void _Runnable::setResult(long v) {
    SET_RESULT_FUNC(longValue,v)
}

void _Runnable::setResult(uint16_t v) {
    SET_RESULT_FUNC(uint16Value,v)
}

void _Runnable::setResult(uint32_t v) {
    SET_RESULT_FUNC(uint32Value,v)
}

void _Runnable::setResult(uint64_t v) {
    SET_RESULT_FUNC(uint64Value,v)
}

void _Runnable::setResult(String v) {
    SET_RESULT_FUNC(stringValue,v)
}

void _Runnable::getResult(int &v) {
    GET_RESULT_FUNC(intValue,v)
}

void _Runnable::getResult(byte &v) {
    GET_RESULT_FUNC(byteValue,v)
}

void _Runnable::getResult(double &v) {
    GET_RESULT_FUNC(doubleValue,v)
}

void _Runnable::getResult(bool &v) {
    GET_RESULT_FUNC(boolValue,v)
}

void _Runnable::getResult(float &v) {
    GET_RESULT_FUNC(floatValue,v)
}

void _Runnable::getResult(long &v) {
    GET_RESULT_FUNC(longValue,v)
}

void _Runnable::getResult(uint16_t &v) {
    GET_RESULT_FUNC(uint16Value,v)
}

void _Runnable::getResult(uint32_t &v) {
    GET_RESULT_FUNC(uint32Value,v)
}

void _Runnable::getResult(uint64_t &v) {
    GET_RESULT_FUNC(uint64Value,v)
}

void _Runnable::getResult(String &v) {
    GET_RESULT_FUNC(stringValue,v)
}

}
