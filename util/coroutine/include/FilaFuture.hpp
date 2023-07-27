#ifndef __OBOTCHA_FILA_FUTURE_HPP__
#define __OBOTCHA_FILA_FUTURE_HPP__

#include "co_routine.h"
#include "co_routine_inner.h"

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "FilaMutex.hpp"
#include "FilaCondition.hpp"
#include "FilaExecutorResult.hpp"
#include "NullPointerException.hpp"
#include "IllegalStateException.hpp"
#include "TimeOutException.hpp"

namespace obotcha {

DECLARE_CLASS(FilaFuture) {

public:
    enum Status {
        Idle = 0,
        Running,
        Complete,
        Interrupt
    };

    _FilaFuture();

    template <typename T> 
    T getResult(long millseconds = 0) {
        switch(mStatus) {
            case Interrupt:
            Trigger(IllegalStateException,"task is not excuted")
            break;

            case Idle:
            case Running: {
                AutoLock l(mMutex);
                if(mCond->wait(mMutex,millseconds) == -ETIMEDOUT) {
                    Trigger(TimeOutException, "time out")
                }
            }

            case Complete: {
                if(mResult == nullptr) {
                    Trigger(NullPointerException,"no result")
                }

                return mResult->get<T>();
            }
            break;

            default:
                Trigger(IllegalStateException,"unknown state")
            break;
        }
    }

    int wait(long interval = -1);

    void wakeAll();
    void wake();
    void setOwner(stCoRoutine_t *owner);

    int getStatus();
    void setStatus(int);

    FilaExecutorResult genResult();

private:
    stCoRoutine_t *owner;
    FilaMutex mMutex;
    FilaCondition mCond;
    FilaExecutorResult mResult;

    int mStatus;
};

} // namespace obotcha
#endif