#ifndef __OBOTCHA_FUTURE_HPP__
#define __OBOTCHA_FUTURE_HPP__

#include "Object.hpp"
#include "ExecutorTask.hpp"
#include "IllegalStateException.hpp"
#include "InterruptedException.hpp"
#include "ExecutorResult.hpp"
#include "TimeOutException.hpp"

namespace obotcha {

DECLARE_CLASS(Future) {
public:
    explicit _Future(ExecutorTask);

    ~_Future() = default;

    int wait(long interval = 0);

    void cancel();
    
    template <typename T> T getResult(long millseconds = 0) {
        switch(mTask->getStatus()) {
            case st(ExecutorTask)::Cancel:
            case st(ExecutorTask)::Idle:
            Trigger(IllegalStateException,"task is not excuted");
        }
        if(mTask->wait(millseconds) != -ETIMEDOUT) {
            if(mTask->getStatus() == st(ExecutorTask)::Cancel) {
                Trigger(InterruptedException, "Task has been cancelled");
            }
            return mTask->mResult->get<T>();
        }

        Trigger(TimeOutException, "time out");
    }

    int getStatus();

private:
    ExecutorTask mTask;
};

} // namespace obotcha
#endif