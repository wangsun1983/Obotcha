#ifndef __OBOTCHA_PROCESS_CONDITION_HPP__
#define __OBOTCHA_PROCESS_CONDITION_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ProcessMutex.hpp"
#include "AutoLock.hpp"

namespace obotcha {

DECLARE_CLASS(ProcessCondition) {
public:
    explicit _ProcessCondition(String name);
    int wait(ProcessMutex m, long int millseconds = 0);
    int wait(AutoLock &m, long int millseconds = 0);
    void notify();
    void notifyAll();
    static void Clear(String name);
    static void Create(String name);

    ~_ProcessCondition() override;

private:
    String mName;
    pthread_cond_t *mCond = nullptr;
    int mConditionFd = -1;
};

}
#endif
