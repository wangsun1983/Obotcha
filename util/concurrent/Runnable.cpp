#include <stdio.h>
#include "Runnable.hpp"
#include "AutoLock.hpp"
#include "IllegalStateException.hpp"
#include "InterruptedException.hpp"
#include "Field.hpp"

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

#define GET_RESULT_FUNC(Type,Value,DefaultValue,Interval) \
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
    switch(mValueType) {\
        case st(Field)::FieldTypeInt:\
            Value = (Type)intValue;\
            break;\
        case st(Field)::FieldTypeByte:\
            Value = (Type)byteValue;\
            break;\
        case st(Field)::FieldTypeDouble:\
            Value = (Type)doubleValue;\
            break;\
        case st(Field)::FieldTypeBool:\
            Value = (Type)boolValue;\
            break;\
        case st(Field)::FieldTypeFloat:\
            Value = (Type)floatValue;\
            break;\
        case st(Field)::FieldTypeLong:\
            Value = (Type)longValue;\
            break;\
        case st(Field)::FieldTypeUint16:\
            Value = (Type)uint16Value;\
            break;\
        case st(Field)::FieldTypeUint32:\
            Value = (Type)uint32Value;\
            break;\
        case st(Field)::FieldTypeUint64:\
            Value = (Type)uint64Value;\
            break;\
        default:\
            Value = DefaultValue;\
    }\
    

_Runnable::_Runnable() {
    mResultMutex = createMutex("RunnableResultMutex");
    mResultCond = createCondition();
    mStatus = ResultWaiting;
    mValueType = -1;
}

void _Runnable::interruptResultWait() {
    AutoLock l(mResultMutex);
    mStatus = ResultInterrupt;
    mResultCond->notifyAll();
}

void _Runnable::setResult(int v) {
    mValueType = st(Field)::FieldTypeInt;
    SET_RESULT_FUNC(intValue,v)
}

void _Runnable::setResult(byte v) {
    mValueType = st(Field)::FieldTypeByte;
    SET_RESULT_FUNC(byteValue,v)
}

void _Runnable::setResult(double v) {
    mValueType = st(Field)::FieldTypeDouble;
    SET_RESULT_FUNC(doubleValue,v)
}

void _Runnable::setResult(bool v) {
    mValueType = st(Field)::FieldTypeBool;
    SET_RESULT_FUNC(boolValue,v)
}

void _Runnable::setResult(float v) {
    mValueType = st(Field)::FieldTypeFloat;
    SET_RESULT_FUNC(floatValue,v)
}

void _Runnable::setResult(long v) {
    mValueType = st(Field)::FieldTypeLong;
    SET_RESULT_FUNC(longValue,v)
}

void _Runnable::setResult(uint16_t v) {
    mValueType = st(Field)::FieldTypeUint16;
    SET_RESULT_FUNC(uint16Value,v)
}

void _Runnable::setResult(uint32_t v) {
    mValueType = st(Field)::FieldTypeUint32;
    SET_RESULT_FUNC(uint32Value,v)
}

void _Runnable::setResult(uint64_t v) {
    mValueType = st(Field)::FieldTypeUint64;
    SET_RESULT_FUNC(uint64Value,v)
}

void _Runnable::setResult(String v) {
    mValueType = st(Field)::FieldTypeString;
    SET_RESULT_FUNC(stringValue,v)
}

void _Runnable::getResult(int &value,int defaultvalue,long millseconds) {
    GET_RESULT_FUNC(int,value,defaultvalue,millseconds);
}

void _Runnable::getResult(byte &value,byte defaultvalue,long millseconds) {
    GET_RESULT_FUNC(byte,value,defaultvalue,millseconds);
}

void _Runnable::getResult(double &value,double defaultvalue,long millseconds) {
    GET_RESULT_FUNC(double,value,defaultvalue,millseconds);
}

void _Runnable::getResult(bool &value,bool defaultvalue,long millseconds) {
    GET_RESULT_FUNC(bool,value,defaultvalue,millseconds);
}

void _Runnable::getResult(float &value,float defaultvalue,long millseconds) {
    GET_RESULT_FUNC(float,value,defaultvalue,millseconds);
}

void _Runnable::getResult(long &value,long defaultvalue,long millseconds) {
    GET_RESULT_FUNC(long,value,defaultvalue,millseconds);
}

void _Runnable::getResult(uint16_t &value,uint16_t defaultvalue,long millseconds) {
    GET_RESULT_FUNC(uint16_t,value,defaultvalue,millseconds);
}

void _Runnable::getResult(uint32_t &value,uint32_t defaultvalue,long millseconds) {
    GET_RESULT_FUNC(uint32_t,value,defaultvalue,millseconds);
}

void _Runnable::getResult(uint64_t &value,uint64_t defaultvalue,long millseconds) {
    GET_RESULT_FUNC(uint64_t,value,defaultvalue,millseconds);
}

void _Runnable::getResult(String &value,String defaultvalue,long millseconds) {
    //GET_RESULT_FUNC(String,value,defaultvalue,millseconds);
    AutoLock l(mResultMutex);
    if(mStatus == ResultWaiting) {
        if(mResultCond->wait(mResultMutex,millseconds) == -WaitTimeout) {
            value = defaultvalue;
            return;
        }
    }
    if(mStatus == ResultInterrupt) {
        value = defaultvalue;
    }

    value = stringValue;
}

}
