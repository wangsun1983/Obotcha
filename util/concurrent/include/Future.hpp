#ifndef __OBOTCHA_FUTURE_HPP__
#define __OBOTCHA_FUTURE_HPP__

#include "ExecutorTask.hpp"

namespace obotcha {

DECLARE_CLASS(Future) {
public:
    _Future(ExecutorTask);

    ~_Future();

    int wait(long interval = 0);

    void cancel();

    template <typename T> T getResult(long millseconds = 0) {
        return mTask->getResult<T>(millseconds);
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