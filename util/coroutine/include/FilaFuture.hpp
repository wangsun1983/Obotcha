#ifndef __OBOTCHA_FILA_FUTURE_HPP__
#define __OBOTCHA_FILA_FUTURE_HPP__

#include "co_routine.h"
#include "co_routine_inner.h"

#include "Object.hpp"
#include "Runnable.hpp"
#include "String.hpp"
#include "StrongPointer.hpp"
#include "FilaMutex.hpp"
#include "OStdApply.hpp"
#include "ConcurrentHashMap.hpp"
#include "Condition.hpp"
#include "ExecutorTask.hpp"

namespace obotcha {

DECLARE_CLASS(FilaFuture) {

public:
    _FilaFuture();

    template <typename T> 
    T getResult(long millseconds = 0) {
        while(1) {
            auto result = FilaExecuteResults->get((uint64_t)owner);
            AutoLock l(mMutex);
            if(result == nullptr) {
                mCond->wait(mMutex);
                continue;
            }
            return __ExecutorTaskResult<T>().get(result);
        }
    }


    template <typename T> static void setResult(T value) {
        auto coa = GetCurrThreadCo();
        FilaExecuteResults->put((uint64_t)coa,value);
    }

    void wait();

    void wakeAll();
    void wake();

    static void setResult(int);
    static void setResult(byte);
    static void setResult(double);
    static void setResult(bool);
    static void setResult(long);
    static void setResult(uint16_t);
    static void setResult(uint32_t);
    static void setResult(uint64_t);

    void setOwner(stCoRoutine_t *owner);

private:
    stCoRoutine_t *owner;
    static ConcurrentHashMap<uint64_t,Object> FilaExecuteResults;
    Mutex mMutex;
    Condition mCond;
};

} // namespace obotcha
#endif