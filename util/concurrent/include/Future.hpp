#ifndef __OBOTCHA_FUTURE_HPP__
#define __OBOTCHA_FUTURE_HPP__

#include "ExecutorTask.hpp"
#include "ExecutorResult.hpp"
#include "IllegalStateException.hpp"
#include "InterruptedException.hpp"

namespace obotcha {

DECLARE_CLASS(Future) {
public:
    _Future(ExecutorTask);

    ~_Future();

    int wait(long interval = 0);

    void cancel();
    
    template <typename T> T getResult(long millseconds = 0) {
        switch(mTask->getStatus()) {
            case st(ExecutorTask)::Cancel:
            case st(ExecutorTask)::Waiting:
            Trigger(IllegalStateException,"task is not excuted");
        }
        if(mTask->wait(millseconds) != -ETIMEDOUT) {
            if(mTask->getStatus() == Cancel) {
                Trigger(InterruptedException, "task has been cancelled");
            }
            return mTask->mResult->get<T>();
        }

        Trigger(TimeOutException, "time out");
    }

    int getStatus();

    enum Status {
        Waiting = st(ExecutorTask)::Waiting,
        Running,
        Cancel,
        Complete,
    };

private:
    ExecutorTask mTask;
};

} // namespace obotcha
#endif