#include <stdio.h>
#include "Runnable.hpp"
#include "AutoLock.hpp"
#include "IllegalStateException.hpp"
#include "InterruptedException.hpp"

namespace obotcha {

#define SET_RESULT_FUNC(Param,V) \
    AutoLock l(mResultMutex);\
    if(mStatus == ResultWaiting) {\
        Param = V;\
        mStatus = ResultComplete;\
        mResultCond->notifyAll();\
        return;\
    }\
    Trigger(IllegalStateException,"already set int result");

#define GET_RESULT_FUNC(Param,Value,DefaultValue,Interval) \
    AutoLock l(mResultMutex);\
    if(mStatus == ResultWaiting) {\
        if(mResultCond->wait(mResultMutex,Interval) == -WaitTimeout) {\
            Value = DefaultValue;\
            return;\
        }\
    }\
    if(mStatus == ResultInterrupt) {\
        Value = DefaultValue;\
    }\
    Value = Param;


_Runnable::_Runnable() {
    mResultMutex = createMutex("RunnableResultMutex");
    mResultCond = createCondition();
    mStatus = ResultWaiting;
}

void _Runnable::interruptResultWait() {
    AutoLock l(mResultMutex);
    mStatus = ResultInterrupt;
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

void _Runnable::getResult(int &value,int defaultvalue,long millseconds) {
    GET_RESULT_FUNC(intValue,value,defaultvalue,millseconds);
}

void _Runnable::getResult(byte &value,byte defaultvalue,long millseconds) {
    GET_RESULT_FUNC(byteValue,value,defaultvalue,millseconds);
}

void _Runnable::getResult(double &value,double defaultvalue,long millseconds) {
    GET_RESULT_FUNC(doubleValue,value,defaultvalue,millseconds);
}

void _Runnable::getResult(bool &value,bool defaultvalue,long millseconds) {
    GET_RESULT_FUNC(boolValue,value,defaultvalue,millseconds);
}

void _Runnable::getResult(float &value,float defaultvalue,long millseconds) {
    GET_RESULT_FUNC(floatValue,value,defaultvalue,millseconds);
}

void _Runnable::getResult(long &value,long defaultvalue,long millseconds) {
    GET_RESULT_FUNC(longValue,value,defaultvalue,millseconds);
}

void _Runnable::getResult(uint16_t &value,uint16_t defaultvalue,long millseconds) {
    GET_RESULT_FUNC(uint16Value,value,defaultvalue,millseconds);
}

void _Runnable::getResult(uint32_t &value,uint32_t defaultvalue,long millseconds) {
    GET_RESULT_FUNC(uint32Value,value,defaultvalue,millseconds);
}

void _Runnable::getResult(uint64_t &value,uint64_t defaultvalue,long millseconds) {
    GET_RESULT_FUNC(uint64Value,value,defaultvalue,millseconds);
}

void _Runnable::getResult(String &value,String defaultvalue,long millseconds) {
    GET_RESULT_FUNC(stringValue,value,defaultvalue,millseconds);
}

}
