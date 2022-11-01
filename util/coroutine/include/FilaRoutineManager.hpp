#ifndef __OBOTCHA_FILA_CROUTINE_MANAGER_HPP__
#define __OBOTCHA_FILA_CROUTINE_MANAGER_HPP__

#include "co_routine.h"

#include "Object.hpp"
#include "Runnable.hpp"
#include "StrongPointer.hpp"
#include "ThreadLocal.hpp"
#include "HashMap.hpp"
#include "FilaRoutine.hpp"
#include "FilaCondition.hpp"
#include "HashSet.hpp"
#include "ConcurrentHashSet.hpp"

namespace obotcha {

DECLARE_CLASS(FilaRoutineManager) {
public:
    void addWaitCondition(FilaCondition);
    void removeWaitCondition(FilaCondition);
    HashSet<FilaRoutine> getWaitRoutine(FilaCondition);

    //void addRoutine(FilaRoutine);
    //FilaRoutine getRoutine();
    //void removeRoutine();

    static FilaRoutineManager getInstance();
  
private:
    _FilaRoutineManager();
    static FilaRoutineManager mInstance;

    Mutex mMutex;
    //ThreadLocal<FilaRoutine> routines;
    HashMap<FilaCondition,ConcurrentHashSet<FilaRoutine>> conditionMaps;
};

} // namespace obotcha
#endif
