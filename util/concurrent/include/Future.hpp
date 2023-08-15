#ifndef __OBOTCHA_FUTURE_HPP__
#define __OBOTCHA_FUTURE_HPP__

#include "Object.hpp"
#include "ExecutorTask.hpp"
#include "IllegalStateException.hpp"
#include "InterruptedException.hpp"
#include "ExecutorResult.hpp"
#include "TimeOutException.hpp"
#include "Concurrent.hpp"

namespace obotcha {

DECLARE_CLASS(Future) {
public:
    explicit _Future(ExecutorTask);

    ~_Future() override = default;

    int wait(long interval = 0);

    void cancel();
    
    template <typename T> T getResult(long millseconds = 0) {
        auto status = mTask->getStatus();
        if(status == st(Concurrent)::Status::Interrupt ||
             status == st(Concurrent)::Status::Idle) {
                Trigger(IllegalStateException,"task is not excuted")
        }

        if(mTask->wait(millseconds) != -ETIMEDOUT) {
            if(mTask->getStatus() == st(Concurrent)::Status::Interrupt) {
                Trigger(InterruptedException, "Task has been cancelled")
            }
            return mTask->mResult->get<T>();
        }

        Trigger(TimeOutException, "time out")
    }

    st(Concurrent)::Status getStatus();

private:
    ExecutorTask mTask;
};

} // namespace obotcha
#endif