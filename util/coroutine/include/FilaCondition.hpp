#ifndef __OBOTCHA_FILA_CONDITION_HPP__
#define __OBOTCHA_FILA_CONDITION_HPP__

#include "co_routine.h"

#include "Object.hpp"
#include "FilaMutex.hpp"
#include "Condition.hpp"
#include "HashSet.hpp"
#include "HashMap.hpp"

namespace obotcha {

class _FilaRoutine;

DECLARE_CLASS(WaitRoutine) {
public:
    _WaitRoutine(sp<_FilaRoutine>);
    sp<_FilaRoutine> routine;
    int count = 1;
};

DECLARE_CLASS(FilaCondition) {

  public:
    friend class _FilaRoutine;
    _FilaCondition() = default;
    int wait(FilaMutex,long int mseconds = st(Concurrent)::kWaitForEver);
    void notify();
    void notifyAll();
    int getWaitCounts();
    
    ~_FilaCondition() override;

  private:
    void addWaitRoutine();
    void removeWaitRoutine();
    void doNotifyAll();
    void doNotify();

    Condition mThreadCond = createCondition();
    stCoCond_t *mCond = co_cond_alloc();

    static FilaMutex mWaitMutex;
    static HashMap<sp<_FilaCondition>,HashSet<WaitRoutine>> mWaitRoutines;
};

} // namespace obotcha
#endif
