#ifndef __OBOTCHA_FUTURE_HPP__
#define __OBOTCHA_FUTURE_HPP__

#include "ExecutorTask.hpp"
#include "ExecutorResult.hpp"

namespace obotcha {

DECLARE_CLASS(Future) {
public:
    _Future(ExecutorTask);

    ~_Future();

    int wait(long interval = 0);

    void cancel();
    
    template <typename T> T getResult(long millseconds = 0) {
        if(mTask->wait(millseconds) != -ETIMEDOUT) {
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