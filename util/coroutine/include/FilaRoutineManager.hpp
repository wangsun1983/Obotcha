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

namespace obotcha {

DECLARE_CLASS(FilaRoutineManager) {
public:
    void addWaitCondition(FilaCondition);
    void removeWaitCondition(FilaCondition);
    HashSet<FilaRoutine> getWaitCroutine(FilaCondition);

    void addCroutine(FilaRoutine);
    void removeFilaRoutine();

    static FilaRoutineManager getInstance();
  
private:
    _FilaRoutineManager();
    static FilaRoutineManager mInstance;

    Mutex mMutex;
    ThreadLocal<FilaRoutine> croutines;
    //HashMap<FilaRoutine,HashSet<FilaCondition>> conditionMaps;
    HashMap<FilaCondition,HashSet<FilaRoutine>> conditionMaps;
};

} // namespace obotcha
#endif
