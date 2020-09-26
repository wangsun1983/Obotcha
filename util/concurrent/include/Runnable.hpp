#ifndef __OBOTCHA_RUNNABLE_HPP__
#define __OBOTCHA_RUNNABLE_HPP__

#include <stdio.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"
#include "ResultDuplicateException.hpp"
#include "InterruptedException.hpp"

namespace obotcha {

enum ResultStatus {
    ResultWaiting = 0,
    ResultComplete,
    ResultInterrupt
};

class _Future;
class _FutureTask;

DECLARE_SIMPLE_CLASS(Runnable) {

public:
    friend class _Future;
    friend class _FutureTask;

	virtual void run() = 0;
    
    virtual void onInterrupt(){};

    virtual ~_Runnable() {}

    _Runnable();

    template<typename T>
    void setResult(T value) {
        AutoLock l(mResultMutex);
        if(resultComplete == ResultWaiting) {
            objResult = (sp<Object>)value;
            resultComplete = ResultComplete;
            mResultCond->notifyAll();
            return;
        }
        throw ResultDuplicateException("set int result");
    }

    void setResult(int);
    void setResult(byte);
    void setResult(double);
    void setResult(bool);
    void setResult(float);
    void setResult(long);
    void setResult(uint16_t);
    void setResult(uint32_t);
    void setResult(uint64_t);
    void setResult(String);

private:
    
    sp<Object> objResult;
    ResultStatus resultComplete;

    int intValue;
    byte byteValue;
    double doubleValue;
    bool boolValue;
    float floatValue;
    long longValue;
    uint8_t uint8Value;
    uint16_t uint16Value;
    uint32_t uint32Value;
    uint64_t uint64Value;
    String stringValue;

    Mutex mResultMutex;
    Condition mResultCond;

    void interruptResultWait();
    template<typename T>
    void getResult(T &v) {
        AutoLock l(mResultMutex);
        if(!resultComplete) {
            mResultCond->wait(mResultMutex);
        }

        if(resultComplete == ResultInterrupt) {
            throw InterruptedException("Runnable Interrupt");
        }

        transform_cast(objResult,v);
    }

    void getResult(int &);
    void getResult(byte &);
    void getResult(double &);
    void getResult(bool &);
    void getResult(float &);
    void getResult(long &);
    void getResult(uint16_t &);
    void getResult(uint32_t &);
    void getResult(uint64_t &);
    void getResult(String &);
};

}
#endif