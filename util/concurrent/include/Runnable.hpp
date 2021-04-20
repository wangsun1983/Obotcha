#ifndef __OBOTCHA_RUNNABLE_HPP__
#define __OBOTCHA_RUNNABLE_HPP__

#include <stdio.h>
#include <future>
#include <utility>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Mutex.hpp"
#include "AutoLock.hpp"
#include "Condition.hpp"
#include "IllegalStateException.hpp"
#include "Error.hpp"
#include "OStdApply.hpp"

namespace obotcha {

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
        if(mStatus == ResultWaiting) {
            objResult = (sp<_Object>)value;
            mStatus = ResultComplete;
            mResultCond->notifyAll();
            return;
        }
        Trigger(IllegalStateException,"set int result");
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

    template<typename T>
    void getResult(T &value,T defaultvalue,long millseconds = 0) {
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

        value = Cast<T>(objResult);
    }

private:
    enum ResultStatus {
        ResultWaiting = 0,
        ResultComplete,
        ResultInterrupt
    };
    
    sp<_Object> objResult;

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
    int mStatus;

    int mValueType;

    void interruptResultWait();

    void getResult(int &value,int defaultvalue,long millseconds = 0);
    void getResult(byte &value,byte defaultvalue,long millseconds = 0);
    void getResult(double &value,double defaultvalue,long millseconds = 0);
    void getResult(bool &value,bool defaultvalue,long millseconds = 0);
    void getResult(float &value,float defaultvalue,long millseconds = 0);
    void getResult(long &value,long defaultvalue,long millseconds = 0);
    void getResult(uint16_t &value,uint16_t defaultvalue,long millseconds = 0);
    void getResult(uint32_t &value,uint32_t defaultvalue,long millseconds = 0);
    void getResult(uint64_t &value,uint64_t defaultvalue,long millseconds = 0);
    void getResult(String &value,String defaultvalue,long millseconds = 0);


};

template<class Function,class... Args> 
class _LambdaRunnable:public _Runnable{
public:
    _LambdaRunnable(Function &&f,Args&&... args):_Runnable(),func(f),_arguments(std::make_tuple(args...)) {

    }

    void run() {
        //func(initializer_list(_arguments));
        ostd::apply(func,_arguments);
    }

private:
    std::tuple<Args...> _arguments;
    Function func;
};

template<typename Callfunc,typename... Args> 
sp<_Runnable> createLambdaRunnable(Callfunc f,Args ...args) {
    _Runnable *r = new _LambdaRunnable<Callfunc,Args ...>(std::forward<Callfunc>(f),
			     std::forward<Args>(args)...);
    return AutoClone(r);
}

}
#endif