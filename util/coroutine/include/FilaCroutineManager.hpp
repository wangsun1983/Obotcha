#ifndef __OBOTCHA_FILA_CROUTINE_MANAGER_HPP__
#define __OBOTCHA_FILA_CROUTINE_MANAGER_HPP__

#include "co_routine.h"

#include "Object.hpp"
#include "Runnable.hpp"
#include "StrongPointer.hpp"
#include "ThreadLocal.hpp"
#include "HashMap.hpp"
#include "FilaCroutine.hpp"
#include "FilaCondition.hpp"
#include "HashSet.hpp"

namespace obotcha {

DECLARE_CLASS(FilaCroutineManager) {
public:
    void addWaitCondition(FilaCondition);
    void removeWaitCondition(FilaCondition);
    HashSet<FilaCroutine> getWaitCroutine(FilaCondition);

    void addCroutine(FilaCroutine);
    void removeFilaCroutine();

    static FilaCroutineManager getInstance();
  
private:
    _FilaCroutineManager();
    static FilaCroutineManager mInstance;

    Mutex mMutex;
    ThreadLocal<FilaCroutine> croutines;
    //HashMap<FilaCroutine,HashSet<FilaCondition>> conditionMaps;
    HashMap<FilaCondition,HashSet<FilaCroutine>> conditionMaps;
};

} // namespace obotcha
#endif
