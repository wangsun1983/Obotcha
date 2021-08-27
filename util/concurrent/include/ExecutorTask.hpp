#ifndef __OBOTCHA_EXECUTOR_TASK_HPP__
#define __OBOTCHA_EXECUTOR_TASK_HPP__

#include "Mutex.hpp"
#include "Condition.hpp"
#include "Runnable.hpp"
#include "InterruptedException.hpp"
#include "TimeOutException.hpp"
#include "OStdInstanceOf.hpp"
#include "Error.hpp"
#include "NullPointerException.hpp"
#include "AutoLock.hpp"

namespace obotcha {

template<typename T>
class __ExecutorTaskResult {
public:
    T get(Object value) {
        return Cast<T>(value);
    }
};

#define __ExecutorTaskResultMacro(X,Y) \
template<> \
class __ExecutorTaskResult<X> { \
public: \
    X get(Object value) { \
        if(value == nullptr) { \
            Trigger(NullPointerException,"no result"); \
        }\
        auto v = Cast<Y>(value);\
        if(v == nullptr) {\
            Trigger(NullPointerException,"no result"); \
        }\
        return v->toValue(); \
    } \
};

__ExecutorTaskResultMacro(int,Integer)
__ExecutorTaskResultMacro(byte,Byte)
__ExecutorTaskResultMacro(double,Double)
__ExecutorTaskResultMacro(bool,Boolean)
__ExecutorTaskResultMacro(float,Double)
__ExecutorTaskResultMacro(long,Long)
__ExecutorTaskResultMacro(uint16_t,Uint16)
__ExecutorTaskResultMacro(uint32_t,Uint32)
__ExecutorTaskResultMacro(uint64_t,Uint64)


DECLARE_CLASS(ExecutorTask) {
public:
    _ExecutorTask(Runnable);

    ~_ExecutorTask();

    int wait(long interval = 0);

    void cancel();

    int getStatus();

    void execute();

    Runnable getRunnable();
    
    template<typename T>
    T getResult(int interval = 0) {
        if(this->wait(interval) != -WaitTimeout) {
            {
                AutoLock l(mMutex);
                if(mStatus != Complete) {
                    Trigger(InterruptedException,"wait exception");
                }
            }
            return __ExecutorTaskResult<T>().get(mResult);
        }

        Trigger(TimeOutException,"time out");
    }

    enum Status {
        Waiting = 0,
        Running,
        Cancel,
        Complete,
    };

    template<typename T>
    void setResult(T value) {
        mResult = value;
    }

    void setResult(int);
    void setResult(byte);
    void setResult(double);
    void setResult(bool);
    void setResult(long);
    void setResult(uint16_t);
    void setResult(uint32_t);
    void setResult(uint64_t);

private:

    Runnable mRunnable;

    int mStatus;

    Mutex mMutex;

    Condition mCompleteCond;

    Object mResult;
};

}
#endif