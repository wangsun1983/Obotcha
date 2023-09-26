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
    _FilaFuture() = default;

    template <typename T> 
    T getResult(long millseconds = 0) {
        switch(mStatus) {
            case st(Concurrent)::Status::Interrupt:
            Trigger(IllegalStateException,"task is not excuted")
            break;

            case st(Concurrent)::Status::Idle:
            case st(Concurrent)::Status::Running: {
                AutoLock l(mMutex);
                if(mCond->wait(mMutex,millseconds) == -ETIMEDOUT) {
                    Trigger(TimeOutException, "time out")
                }
            }

            case st(Concurrent)::Status::Complete: {
                if(mResult == nullptr) {
                    Trigger(NullPointerException,"no result")
                }

                return mResult->get<T>();
            }
            break;

            default:
            //do nothing
            break;
        }
        
        Trigger(IllegalStateException,"no result")
    }

    int wait(long interval = st(Concurrent)::kWaitForEver);

    void wakeAll();
    void wake();
    void setOwner(stCoRoutine_t *owner);

    st(Concurrent)::Status getStatus() const;
    void setStatus(st(Concurrent)::Status);

    FilaExecutorResult genResult();

private:
    stCoRoutine_t *owner;
    FilaMutex mMutex = createFilaMutex();
    FilaCondition mCond = createFilaCondition();
    FilaExecutorResult mResult;

    st(Concurrent)::Status mStatus = st(Concurrent)::Status::Idle;
};

} // namespace obotcha
#endif